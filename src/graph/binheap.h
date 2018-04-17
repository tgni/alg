#ifndef _BinHeap_H
#define _BinHeap_H

struct tbl_s {
        int v;
        int dv;
};

typedef struct tbl_s HeapElemType;
typedef struct HeapStruct *PriorityQueue;

typedef struct HeapStruct {
        int Capacity;
        int Size;
        HeapElemType *Elements;

        void (*MakeEmpty)( PriorityQueue H );
        void (*Insert)( HeapElemType X, PriorityQueue H );
        HeapElemType (*DeleteMin)( PriorityQueue H );
        HeapElemType (*FindMin)( PriorityQueue H );
        int (*IsEmpty)( PriorityQueue H );
        int (*IsFull)( PriorityQueue H );
} HeapStruct;


PriorityQueue Initialize( int MaxElements );
void Destroy( PriorityQueue H );
#endif
