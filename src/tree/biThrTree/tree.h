#ifndef __TREE_H__
#define __TREE_H__

#include "types.h"

typedef enum PointerTag {
	Link,
	Thread
} PointerTag;


typedef struct BiThrNode {
	TElemType data;
	struct BiThrNode *lchild, *rchild;
	PointerTag LTag, RTag;
} BiThrNode, * BiThrTree;

typedef struct BiTNode {
	TElemType data;
	struct BiTNode *lchild, *rchild;
	int depth;
} BiTNode, *BiTree;

typedef int32_t (*VisitFn)(void *p);

#endif
