#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "types.h"
#include "list.h"
//#include "queue.h"
#include "binheap.h"

#define HASH_KEY(x) (x - 1)
#define Infinity    (0xFFFF)
#define NotAVertex  (-1)

struct eage {
        int32_t left_v;
        int32_t right_v;
        uint32_t weight;
        struct hlist_node h_node;
};

struct record {
        int32_t known; 
        int32_t dv;
        int32_t pv;
};

struct graph {
        int32_t vertices;
        int32_t eages;
        int32_t *indegree;
        struct record *record;
        struct hlist_head *hash;
};

struct graph *create_graph(int32_t vertex_num, int32_t eage_num)
{
        struct graph *g; 
        uint32_t i;

        g = (struct graph *)malloc(sizeof(struct graph));
        assert(g);

        g->hash = (struct hlist_head *)malloc(sizeof(struct hlist_head) * vertex_num);
        assert(g->hash);
        for (i = 0; i < vertex_num; i++) {
                INIT_HLIST_HEAD(&g->hash[i]);
        }

        g->indegree = (int32_t *)malloc(sizeof(int32_t) * vertex_num);
        assert(g->indegree);
        memset(g->indegree, 0, sizeof(int32_t) * vertex_num);

        g->record = (struct record *)malloc(sizeof(struct record) * vertex_num);
        assert(g->record);
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
        if (g->hash)
                free(g->hash);
        free(g);
}

void show_graph(struct graph *g)
{
        struct eage *e;
        struct hlist_node *h;
        int32_t i;

        printf("=======graph=======\n");
        for (i = 0; i < g->vertices; i++) {
                printf("[%d]", i + 1);
                hlist_for_each_entry(e, h, &g->hash[i], h_node) {
                        printf(" -%d-> [%d]", e->weight, e->right_v);
                }
                printf("\n");
        }
}

struct eage *query_eage(struct graph *g, int32_t u, int32_t v)
{
        struct eage *e;
        struct hlist_node *h;

