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
#define MAXVEX 20
#define INFINITY 0x3f3f3f3f 

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */ 


typedef struct
{
	int vexs[MAXVEX];
	int arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
}MGraph;

typedef int Patharc[MAXVEX];    /* 用于存储最短路径下标的数组 */
typedef int ShortPathTable[MAXVEX];/* 用于存储到各点最短路径的权值和 */

/* 构件图 */
void CreateMGraph(MGraph *G)
{
	int i, j;

	/* printf("请输入边数和顶点数:"); */
	G->numEdges=16;
	G->numVertexes=9;

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
				G->arc[i][j] = G->arc[j][i] = INFINITY;
		}
	}

	G->arc[0][1]=1;
	G->arc[0][2]=5; 
	G->arc[1][2]=3; 
	G->arc[1][3]=7; 
	G->arc[1][4]=5; 

	G->arc[2][4]=1; 
	G->arc[2][5]=7; 
	G->arc[3][4]=2; 
	G->arc[3][6]=3; 
	G->arc[4][5]=3;

	G->arc[4][6]=6;
	G->arc[4][7]=9; 
	G->arc[5][7]=5; 
	G->arc[6][7]=2; 
	G->arc[6][8]=7;

	G->arc[7][8]=4;


	for(i = 0; i < G->numVertexes; i++)
	{
		for(j = i; j < G->numVertexes; j++)
		{
			G->arc[j][i] =G->arc[i][j];
		}
	}

}

/* Dijkstra算法，求有向网G的v0顶点到其余顶点v的最短路径P[v]及带权长度D[v] */    
/* P[v]的值为前驱顶点下标,D[v]表示v0到v的最短路径长度和 */  
void ShortestPath_Dijkstra(MGraph G, int v0, Patharc *P, ShortPathTable *D)
{    
	int v,w,k,min;  
	int final[MAXVEX];/* final[w]=1表示求得顶点v0至vw的最短路径 */	
	//final数组是为了v0到某顶点是否已经求得最短路径的标记。如果v0~vw有结果，则final[w]=1
	for(v=0; v < G.numVertexes; v++)    /* 初始化数据 */
	{        
		final[v] = 0;			/* 全部顶点初始化为未知最短路径状态 */
		(*D)[v] = G.arc[v0][v];/* 将与v0点【有连线】的顶点加上权值 */
		(*P)[v] = -1;				/* 初始化路径数组P为-1  */    //-1表示没有路径   
	}

	(*D)[v0] = 0;  /* v0至v0路径为0 */  
	final[v0] = 1;    /* v0至v0不需要求路径 */        
///////////////////////////初始化完成////////////////////////////////

	/* 开始主循环，每次求得v0到某个v顶点的最短路径 */		//所以v从1开始，而不是从0（你从0你不是自己设自己了？）
	for(v=1; v < G.numVertexes; v++)   
	{
		min=INFINITY;    /* 当前所知离v0顶点的最近距离 */    //确保每一次循环时，min都能赋原来走过的路的总和值
		for(w=0; w < G.numVertexes; w++) /* 寻找离v0最近的顶点 */    
		{  
			//这个顶点没有求过路径 && w顶点离v0的距离，比这一次循环里，记录的最小值还要小
			if(!final[w] && (*D)[w]<min)	//(*D)[w]记录着vi走的权值总和           
			{                    
				k=w;               //这个顶点之后就不用求路径了     
				min = (*D)[w];    /* w顶点离v0顶点更近 */	//开始刷新min值
			}        
		}        
		final[k] = 1;    /* 将目前找到的最近的顶点置为1 */	//之后这个顶点就不用求路径了
		for(w=0; w < G.numVertexes; w++) /* 修正当前最短路径及距离 */
		{
			/* 这个顶点没有求过路径 && (经过vi顶点的路径<现在这条路径的长度)*/
			if(!final[w] && (min+G.arc[k][w]<(*D)[w]))   //min+的意思是存储着以前走过的最优解的路
			{ /*  说明找到了更短的路径，修改D[w]和P[w] */
				(*D)[w] = min + G.arc[k][w];  /* 修改当前路径长度 */               
				(*P)[w]=k;        
			}       
		}   
	}
}

int main(void)
{   
	int i,j,v0;
	MGraph G;    
	Patharc P;    
	ShortPathTable D;	 /* 求某点到其余各点的最短路径 */   
	v0=0;
	
	CreateMGraph(&G);
	
	ShortestPath_Dijkstra(G, v0, &P, &D);  

	printf("最短路径倒序如下:\n");    
	for(i=1;i<G.numVertexes;++i)   
	{       
		printf("v%d - v%d : ",v0,i);
		j=i;
		while(P[j]!=-1)
		{
			printf("%d ",P[j]);
			j=P[j];
		}
		printf("\n");
	}    
	printf("\n源点到各顶点的最短路径长度为:\n");  
	for(i=1;i<G.numVertexes;++i)        
		printf("v%d - v%d : %d \n",G.vexs[0],G.vexs[i],D[i]);     
	return 0;
}


//最小生成树只关心所有边的和最小，而最短路径树只搜索权值最小
//最短路径树可以适用于有向图

/*
* Prim算法与Dijkstra算法两者的区别在于：每次更新路径的不一样
Prim更新的是 未标记集合 到 已标记集合 之间的距离
Dijkstra更新的是 源点 到 未标记集合 之间的距离
*/

//Dijkstra算法的时间复杂度为O(n^2)
//如果需要任一顶点到其余所有顶点的最短路径时，那么便再进行一次Dijkstra算法的遍历就行
//当然时间复杂度就是O(n^3)
