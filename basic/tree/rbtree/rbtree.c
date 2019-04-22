/*
 * Copyright: (c) 2006-2007, 2008 Triductor Technology, Inc.
 * All Rights Reserved.
 *
 * File:        rbtree.c
 * Purpose:     Red black tree algorithms.
 * History:     07/15/2007, created by jetmotor
 */

#include "rbtree.h"


static void rb_link_node(struct rb_node *node, struct rb_node *parent, struct rb_node **rb_link);
static void rb_insert_color(struct rb_root *root, struct rb_node *node);
static void rb_erase(struct rb_root *root, struct rb_node *node);
static void rb_erase_color(struct rb_root *root, struct rb_node *node, struct rb_node *parent);

static void rb_rotate_left(struct rb_node *node, struct rb_root *root);
static void rb_rotate_right(struct rb_node * node, struct rb_root * root);


void rb_tree_init(rb_tree_t *tree, 
		     rb_treenode_cmp_fp cmp,
		     rb_tree_find_fp find,
		     rb_tree_insert_fp insert,
		     rb_tree_erase_fp erase,
		     rb_treenode_del_fp del,
		     rb_tree_finalize_fp finalize)
{
	tree->nr = 0;
	tree->root.rb_node = tree->first = NULL;

	tree->cmp = cmp;
	tree->find = find;
	tree->insert = insert;
	tree->erase = erase;
	tree->del = del;
	tree->finalize = finalize;

	return;
}


struct rb_node ** rb_tree_find_default(rb_tree_t *tree, void *key, struct rb_node **parent)
{
	struct rb_node **p = &(tree->root.rb_node);
	int32_t res;
	
	*parent = NULL;
	while ( *p ) {
		*parent = *p;
		res = tree->cmp(*parent, key);

		if ( res > 0 )
			p = &(*p)->rb_left;
		else if ( res < 0 )
			p = &(*p)->rb_right;
		else
			break;
	}

	return p;
}


void rb_tree_insert_default(rb_tree_t *tree, struct rb_node *n, struct rb_node *parent, struct rb_node **p)
{
	rb_link_node(n, parent, p);
	rb_insert_color(&tree->root, n);
	tree->first = rb_first(&tree->root);
	tree->nr++;

	return;
}


void rb_tree_erase_default(rb_tree_t *tree, struct rb_node *n)
{
	rb_erase(&tree->root, n);
	tree->nr--;
	if ( tree->first == n )
		tree->first = rb_first(&tree->root);
	
	return;
}


void rb_tree_finalize_default(rb_tree_t *tree)
{
	if ( tree->root.rb_node )
		_rb_tree_finalize_default(&tree->root.rb_node, tree->del);
	
	return;
}


void _rb_tree_finalize_default(struct rb_node **p, rb_treenode_del_fp del)
{
	if ( (*p)->rb_left )
		_rb_tree_finalize_default(&(*p)->rb_left, del);
	else if ( (*p)->rb_right )
		_rb_tree_finalize_default(&(*p)->rb_right, del);
	else {
		if ( del ) {
			del(*p);
			*p = NULL;
		}
			
		return;
	}
}


struct rb_node * rb_first(struct rb_root *root)
{
	struct rb_node *n;


	if ( (n = root->rb_node) == NULL )
		return NULL;

	while ( n->rb_left )
		n = n->rb_left;

	return n;
}


struct rb_node * rb_last(struct rb_root *root)
{
	struct rb_node *n;
	
	
        if ( (n = root->rb_node) == NULL )
                return NULL;
	
        while ( n->rb_right )
                n = n->rb_right;

        return n;
}


struct rb_node * rb_next(struct rb_node *node)
{
	/* If we have a right-hand child, go down and then left as far
	 * as we can.
	 */
	if ( node->rb_right ) {
                node = node->rb_right;

                while ( node->rb_left )
                        node = node->rb_left;

                return node;
        }

