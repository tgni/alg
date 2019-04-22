#ifndef __TREE_H__
#define __TREE_H__

#include "types.h"

typedef uint32_t element_t;
struct tree_node_s;


typedef struct tree_node_s position_t;
typedef struct tree_node_s search_tree_t;

extern search_tree_t * make_empty(search_tree_t * t);
extern position_t * find(element_t e, search_tree_t * t);
extern position_t * find_min(search_tree_t * t);
extern position_t * find_max(search_tree_t * t);
extern search_tree_t * insert(element_t e, search_tree_t * t);
extern search_tree_t * delete(element_t e, search_tree_t * t);
extern void print_tree(search_tree_t * t);

#endif /* __TREE_H__ */
