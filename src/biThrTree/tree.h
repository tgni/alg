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


typedef int32_t (*VisitFn)(BiThrNode *p);


#endif
