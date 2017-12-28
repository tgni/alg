#ifndef _BinHeap_H
#define _BinHeap_H

struct tbl_s {
        int v;
        int dv;
};
typedef struct tbl_s ElementType;
struct HeapStruct;
typedef struct HeapStruct *PriorityQueue;

struct HeapOps {
        void (*MakeEmpty)( PriorityQueue H );
        void (*Insert)( ElementType X, PriorityQueue H );
        ElementType (*DeleteMin)( PriorityQueue H );
        ElementType (*FindMin)( PriorityQueue H );
        int (*IsEmpty)( PriorityQueue H );
        int (*IsFull)( PriorityQueue H );
};

PriorityQueue Initialize( int MaxElements );
void Destroy( PriorityQueue H );
struct HeapOps *RegisterHeapOps(void);
void UnRegisterHeapOps(struct HeapOps *op);
#endif
