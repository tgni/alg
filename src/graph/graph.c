#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "list.h"
#include "queue.h"
#include "binheap.h"
#include "stack.h"

#define KEY(x) (x - 1)
#define Infinity    (0xFFFF)
#define NotAVertex  (-1)

typedef struct eage {
        int32_t left;
        int32_t right;
        uint32_t weight;
        list_head_t node;
} *Eage;

typedef struct record {
        int32_t known;
        int32_t dv;
        int32_t pv;
} *Record;

typedef struct graph {
        int32_t vertices;
        int32_t eages;
        int32_t *indegree;
        struct record *record;
        list_head_t *list;
} *Graph;

struct graph *create_graph(int32_t vertex_num, int32_t eage_num)
{
        struct graph *g; 
        uint32_t i;

        g = (struct graph *)malloc(sizeof(struct graph));

        g->list = (struct list_head *)malloc(sizeof(struct list_head) * vertex_num);
        for (i = 0; i < vertex_num; i++) {
                INIT_LIST_HEAD(&g->list[i]);
        }

        g->indegree = (int32_t *)malloc(sizeof(int32_t) * vertex_num);
        memset(g->indegree, 0, sizeof(int32_t) * vertex_num);

        g->record = (struct record *)malloc(sizeof(struct record) * vertex_num);
        for (i = 0; i < vertex_num; i++) {
                g->record[i].known = FALSE;
                g->record[i].dv = Infinity;
                g->record[i].pv = NotAVertex;
        }

        g->eages = eage_num;
        g->vertices = vertex_num;

        return g;
}

void destroy_graph(struct graph *g)
{
        if (!g)
                return;
        if (g->list)
                free(g->list);
        free(g);
}

void show_graph(struct graph *g)
{
        struct eage *e;
        int32_t i;

        for (i = 0; i < g->vertices; i++) {
                printf("[%d]", i + 1);
                list_for_each_entry(e, &g->list[i], node) {
                        printf(" --> [%d]", e->right);
                }
                printf("\n");
        }
}

struct eage *query_eage(struct graph *g, int32_t u, int32_t v)
{
        struct eage *e;

        list_for_each_entry(e, &g->list[KEY(u)], node) {
                if ((e->left == u) && (e->right == v))
                        return e;
        }
        return NULL;
}
/*
 * add_eage - add eage (u,v) into graph g.
 */
struct eage *add_eage(struct graph *g, int32_t u, int32_t v, uint32_t weight) 
{
        struct eage *e;
        int32_t key;

        e = (struct eage *)malloc(sizeof(struct eage));

        e->left = u;
        e->right = v;
        e->weight = weight;

        key = KEY(u);
	list_add_tail(&e->node, &g->list[key]);

        return e;
}

int32_t remove_eage(struct graph *g, int32_t u, int32_t v)
{
        struct eage *e;
        e = query_eage(g, u, v);
        if (!e)
                return ERROR;

        list_del(&e->node);
        free(e);
        return OK;
}

int32_t create_indegree(struct graph *g)
{
        struct eage *e;
        int32_t i;

        memset(g->indegree, 0, sizeof(int32_t) * g->vertices);
        for (i = 0; i < g->vertices; i++) {
                list_for_each_entry(e, &g->list[i], node) {
                        g->indegree[KEY(e->right)]++;
                }
        }
        return OK;
}

void top_sort(struct graph *g)
{
        Queue q;
        struct eage *e;
        //int32_t top_num[10];
        int32_t counter = 0, v;

        q = CreateQueue(g->vertices);

        for (v = 1; v <= g->vertices; v++)
                if (g->indegree[KEY(v)] == 0)
                        q->Enqueue(v, q);

        printf("top sort: \n");
        while (!q->IsEmpty(q)) {
                v = q->Dequeue(q);        
                //top_num[v] = ++counter;
                printf("v%d ", v);
                list_for_each_entry(e, &g->list[KEY(v)], node) {
                        if (--g->indegree[KEY(e->right)] == 0)
                                q->Enqueue(e->right, q);
                }
        }
        printf("\n");

        DisposeQueue(q);
	return;
}

#if 0
void unweighted(struct graph *g, int32_t s)
{
        Queue q;
        struct QueueOps *op;
        struct eage *e;
        struct record *r;
        struct list_head *h;
        int32_t key, v, w;

        q = CreateQueue(g->vertices);
        op = RegisterQueueOps();
        op->MakeEmpty(q);

        r = g->record; 
        r[KEY(s)].dv = 0;
        op->Enqueue(s, q);

        while (!op->IsEmpty(q)) {
                v = op->FrontAndDequeue(q); 
                r[KEY(v)].known = 1;

                list_for_each_entry(e, h, &g->list[KEY(v)], node) {
                        if (r[KEY(e->right)].dv == Infinity) {
                                r[KEY(e->right)].dv = r[KEY(v)].dv + 1;
                                r[KEY(e->right)].pv = v;
                                op->Enqueue(e->right, q);
                        }
                }
        }
        DisposeQueue(q);
        UnRegisterQueueOps(op);
}
#endif

