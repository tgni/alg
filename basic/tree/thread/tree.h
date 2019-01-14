#ifndef __TREE_H__
#define __TREE_H__

#include "types.h"

typedef struct BiTNode {
	TElemType data;
	struct BiTNode *lchild, *rchild;
	int depth;
} BiTNode, *BiTree;

typedef int32_t (*VisitFn)(void *p);

#endif
