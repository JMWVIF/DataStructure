#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */

#define MAXEDGE 20
#define MAXVEX 20
#define INFINITY 65535

typedef struct
{
	int arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
}MGraph;

typedef struct
{
	int begin;
	int end;
	int weight;
}Edge;   /* 对边集数组Edge结构的定义 */

/* 构建图 */
void CreateMGraph(MGraph *G)
{
	int i, j;

	/* printf("请输入边数和顶点数:"); */
	G->numEdges=15;
	G->numVertexes=9;

	for (i = 0; i < G->numVertexes; i++)/* 初始化图 */
	{
		for ( j = 0; j < G->numVertexes; j++)
		{
			if (i==j)		//矩阵对角线
				G->arc[i][j]=0;
			else
				G->arc[i][j] = G->arc[j][i] = INFINITY;	//初始化权值
		}
	}

	G->arc[0][1]=10;
	G->arc[0][5]=11; 
	G->arc[1][2]=18; 
	G->arc[1][8]=12; 
	G->arc[1][6]=16; 
	G->arc[2][8]=8; 
	G->arc[2][3]=22; 
	G->arc[3][8]=21; 
	G->arc[3][6]=24; 
	G->arc[3][7]=16;
	G->arc[3][4]=20;
	G->arc[4][7]=7; 
	G->arc[4][5]=26; 
	G->arc[5][6]=17; 
	G->arc[6][7]=19; 

	for(i = 0; i < G->numVertexes; i++)
	{
		for(j = i; j < G->numVertexes; j++)
		{
			G->arc[j][i] =G->arc[i][j];		//无向图的镜像操作
		}
	}

}

/* 交换权值 以及头和尾 */
void Swapn(Edge *edges,int i, int j)
{	//头
	int temp;
	temp = edges[i].begin;
	edges[i].begin = edges[j].begin;
	edges[j].begin = temp;
	//尾
	temp = edges[i].end;
	edges[i].end = edges[j].end;
	edges[j].end = temp;
	//权值
	temp = edges[i].weight;
	edges[i].weight = edges[j].weight;
	edges[j].weight = temp;
}

/* 对权值进行排序 */
void sort(Edge edges[],MGraph *G)
{
	int i, j;
	for ( i = 0; i < G->numEdges; i++)
	{
		for ( j = i + 1; j < G->numEdges; j++)
		{
			if (edges[i].weight > edges[j].weight)	//冒泡排序
			{
				Swapn(edges, i, j);
			}
		}
	}
	printf("权排序之后的为:\n");
	for (i = 0; i < G->numEdges; i++)
	{
		printf("(%d, %d) %d\n", edges[i].begin, edges[i].end, edges[i].weight);
	}

}

/* 查找连线顶点的尾部下标 */
int Find(int *parent, int f)
{
	while ( parent[f] > 0)
	{
		f = parent[f];	//仅仅是方便return用
	}
	return f;
}

/* 生成最小生成树 */
void MiniSpanTree_Kruskal(MGraph G)
{
	int i, j, n, m;
	int k = 0;
	int parent[MAXVEX];/* 定义一数组用来判断边与边是否形成环路 */
	
	Edge edges[MAXEDGE];/* 定义边集数组,edge的结构为begin,end,weight,均为整型 */

	/* 用来构建边集数组并排序（冒泡排序）********************* */
	for ( i = 0; i < G.numVertexes-1; i++)
	{
		for (j = i + 1; j < G.numVertexes; j++)
		{
			if (G.arc[i][j]<INFINITY)		
			{//给edges进行赋值，以此收集所有边的数据（头、尾、权值）
			//好方便在另一个冒泡排序中进行排序
				edges[k].begin = i;
				edges[k].end = j;
				edges[k].weight = G.arc[i][j];
				k++;
			}
		}
	}
	sort(edges, &G);//给你冒泡
	/* ******************************************* */


	for (i = 0; i < G.numVertexes; i++)		//先给你初始化
		parent[i] = 0;	/* 初始化数组值为0 */

	printf("打印最小生成树：\n");
	for (i = 0; i < G.numEdges; i++)	/* 循环每一条边 */
	{
		n = Find(parent,edges[i].begin);	//最小的边的头顶点
		m = Find(parent,edges[i].end);		//最小的边的尾顶点
		if (n != m) /* 假如n与m不等，说明此边没有与现有的生成树形成环路 */
		{
			parent[n] = m;	/* 将此边的尾顶点放入下标为起点的parent中。表示此顶点已经在生成树集合中 */  //（收纳进parent[]去）
			//parent数组仅仅只是检测是否形成环路用
			printf("(%d, %d) %d\n", edges[i].begin, edges[i].end, edges[i].weight);
		}
	}
}

int main(void)
{
	MGraph G;
	CreateMGraph(&G);
	MiniSpanTree_Kruskal(G);
	return 0;
}


//Kruskal算法就相当于在上帝视角，先把权值最短的边一个个挑出来
//Kruskal算法适合于稀疏图，Prim算法适合于稠密图（显然克鲁斯卡尔在日常的绝大部分中存在着）
