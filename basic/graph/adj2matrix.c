#define MaxVertexNum	100
typedef char VertexType;
typedef int EdgeType;

typedef struct {
	VertexType Vex[MaxVertexNum];
	EdgeType Edge[MaxVertexNum][MaxVertexNum];
	int vexnum, arcnum;
} MGraph;


typedef struct ArcNode {
	int adjvex;
	struct ArcNode *next;
} ArcNode;

typedef struct VNode {
	VertexType data;
	ArcNode *first;
} VNode, AdjList[MaxVertexNum];

typedef struct {
	AdjList vertices;
	int vexnum, arcnum;
} ALGraph;


void adj2matrix(ALGraph *A, MGraph *M)
{
	int i;
	ArcNode *p;

	for (i = 0; i < A->vexnum; ++i) {
		p = A->vertices[i].first;

		while (p) {
			M->Edge[i][p->data] = 1;
			p = p->next;
		}
	}

	M.vexnum = A->vexnum;
	M.arcnum = A->arcnum;

	return;
}