        assert(g);
        assert(u <= g->vertices && v <= g->vertices);
        hlist_for_each_entry(e, h, &g->hash[HASH_KEY(u)], h_node) {
                if ((e->left_v == u) && (e->right_v == v))
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

        assert(g);

        e = (struct eage *)malloc(sizeof(struct eage));
        assert(e);

        e->left_v = u;
        e->right_v = v;
        e->weight = weight;
        INIT_HLIST_NODE(&e->h_node);

        key = HASH_KEY(u);
        if (hlist_empty(&g->hash[key]))
                hlist_add_head(&e->h_node, &g->hash[key]);
        else
                hlist_add_before(&e->h_node, (&g->hash[key])->first);

        return e;
}

int32_t remove_eage(struct graph *g, int32_t u, int32_t v)
{
        struct eage *e;
        e = query_eage(g, u, v);
        if (!e)
                return ERROR;

        hlist_del(&e->h_node);
        free(e);
        return OK;
}

int32_t create_indegree(struct graph *g)
{
        struct eage *e;
        struct hlist_node *h;
        int32_t i;

        assert(g && g->indegree);
        memset(g->indegree, 0, sizeof(int32_t) * g->vertices);
        for (i = 0; i < g->vertices; i++) {
                hlist_for_each_entry(e, h, &g->hash[i], h_node) {
                        g->indegree[HASH_KEY(e->right_v)]++;
                }
        }
        return OK;
}
#if 0
void top_sort(struct graph *g)
{
        Queue q;
        struct QueueOps *op;
        struct eage *e;
        struct hlist_node *h;
        int32_t top_num[10];
        int32_t counter = 0, v;

        q = CreateQueue(g->vertices);
        op = RegisterQueueOps();

        op->MakeEmpty(q);
        for (v = 1; v <= g->vertices; v++)
                if (g->indegree[HASH_KEY(v)] == 0)
                        op->Enqueue(v, q);
        printf("top sort: \n");
        while (!op->IsEmpty(q)) {
                v = op->FrontAndDequeue(q);        
                top_num[v] = ++counter;
                printf("v%d ", v);
                hlist_for_each_entry(e, h, &g->hash[HASH_KEY(v)], h_node) {
                        if (--g->indegree[HASH_KEY(e->right_v)] == 0)
                                op->Enqueue(e->right_v, q);
                }
        }
        printf("\n");

        if (counter != g->vertices)
                assert(0);
        DisposeQueue(q);
        UnRegisterQueueOps(op);
}

void unweighted(struct graph *g, int32_t s)
{
        Queue q;
        struct QueueOps *op;
        struct eage *e;
        struct record *r;
        struct hlist_node *h;
        int32_t key, v, w;

        assert(g && g->record);
        assert(s <= g->vertices);

        q = CreateQueue(g->vertices);
        op = RegisterQueueOps();
        op->MakeEmpty(q);

        r = g->record; 
        r[HASH_KEY(s)].dv = 0;
        op->Enqueue(s, q);

        while (!op->IsEmpty(q)) {
                v = op->FrontAndDequeue(q); 
                r[HASH_KEY(v)].known = 1;

                hlist_for_each_entry(e, h, &g->hash[HASH_KEY(v)], h_node) {
                        if (r[HASH_KEY(e->right_v)].dv == Infinity) {
                                r[HASH_KEY(e->right_v)].dv = r[HASH_KEY(v)].dv + 1;
                                r[HASH_KEY(e->right_v)].pv = v;
                                op->Enqueue(e->right_v, q);
                        }
                }
        }
        DisposeQueue(q);
        UnRegisterQueueOps(op);
}
#endif

/*
 * Noted Dijkstra Alg.
 */
void Dijkstra(struct graph *g, int32_t s)
{
        int32_t v, w;  
        PriorityQueue q;
        struct HeapOps *op;
        struct tbl_s t;
        struct eage *e;
        struct record *r;
        struct hlist_node *h;

        assert(g && g->record);
        assert(s <= g->vertices);

        r = g->record;
        q = Initialize(g->eages);
        op = RegisterHeapOps();
        g->record[HASH_KEY(s)].dv = 0;
        t.v = s;
        t.dv = 0;
        op->Insert(t, q);

        while (!op->IsEmpty(q)) {
                t = op->DeleteMin(q);
                v = t.v;
                printf("DeleteMin v:%d dv:%d\n", t.v, t.dv);
                if (v == NotAVertex)
                        break;
                r[HASH_KEY(v)].known = TRUE;
                hlist_for_each_entry(e, h, &g->hash[HASH_KEY(v)], h_node) {
                        w = e->right_v;
                        if (!r[HASH_KEY(w)].known) {
                                if (r[HASH_KEY(v)].dv + e->weight < r[HASH_KEY(w)].dv) {
                                        r[HASH_KEY(w)].dv = r[HASH_KEY(v)].dv + e->weight;
                                        t.v = w;
                                        t.dv = r[HASH_KEY(v)].dv + e->weight;
                                        printf("Insert w:%d dv:%d\n", t.v, t.dv);
                                        op->Insert(t, q);
                                        r[HASH_KEY(w)].pv = v;
                                }
                        }
                }
        }
        Destroy(q);
        UnRegisterHeapOps(op);
}

void Prim(struct graph *g, int32_t s)
{
        int32_t v, w;  
        PriorityQueue q;
        struct HeapOps *op;
        struct tbl_s t;
        struct eage *e;
        struct record *r;
        struct hlist_node *h;

        assert(g && g->record);
        assert(s <= g->vertices);

        r = g->record;
        q = Initialize(g->eages);
        op = RegisterHeapOps();
        g->record[HASH_KEY(s)].dv = 0;
        t.v = s;
        t.dv = 0;
        op->Insert(t, q);

        while (!op->IsEmpty(q)) {
                t = op->DeleteMin(q);
                v = t.v;
                printf("DeleteMin v:%d dv:%d\n", t.v, t.dv);
                if (v == NotAVertex)
                        break;
                r[HASH_KEY(v)].known = TRUE;
                hlist_for_each_entry(e, h, &g->hash[HASH_KEY(v)], h_node) {
                        w = e->right_v;
                        if (!r[HASH_KEY(w)].known) {
                                if (e->weight < r[HASH_KEY(w)].dv) {
                                        r[HASH_KEY(w)].dv = e->weight;
                                        t.v = w;
                                        t.dv = e->weight;
                                        printf("Insert w:%d dv:%d\n", t.v, t.dv);
                                        op->Insert(t, q);
                                        r[HASH_KEY(w)].pv = v;
                                }
                        }
                }
        }
        Destroy(q);
        UnRegisterHeapOps(op);

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
        assert(g);
        for (i = 0; i < 12; i++)
                add_eage(g, e[i][0], e[i][1], 1);
        show_graph(g);
        create_indegree(g);
        //top_sort(g);

        return OK;
}

void print_path(int32_t v, struct graph *g)
{
        int32_t i;        
        if (g->record[HASH_KEY(v)].pv != NotAVertex) {
                print_path(g->record[HASH_KEY(v)].pv, g); 
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
        assert(g);
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
        assert(g);
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
        assert(g);
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
        //weighted_test();
        undirected_graph_test();
        return OK;
}