void BFS(Graph g, int s)
{	
	Queue q;
	Eage e;
	int v;

	printf("%d ", s);
	g->record[KEY(s)].known = TRUE;

	q = CreateQueue(g->vertices);
	q->Enqueue(s, q);

	while (!q->IsEmpty(q)) {
		v = q->Dequeue(q);

		list_for_each_entry(e, &g->list[KEY(v)], node) {
			if (!g->record[KEY(e->right)].known) {
				g->record[KEY(e->right)].known = TRUE;
				printf("%d ", e->right);
				q->Enqueue(e->right, q);
			}
		}
	}

	return;
}

void BFSTraverse(Graph g)
{
	int i;

	printf("BFS: ");
	for (i = 1; i <= g->vertices; ++i)
		g->record[KEY(i)].known = FALSE;


	for (i = 1; i <= g->vertices; ++i) {
		if (!g->record[KEY(i)].known)
			BFS(g, i);
	}
	printf("\n");

	return;
}

void DFS(Graph g, int v)
{
	Eage e;

	printf("%d ", v);	
	g->record[KEY(v)].known = TRUE;
	
	list_for_each_entry(e, &g->list[KEY(v)], node) {
		if (!g->record[KEY(e->right)].known) {
			DFS(g, e->right);
		}
	}
	
	return;
}

void DFSNoRC(Graph g, int v)
{
	Stack s;
	Eage e;
	int k;

	s = CreateStack();

	Push(v, s);
	g->record[KEY(v)].known = TRUE;

	while (!StackIsEmpty(s)) {
		k = Pop(s);
		printf("%d ", k);

		list_for_each_entry(e, &g->list[KEY(v)], node) {
			if (!g->record[KEY(e->right)].known) {
				Push(e->right, s);
				g->record[KEY(e->right)].known = TRUE;
			}
		}
	}

	DisposeStack(s);	

	return;
}


#define RC_MODE		1
#define NONRC_MODE	0
void DFSTraverse(Graph g, int mode)
{
	int i;

	printf("DFS: ");
	for (i = 1; i <= g->vertices; ++i)
		g->record[KEY(i)].known = FALSE;

	for (i = 1; i <= g->vertices; ++i) {
		if (!g->record[KEY(i)].known)
			if (mode) {
				DFS(g, i);
			} else {
				DFSNoRC(g, i);
			}
	}
	printf("\n");

	return;
}

/*
 * Noted Dijkstra Alg.
 */
void Dijkstra(struct graph *g, int32_t s)
{
        int32_t v, w;  
        PriorityQueue q;
        struct tbl_s t;
        struct eage *e;
        struct record *r;

        r = g->record;
        q = Initialize(g->eages);
        g->record[KEY(s)].dv = 0;
        t.v = s;
        t.dv = 0;
        q->Insert(t, q);

        while (!q->IsEmpty(q)) {
                t = q->DeleteMin(q);
                v = t.v;
                //printf("DeleteMin v:%d dv:%d\n", t.v, t.dv);
                if (v == NotAVertex)
                        break;
                r[KEY(v)].known = TRUE;
                list_for_each_entry(e, &g->list[KEY(v)], node) {
                        w = e->right;
                        if (!r[KEY(w)].known) {
                                if (r[KEY(v)].dv + e->weight < r[KEY(w)].dv) {
                                        r[KEY(w)].dv = r[KEY(v)].dv + e->weight;
                                        t.v = w;
                                        t.dv = r[KEY(v)].dv + e->weight;
                                        //printf("Insert w:%d dv:%d\n", t.v, t.dv);
                                        q->Insert(t, q);
                                        r[KEY(w)].pv = v;
                                }
                        }
                }
        }

        Destroy(q);
}

void Prim(struct graph *g, int32_t s)
{
        int32_t v, w;  
        PriorityQueue q;
        struct tbl_s t;
        struct eage *e;
        struct record *r;

        r = g->record;
        q = Initialize(g->eages);
        g->record[KEY(s)].dv = 0;
        t.v = s;
        t.dv = 0;
        q->Insert(t, q);

        while (!q->IsEmpty(q)) {
                t = q->DeleteMin(q);
                v = t.v;
                //printf("DeleteMin v:%d dv:%d\n", t.v, t.dv);
                if (v == NotAVertex)
                        break;
                r[KEY(v)].known = TRUE;
                list_for_each_entry(e, &g->list[KEY(v)], node) {
                        w = e->right;
                        if (!r[KEY(w)].known) {
                                if (e->weight < r[KEY(w)].dv) {
                                        r[KEY(w)].dv = e->weight;
                                        t.v = w;
                                        t.dv = e->weight;
                                        //printf("Insert w:%d dv:%d\n", t.v, t.dv);
                                        q->Insert(t, q);
                                        r[KEY(w)].pv = v;
                                }
                        }
                }
        }
        Destroy(q);
}

