typedef int ElementType;

#ifndef _AvlTree_H
#define _AvlTree_H

struct AvlNode;
typedef struct AvlNode *Position;
typedef struct AvlNode *AvlTree;

extern AvlTree MakeEmpty( AvlTree T );
extern Position Find( ElementType X, AvlTree T );
extern Position FindMin( AvlTree T );
extern Position FindMax( AvlTree T );
extern AvlTree Insert( ElementType X, AvlTree T );
extern AvlTree LoopInsert( ElementType X, AvlTree T );
extern AvlTree Delete( ElementType X, AvlTree T );
extern ElementType Retrieve( Position P );
extern void ComputeDistAndDepth( AvlTree T );
extern void VPrintAvlTree(AvlTree T);
extern void HPrintAvlTree(AvlTree T);

#endif  /* _AvlTree_H */
