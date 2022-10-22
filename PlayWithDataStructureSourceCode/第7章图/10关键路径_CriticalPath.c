#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXEDGE 30
#define MAXVEX 30
#define INFINITY 65535

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */  

int *etv,*ltv; /* 【事件最早发生时间】和【事件最迟发生时间】数组，全局变量 */
//因为整个事件必须要在*etv之后，在*ltv之前（包含是可以的）
int *stack2;   /* 用于存储拓扑序列的栈 */
int top2;	   /* 用于stack2的指针 */

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
	G->numEdges=13;
	G->numVertexes=10;

	for (i = 0; i < G->numVertexes; i++)/* 初始化图 */
	{
		G->vexs[i]=i;
	}

	for (i = 0; i < G->numVertexes; i++)/* 初始化图 */
	{
		for ( j = 0; j < G->numVertexes; j++)
		{
			if (i==j)
				G->arc[i][j]=0;
			else
				G->arc[i][j]=INFINITY;
		}
	}

	G->arc[0][1]=3;
	G->arc[0][2]=4; 
	G->arc[1][3]=5; 
	G->arc[1][4]=6; 
	G->arc[2][3]=8; 
	G->arc[2][5]=7; 
	G->arc[3][4]=3;
	G->arc[4][6]=9; 
	G->arc[4][7]=4;
	G->arc[5][7]=6; 
	G->arc[6][9]=2;
	G->arc[7][8]=5;
	G->arc[8][9]=3;

}

/* 利用邻接矩阵构建邻接表 */
void CreateALGraph(MGraph G,GraphAdjList *GL)
{
	int i,j;
	EdgeNode *e;

	*GL = (GraphAdjList)malloc(sizeof(graphAdjList));

	(*GL)->numVertexes=G.numVertexes;
	(*GL)->numEdges=G.numEdges;
	for(i=0;i<G.numVertexes;i++) /* 读入顶点信息，建立顶点表 */
	{
		(*GL)->adjList[i].in=0;
		(*GL)->adjList[i].data=G.vexs[i];
		(*GL)->adjList[i].firstedge=NULL; 	/* 将边表置为空表 */
	}
	
	for(i=0;i<G.numVertexes;i++) /* 建立边表 */
	{ 
		for(j=0;j<G.numVertexes;j++)
		{
			if (G.arc[i][j]!=0 && G.arc[i][j]<INFINITY)
			{
				e=(EdgeNode *)malloc(sizeof(EdgeNode));
				e->adjvex=j;					/* 邻接序号为j */   
				e->weight=G.arc[i][j];
				e->next=(*GL)->adjList[i].firstedge;	/* 将当前顶点上的指向的结点指针赋值给e */
				(*GL)->adjList[i].firstedge=e;		/* 将当前顶点的指针指向e  */  
				(*GL)->adjList[j].in++;
			}
		}
	}
}


/* 拓扑排序 */
Status TopologicalSort(GraphAdjList GL)
{    /* 若GL无回路，则输出拓扑排序序列并返回1，若有回路返回0 */    
	EdgeNode *e;    
	int i,k,gettop;   
	int top=0;  /* 用于栈指针下标  */
	int count=0;/* 用于统计输出顶点的个数 */   
	int *stack;	/* 建栈将入度为0的顶点入栈  */   
	stack=(int *)malloc(GL->numVertexes * sizeof(int) );    
	for(i = 0; i < GL->numVertexes; i++)                
		if(0 == GL->adjList[i].in) /* 将入度为0的顶点入栈 */           
			stack[++top]=i;    

	top2=0;    //初始化top2
	etv=(int *)malloc(GL->numVertexes * sizeof(int) ); /* 事件最早发生时间数组 */    
	for(i=0; i < GL->numVertexes; i++)        
		etv[i]=0;    /* 初始化etv数组 */
	stack2=(int *)malloc(GL->numVertexes * sizeof(int) );/* 初始化拓扑序列栈(stack2) */

	printf("TopologicalSort:\t");
	while(top!=0)    //当栈中有数据元素时，始终循环
	{        
		gettop=stack[top--];      //获取top值，且获取之此顶点后，栈要出1个，故要--
		printf("%d -> ",GL->adjList[gettop].data);	//打印此顶点 
		count++;        /* 输出i号顶点，并计数 */ 

		stack2[++top2]=gettop;        /* 将弹出的顶点序号压入拓扑序列的栈 */	//第二个栈就是拓扑序列的栈
		/* 记录拓扑排序输出顶点个数(用以判断是否存在环路) */

		for(e = GL->adjList[gettop].firstedge; e; e = e->next)        
		{            
			k=e->adjvex;            
			if( !(--GL->adjList[k].in) )        /* 将i号顶点的邻接点的入度减1，如果减1后为0，则入栈 */                
				stack[++top]=k; 

			/* 如果某一个顶点有多个入度，则该事件需要等待这几个活动都完成才能有效 */
			/* 故这里判断如果有更长的路径，则替代原本的etv */		//都具备后才能执行
			if((etv[gettop] + e->weight) > etv[k])    /* 求各顶点事件的最早发生时间etv值 */                
				etv[k] = etv[gettop] + e->weight;   
		}    
	}    
	printf("\n");   
	if(count < GL->numVertexes)        
		return ERROR;    
	else       
		return OK;
}