/*
 * graph test
 1 -> 2 -> 4 -> 3 
 2 -> 4 -> 5
 3 -> 6
 4 -> 6 -> 7 -> 3
 5 -> 4 -> 7
 6 
 7 -> 6
 */
int32_t graph_test(void)
{
        struct graph *g;
        int32_t e[12][2] = {
                {1,2},{1,4},{1,3},
                {2,4},{2,5},
                {3,6},
                {4,6},{4,7},{4,3},
                {5,4},{5,7},
                {7,6}
        };
        int32_t i;

        g = create_graph(7, 12);
        for (i = 0; i < 12; i++)
                add_eage(g, e[i][0], e[i][1], 1);
        show_graph(g);
	BFSTraverse(g);
	DFSTraverse(g, RC_MODE);
	DFSTraverse(g, NONRC_MODE);
        create_indegree(g);
        top_sort(g);

        return OK;
}

void print_path(int32_t v, struct graph *g)
{
        int32_t i;        
        if (g->record[KEY(v)].pv != NotAVertex) {
                print_path(g->record[KEY(v)].pv, g); 
                printf(" to ");
        }
        printf( "%d", v);
}
/*
 * unweighted test , circle here.
 1 -> 2 -> 4 
 2 -> 4 -> 5
 3 -> 6 -> 1
 4 -> 6 -> 7 -> 3 -> 5
 5 -> 7
 6 
 7 -> 6
 */

int32_t unweighted_test(void)
{
        struct graph *g;
        int32_t e[12][2] = {
                {1,2},{1,4},
                {2,4},{2,5},
                {3,6},{3,1},
                {4,6},{4,7},{4,3},{4,5},
                {5,7},
                {7,6}
        };
        int32_t i;
        g = create_graph(7, 12);
        for (i = 0; i < 12; i++)
                add_eage(g, e[i][0], e[i][1], 1);
        show_graph(g);
        //unweighted(g, 3);
        for (i = 0; i < g->vertices; i++) {
                print_path(i + 1, g);
                printf("\n");
        }
        return OK;
}

/*
 * weighted graph test, circle here: 1->4->3->1
 1 -> 2 -> 4 
 2 -> 4 -> 5
 3 -> 6 -> 1
 4 -> 6 -> 7 -> 3 -> 5
 5 -> 7
 6 
 7 -> 6
 */
int32_t weighted_test(void)
{
        struct graph *g;
        int32_t e[12][3] = {
                {1,2,2},{1,4,1},
                {2,4,3},{2,5,10},
                {3,6,5},{3,1,4},
                {4,6,8},{4,7,4},{4,3,2},{4,5,2},
                {5,7,6},
                {7,6,1}
        };
        int32_t i;

        g = create_graph(7, 12);
        for (i = 0; i < 12; i++)
                add_eage(g, e[i][0], e[i][1], e[i][2]);
        show_graph(g);
        Dijkstra(g, 1);
        for (i = 0; i < g->vertices; i++) {
                print_path(i + 1, g);
                printf("\n");
        }
        return OK;
}

/*
 * undirected graph test
 */
int32_t undirected_graph_test(void)
{
        struct graph *g;
        /*
         * {start, end, weight}
         */
        int32_t e[24][3] = {
                {1,2,2},{1,3,4},{1,4,1},
                {2,1,2},{2,4,3},{2,5,10},
                {3,1,4},{3,4,2},{3,6,5},
                {4,1,1},{4,2,3},{4,3,2},{4,5,7},{4,6,8},{4,7,4},
                {5,2,10},{5,4,7},{5,7,6},
                {6,3,5},{6,4,8},{6,7,1},
                {7,4,4},{7,5,6},{7,6,1}
        };
        int32_t i;

        g = create_graph(7, 24);
        for (i = 0; i < 24; i++)
                add_eage(g, e[i][0], e[i][1], e[i][2]);
        show_graph(g);
        Prim(g, 4);
        for (i = 0; i < g->vertices; i++) {
                print_path(i + 1, g);
                printf("\n");
        }
        return OK;
}
int32_t main(void)
{
	graph_test();
        //weighted_test();
        //undirected_graph_test();
        return OK;
}
