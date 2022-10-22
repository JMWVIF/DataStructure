#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXVEX 100 /* 最大顶点数,应由用户定义 */

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码,如OK等 */
typedef char VertexType; /* 顶点类型应由用户定义 */
typedef int EdgeType; /* 边上的权值类型应由用户定义 */

typedef struct EdgeNode /* 边表结点  */
{
	int adjvex;    /* 邻接点域,存储该顶点对应的下标 */
	EdgeType info;		/* 用于存储权值,对于非网图可以不需要 */
	struct EdgeNode *next; /* 链域,指向下一个邻接点 */
}EdgeNode;

typedef struct VertexNode /* 顶点表结点 */
{
	VertexType data; /* 顶点域,存储顶点信息 */
	EdgeNode *firstedge;/* 边表头指针 */
}VertexNode, AdjList[MAXVEX];					//因为这是数组，所以这里头的就是.而非->
//顶点用一个一维数组来存储，比链表快，且更简单写出来

typedef struct
{
	AdjList adjList;		//由此来让后面的G->adjList
	int numNodes,numEdges; /* 图中当前顶点数和边数 */
}GraphAdjList;

/* 建立图的邻接表结构 */
void  CreateALGraph(GraphAdjList *G)
{
	int i,j,k;
	EdgeNode *e;
	printf("输入顶点数和边数:\n");
	scanf("%d,%d",&G->numNodes,&G->numEdges); /* 输入顶点数和边数 */
	for(i = 0;i < G->numNodes;i++) /* 读入顶点信息,建立顶点表 */
	{
		scanf(&G->adjList[i].data); 	/* 输入顶点信息 */
		G->adjList[i].firstedge=NULL; 	/* 将边表置为空表 */
	}
	
	
	for(k = 0;k < G->numEdges;k++)/* 建立边表 */
	{
		printf("输入边(vi,vj)上的顶点序号:\n");
		scanf("%d,%d",&i,&j); /* 输入边(vi,vj)上的顶点序号 */
		//这里用的是头插法，对于无向图，一条边都是对应两个顶点
		e=(EdgeNode *)malloc(sizeof(EdgeNode)); /* 向内存申请空间,生成边表结点 */
		e->adjvex=j;					/* 邻接序号为j */                         
		e->next=G->adjList[i].firstedge;	/* 将e的指针指向当前顶点上指向的结点 */
		G->adjList[i].firstedge=e;		/* 将当前顶点的指针指向e */               
		
		//几乎完全一致的重复（升维必要）
		e=(EdgeNode *)malloc(sizeof(EdgeNode)); /* 向内存申请空间,生成边表结点 */
		e->adjvex=i;					/* 邻接序号为i */                         
		e->next=G->adjList[j].firstedge;	/* 将e的指针指向当前顶点上指向的结点 */
		G->adjList[j].firstedge=e;		/* 将当前顶点的指针指向e */               
	}
}

int main(void)
{    
	GraphAdjList G;    
	CreateALGraph(&G);
	
	return 0;
}

//对边/弧进行链式存储，就是邻接表。
//目的在于防止浪费过多存储空间，因为邻接矩阵对于稀疏图是很浪费空间的
//实际开发过程中，一般绝大多数是稀疏图，所以日常更用邻接表

//如果想在图中同时获得出度与入度的特性，需要将邻接表和逆邻接表结合起来，构造成十字链表。