#include<cstdio>
#include<iostream>
#include<queue>
#include<algorithm>
#include <string.h>

using namespace std;

#define MAX_VERTEX_NUM 100

int Counter;
int Visit[MAX_VERTEX_NUM]; //标记是否被访问过 
int Num[MAX_VERTEX_NUM];
int Low[MAX_VERTEX_NUM]; //记录从当前顶点通过树边跟一条背向边能达到的最低顶点编号 
int Parent[MAX_VERTEX_NUM];
int isArt[MAX_VERTEX_NUM]; //用于标记是否已经被输出为割点了 

void Init_Globalpara(void)
{
	Counter=1;
	memset(Visit,0,sizeof(Visit));
	memset(Num,0,sizeof(Num));
	memset(Low,0,sizeof(Low));
	memset(Parent,0,sizeof(Parent));
	memset(isArt,0,sizeof(isArt));
}

typedef struct EdgeNode
{
	int adjVertex;
	EdgeNode *nextEdgeNode;
}EdgeNode;

typedef struct VerNode
{
	int data;
	EdgeNode *firstedge;
}VerNode;

typedef struct Graph
{
	VerNode verNode[MAX_VERTEX_NUM];
	int vertex_num,edge_num;
}Graph;

void CreateDAG(Graph &G,int n,int e)
{
	int k;
	char v,i,j;
	G.vertex_num=n;
	G.edge_num=e;
	EdgeNode *p;

	for(k=1;k<=n;k++)
	{
		cin>>v;
		G.verNode[k].data=(v-'A'+1);
		G.verNode[k].firstedge=NULL;
	}
	for(k=1;k<=e;k++) //创建无向图
	{
		cin>>i>>j;

		p=new EdgeNode;
		p->adjVertex=(j-'A'+1);
		p->nextEdgeNode=G.verNode[i-'A'+1].firstedge;
		G.verNode[i-'A'+1].firstedge=p;

		p=new EdgeNode;
		p->adjVertex=(i-'A'+1);
		p->nextEdgeNode=G.verNode[j-'A'+1].firstedge;
		G.verNode[j-'A'+1].firstedge=p;
	}
}

void FindArt(Graph &G,char Vert) //一次DFS搞定，复杂度O(V+E)，前序遍历后序遍历混合使用 
{
	int children=0;
	int Vnum=(Vert-'A'+1);
	EdgeNode *w;
	w=G.verNode[Vnum].firstedge;
	Visit[Vnum]=1;

	Low[Vnum]=Num[Vnum]=Counter++; //CASE1 

	while(w)
	{
		int Wnum=w->adjVertex;
		if(!Visit[Wnum])
		{
			children++;
			Parent[Wnum]=(Vert-'A'+1);
			FindArt(G,char(Wnum-1+'A'));
			//考虑根是否为割点，当且仅当深度优先树的根有不止一个儿子时，根才为节点 
			if(Parent[Vnum]!=0 && Low[Wnum]>=Num[Vnum] && !isArt[Vnum])
			{
				isArt[Vnum]=1;
				cout<<char(Vnum-1+'A')<<" is an articulation point."<<endl;
			}   
			else if(Parent[Vnum]==0 && children>1)
			{
				isArt[Vnum]=1;
				cout<<char(Vnum-1+'A')<<" is an articulation point."<<endl;
			}   
			Low[Vnum]=min(Low[Vnum],Low[Wnum]); //CASE3
		}
		else if(Parent[Vnum]!=char(Wnum-1+'A'))
			Low[Vnum]=min(Low[Vnum],Num[Wnum]); //CASE2
		w=w->nextEdgeNode;
	}
}

int main()
{
	Graph G;
	Init_Globalpara();
	CreateDAG(G,7,8);
	FindArt(G,'A');
}

/**************
  A B C D E F G
  A B
  B C
  C G
  C D
  D E
  E F
  F D
  D A
  输出：
  D is an articulation point.
  C is an articulation point. 
 **************/

