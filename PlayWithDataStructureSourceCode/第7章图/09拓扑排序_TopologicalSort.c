#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXEDGE 20
#define MAXVEX 14
#define INFINITY 65535

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */

/* 邻接矩阵结构 */
typedef struct
{
	int vexs[MAXVEX];
	int arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
}MGraph;

/* 邻接表结构****************** */
typedef struct EdgeNode /* 边表结点  */
{
	int adjvex;    /* 邻接点域，存储该顶点对应的下标 */
	int weight;		/* 用于存储权值，对于非网图可以不需要 */
	struct EdgeNode *next; /* 链域，指向下一个邻接点 */
}EdgeNode;

typedef struct VertexNode /* 顶点表结点 */
{
	int in;	/* 顶点入度 */
	int data; /* 顶点域，存储顶点信息 */
	EdgeNode *firstedge;/* 边表头指针 */
}VertexNode, AdjList[MAXVEX];

typedef struct
{
	AdjList adjList; 
	int numVertexes,numEdges; /* 图中当前顶点数和边数 */
}graphAdjList,*GraphAdjList;
/* **************************** */


void CreateMGraph(MGraph *G)/* 构件图 */
{
	int i, j;
	
	/* printf("请输入边数和顶点数:"); */
	G->numEdges=MAXEDGE;
	G->numVertexes=MAXVEX;

	for (i = 0; i < G->numVertexes; i++)/* 初始化图 */
	{
		G->vexs[i]=i;
	}

	for (i = 0; i < G->numVertexes; i++)/* 初始化图 */
	{
		for ( j = 0; j < G->numVertexes; j++)
		{
			G->arc[i][j]=0;
		}
	}

	G->arc[0][4]=1;
	G->arc[0][5]=1; 
	G->arc[0][11]=1; 
	G->arc[1][2]=1; 
	G->arc[1][4]=1; 
	G->arc[1][8]=1; 
	G->arc[2][5]=1; 
	G->arc[2][6]=1;
	G->arc[2][9]=1;
	G->arc[3][2]=1; 
	G->arc[3][13]=1;
	G->arc[4][7]=1;
	G->arc[5][8]=1;
	G->arc[5][12]=1; 
	G->arc[6][5]=1; 
	G->arc[8][7]=1;
	G->arc[9][10]=1;
	G->arc[9][11]=1;
	G->arc[10][13]=1;
	G->arc[12][9]=1;

}

/* 利用邻接矩阵构建邻接表 */
void CreateALGraph(MGraph G,GraphAdjList *GL)
{
	int i,j;
	EdgeNode *e;

	*GL = (GraphAdjList)malloc(sizeof(graphAdjList));

	(*GL)->numVertexes=G.numVertexes;
	(*GL)->numEdges=G.numEdges;
	for(i= 0;i <G.numVertexes;i++) /* 读入顶点信息，建立顶点表 */
	{
		(*GL)->adjList[i].in=0;
		(*GL)->adjList[i].data=G.vexs[i];
		(*GL)->adjList[i].firstedge=NULL; 	/* 将边表置为空表 */
	}
	
	for(i=0;i<G.numVertexes;i++) /* 建立边表 */
	{ 
		for(j=0;j<G.numVertexes;j++)
		{
			if (G.arc[i][j]==1)
			{
				e=(EdgeNode *)malloc(sizeof(EdgeNode));
				e->adjvex=j;					/* 邻接序号为j */                        
				e->next=(*GL)->adjList[i].firstedge;	/* 将e的指针指向【当前顶点上指向的结点】 */
				(*GL)->adjList[i].firstedge = e;		/* 将当前顶点的指针指向e */
				//上两段代码用来构建链表，死记硬背就行
				(*GL)->adjList[j].in++;			//顶点入度++
			}
		}
	}
}


/* 拓扑排序，若GL无回路，则输出拓扑排序序列并返回1，若有回路返回0。 */
Status TopologicalSort(GraphAdjList GL)
{    
	EdgeNode *e;    
	int i,k,gettop;   
	int top=0;  /* 用于栈指针下标 */
	int count=0;/* 用于统计输出顶点的个数 */    
	int *stack;	/* 建栈，将入度为0的顶点入栈 */   
	stack=(int *)malloc(GL->numVertexes * sizeof(int));    

	for(i = 0; i < GL->numVertexes; i++)		//遍历所有顶点                
		if(GL->adjList[i].in == 0)	/* 将入度为0的全部顶点，入栈 */
			stack[++top]=i;    //入栈，栈顶是1。相当于是栈这个数组里存值
	while(top!=0)    //当栈中有数据元素时，始终循环
	//如此循环，会让顶点逐个被压入栈中，而导致还在图中的顶点数量变少，以达到拓扑排序的目的
	{
		gettop=stack[top--];	//获取top值，且获取之此顶点后，栈要出1个，故要--
		printf("%d -> ",GL->adjList[gettop].data);   //打印此顶点     
		count++;        /* 输出i号顶点，并计数 */        
		for(e = GL->adjList[gettop].firstedge; e; e = e->next)  //对此顶点弧表遍历  
		//e 先等于 GL->adjList[gettop].firstedge ; e为真就继续 ; e再指向下一个顶点
		//因为大概率不唯一，所以要循环才能找到所有符合的点  
		{
			k=e->adjvex;       //k成为e顶点的邻接序号     
			if( !(--GL->adjList[k].in) )  /* 将i号顶点的邻接点的入度减1，如果减1后为0，则入栈，以便下次循环时输出 */                
				stack[++top]=k;      //入栈  
		}
	}   
	printf("\n");   
	if(count < GL->numVertexes)    //当输出顶点数小于所有顶点数，说明存在环   
		return ERROR;    
	else       
		return OK;
}


int main(void)
{    
	MGraph G;  
	GraphAdjList GL; 
	int result;   
	CreateMGraph(&G);
	CreateALGraph(G,&GL);
	result=TopologicalSort(GL);
	printf("result:%d", result);
	return 0;
}

//拓扑排序是无环（无回路）的图。（集合某些条件才能解锁下一条件）
//时间复杂度为O(n+e)