        /* No right-hand children.  Everything down and left is
	 * smaller than us, so any 'next' node must be in the general
         * direction of our parent. Go up the tree; any time the
	 * ancestor is a right-hand child of its parent, keep going
         * up. First time it's a left-hand child of its parent, said
         * parent is our 'next' node.
	 */
        while ( node->rb_parent && node == node->rb_parent->rb_right )
                node = node->rb_parent;

        return node->rb_parent;
}


struct rb_node * rb_prev(struct rb_node *node)
{
        /* If we have a left-hand child, go down and then right as far
	 * as we can.
	 */
        if ( node->rb_left ) {
                node = node->rb_left;

                while ( node->rb_right )
                        node = node->rb_right;

                return node;
        }

        /* No left-hand children. Go up till we find an ancestor which
         * is a right-hand child of its parent.
	 */
        while ( node->rb_parent && node == node->rb_parent->rb_left )
                node = node->rb_parent;

        return node->rb_parent;
}


void rb_link_node(struct rb_node *node, struct rb_node *parent, struct rb_node **rb_link)
{
	node->rb_parent = parent;
	node->rb_color = RB_RED;
	node->rb_left = node->rb_right = NULL;

	*rb_link = node;
}


void rb_insert_color(struct rb_root *root, struct rb_node *node)
{
	struct rb_node *parent, *gparent;


	while ( (parent = node->rb_parent) && parent->rb_color == RB_RED ) {
		gparent = parent->rb_parent;

		if ( parent == gparent->rb_left ) {
			{
				register struct rb_node *uncle = gparent->rb_right;

				if (uncle && uncle->rb_color == RB_RED)	{
					uncle->rb_color = RB_BLACK;
					parent->rb_color = RB_BLACK;
					gparent->rb_color = RB_RED;
					node = gparent;
					continue;
				}
			}

			if ( parent->rb_right == node ) {
				register struct rb_node *tmp;

				rb_rotate_left(parent, root);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			parent->rb_color = RB_BLACK;
			gparent->rb_color = RB_RED;
			rb_rotate_right(gparent, root);

		} else {
			{
				register struct rb_node *uncle = gparent->rb_left;

				if ( uncle && uncle->rb_color == RB_RED ) {
					uncle->rb_color = RB_BLACK;
					parent->rb_color = RB_BLACK;
					gparent->rb_color = RB_RED;
					node = gparent;
					continue;
				}
			}

			if ( parent->rb_left == node ) {
				register struct rb_node *tmp;

				rb_rotate_right(parent, root);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			parent->rb_color = RB_BLACK;
			gparent->rb_color = RB_RED;
			rb_rotate_left(gparent, root);
		}
	}

	root->rb_node->rb_color = RB_BLACK;
}


void rb_erase(struct rb_root *root, struct rb_node *node)
{
	struct rb_node *child, *parent;
	int color;


	if ( !node->rb_left )
		child = node->rb_right;
	else if ( !node->rb_right )
		child = node->rb_left;
	else {
		struct rb_node * old = node, * left;

		node = node->rb_right;
		while ( (left = node->rb_left) )
			node = left;

		child = node->rb_right;
		parent = node->rb_parent;
		color = node->rb_color;

		if ( child )
			child->rb_parent = parent;
		if ( parent ) {
			if ( parent->rb_left == node )
				parent->rb_left = child;
			else
				parent->rb_right = child;
		}
		else
			root->rb_node = child;

		if ( node->rb_parent == old )
			parent = node;
		node->rb_parent = old->rb_parent;
		node->rb_color = old->rb_color;
		node->rb_right = old->rb_right;
		node->rb_left = old->rb_left;

		if ( old->rb_parent ) {
			if (old->rb_parent->rb_left == old)
				old->rb_parent->rb_left = node;
			else
				old->rb_parent->rb_right = node;
		} else
			root->rb_node = node;

		old->rb_left->rb_parent = node;
		if ( old->rb_right )
			old->rb_right->rb_parent = node;
		goto color;
	}

	parent = node->rb_parent;
	color = node->rb_color;

	if ( child )
		child->rb_parent = parent;
	if ( parent ) {
		if ( parent->rb_left == node )
			parent->rb_left = child;
		else
			parent->rb_right = child;
	}
	else
		root->rb_node = child;

 color:
	if ( color == RB_BLACK )
		rb_erase_color(root, child, parent);
}


void rb_erase_color(struct rb_root *root, struct rb_node *node, struct rb_node *parent)
{
	struct rb_node *other;

	while ( (!node || node->rb_color == RB_BLACK) && node != root->rb_node ) {

		if ( parent->rb_left == node ) {
			other = parent->rb_right;
			if ( other->rb_color == RB_RED ) {
				other->rb_color = RB_BLACK;
				parent->rb_color = RB_RED;
				rb_rotate_left(parent, root);
				other = parent->rb_right;
			}
			if ( (!other->rb_left || other->rb_left->rb_color == RB_BLACK)
			    && (!other->rb_right || other->rb_right->rb_color == RB_BLACK) ) {

				other->rb_color = RB_RED;
				node = parent;
				parent = node->rb_parent;
			}
			else {
				if ( !other->rb_right || other->rb_right->rb_color == RB_BLACK ) {
					register struct rb_node *o_left;
					if ( (o_left = other->rb_left) )
						o_left->rb_color = RB_BLACK;
					other->rb_color = RB_RED;
					rb_rotate_right(other, root);
					other = parent->rb_right;
				}
				other->rb_color = parent->rb_color;
				parent->rb_color = RB_BLACK;
				if ( other->rb_right )
					other->rb_right->rb_color = RB_BLACK;
				rb_rotate_left(parent, root);
				node = root->rb_node;
				break;
			}
		}
		else {
			other = parent->rb_left;
			if ( other->rb_color == RB_RED ) {
				other->rb_color = RB_BLACK;
				parent->rb_color = RB_RED;
				rb_rotate_right(parent, root);
				other = parent->rb_left;
			}
			if ( (!other->rb_left || other->rb_left->rb_color == RB_BLACK)
			    && (!other->rb_right || other->rb_right->rb_color == RB_BLACK) ) {
				other->rb_color = RB_RED;
				node = parent;
				parent = node->rb_parent;
			}
			else {
				if ( !other->rb_left || other->rb_left->rb_color == RB_BLACK ) {
					register struct rb_node *o_right;
					if ( (o_right = other->rb_right) )
						o_right->rb_color = RB_BLACK;
					other->rb_color = RB_RED;
					rb_rotate_left(other, root);
					other = parent->rb_left;
				}
				other->rb_color = parent->rb_color;
				parent->rb_color = RB_BLACK;
				if ( other->rb_left )
					other->rb_left->rb_color = RB_BLACK;
				rb_rotate_right(parent, root);
				node = root->rb_node;
				break;
			}
		}
	}

	if ( node )
		node->rb_color = RB_BLACK;
}


void rb_rotate_left(struct rb_node *node, struct rb_root *root)
{
	struct rb_node *right = node->rb_right;

	if ( (node->rb_right = right->rb_left) )
		right->rb_left->rb_parent = node;
	right->rb_left = node;
	
	if ( (right->rb_parent = node->rb_parent) ) {
		if ( node == node->rb_parent->rb_left )
			node->rb_parent->rb_left = right;
		else
			node->rb_parent->rb_right = right;
	}
	else
		root->rb_node = right;

	node->rb_parent = right;
}


void rb_rotate_right(struct rb_node *node, struct rb_root *root)
{
	struct rb_node *left = node->rb_left;
	
	if ( (node->rb_left = left->rb_right) )
		left->rb_right->rb_parent = node;
	left->rb_right = node;
	
	if ( (left->rb_parent = node->rb_parent) ) {
		if ( node == node->rb_parent->rb_right )
			node->rb_parent->rb_right = left;
		else
			node->rb_parent->rb_left = left;
	}
	else
		root->rb_node = left;

	node->rb_parent = left;
}