/* 求关键路径,GL为有向网，输出G的各项关键活动 */
void CriticalPath(GraphAdjList GL) 
{    
	EdgeNode *e;    
	int i,gettop,k,j;    
	int ete,lte;  /* 声明活动【最早发生时间】和【最迟发生时间】变量 */  

	/* 调用改进后的拓扑排序 */
	/* 求出etv数组(事件最早发生时间)和stack2(拓扑序列) */
	TopologicalSort(GL);   /* 求拓扑序列，计算数组etv和stack2的值 */

	/* 初始化ltv(事件最晚发生时间)都为汇点的时间(ltv是由汇点开始倒推的) */
	ltv=(int *)malloc(GL->numVertexes*sizeof(int));/* 事件最晚发生时间数组 */   
	for(i=0; i < GL->numVertexes; i++)
		ltv[i]=etv[GL->numVertexes-1];    /* 初始化ltv成etv栈尾的值 */
		/* 汇点的发生时间(汇点etv=ltv) */

	printf("etv:\t");   
	for(i=0; i < GL->numVertexes; i++)        
		printf("%d -> ",etv[i]);    
	printf("\n"); 

	/* 从汇点倒推计算ltv */
	while(top2!=0)    /* 出栈是求ltv */    //计算ltv
	{        
		gettop=stack2[top2--];  //将拓扑序列出栈，后进先出 （第一个出栈的是汇点）

		/* 汇点无firstedge，故直接出栈的下一个点 */
		/* 只有【有出度的顶点】，firstedge才不为空 */
		for(e = GL->adjList[gettop].firstedge; e; e = e->next)                
		{/* 求各顶点事件的最迟发生时间ltv值 */            
			k=e->adjvex;
			/* 如果某一个顶点有多个出度，则在计算ltv时需要选择通过这几条出度算得的ltv的最小值 */
			/* 如果没有选择其中的最小值，则计算出更小的ltv的那条出度的路径将导致汇点延时 */
			/* 故这里判断如果有更小的ltv结果，则替代原本的ltv（缩短开始执行的时间） */
			if(ltv[k] - e->weight < ltv[gettop])    //           
				ltv[gettop] = ltv[k] - e->weight;        
		}   
	}    
	
	printf("ltv:\t");   
	for(i=0; i < GL->numVertexes; i++)        
		printf("%d -> ",ltv[i]);    
	printf("\n"); 

	/* 通过etv和ltv 求ete和lte（ete与lte只不过是弧的变量而已，只是求最早开始、最迟开始、检测关键活动来用） */
	for(j=0; j < GL->numVertexes; j++)        /* 求ete,lte和关键活动 */        
	{            
		for(e = GL->adjList[j].firstedge; e; e = e->next)            
		{                
			k=e->adjvex;
			/* 顶点(事件)的etv即它的出度的弧(活动)的ete */
			ete = etv[j];        /* 活动最早发生时间（必须要在etv[j]执行后才能开始） */

			/* 弧(活动)的lte即它所指向的下一个顶点(事件)的ltv-弧的权值weight */
			lte = ltv[k] - e->weight; /* 活动最迟发生时间（时间因弧推移，仅此而已） */

			/* ete = lte的事件即为关键活动 连接成为关键路径 */
			if(ete == lte)    /* 两者相等即【在关键路径上】，没有任何空闲 */		//“万事俱备，只欠东风”                    
				printf("<v%d - v%d> length: %d \n",GL->adjList[j].data,GL->adjList[k].data,e->weight); 
				//输出关键路径 
		}        
	}
}


int main(void)
{    
	MGraph G;    
	GraphAdjList GL;    
	CreateMGraph(&G);
	CreateALGraph(G,&GL);
	CriticalPath(GL);
	return 0;
}


//在一个表示工程的带权有向图中，用顶点表示事件，用有向边表示活动，用边上的权值表示活动的持续时间
//这种有向图的边表示活动的网，这是AOE网

//AOV网是顶点表示活动的网，它只描述活动之间的制约关系
//AOE网是用边表示活动的网，边上的权值表示活动的持续时间

//所以AOE网是要建立在活动之间制约关系没有矛盾的基础上的