#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXVEX 100 /* 最大顶点数，应由用户定义 */
#define INFINITY 0x3f3f3f3f

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef char VertexType; /* 顶点类型应由用户定义  */
typedef int EdgeType; /* 边上的权值类型应由用户定义 */
typedef struct
{
	VertexType vexs[MAXVEX]; /* 顶点表 */						//一维数组
	EdgeType arc[MAXVEX][MAXVEX];/* 邻接矩阵，可看作边表 */		//二维数组
	int numNodes, numEdges; /* 图中当前的顶点数和边数  */
}MGraph;

/* 建立无向网图的邻接矩阵表示 */
void CreateMGraph(MGraph *G)
{
	int i,j,k,w;
	printf("输入顶点数和边数:\n");
	scanf("%d,%d",&G->numNodes,&G->numEdges); /* 输入顶点数和边数 */
	for(i = 0;i < G->numNodes;i++) /* 读入顶点信息,建立顶点表 */
		scanf(&G->vexs[i]);										//一维数组
	for(i = 0;i < G->numNodes;i++)
		for(j = 0;j <G->numNodes;j++)
			G->arc[i][j]=INFINITY;	/* 邻接矩阵初始化 */
	for(k = 0;k < G->numEdges;k++) /* 读入numEdges条边，建立邻接矩阵 */
	{
		printf("输入边(vi,vj)上的下标i，下标j和权w:\n");
		scanf("%d,%d,%d",&i,&j,&w); /* 输入边(vi,vj)上的权w */		//二维数组
		G->arc[i][j]=w;				//权以覆写∞
		G->arc[j][i] = G->arc[i][j]; /* 因为是无向图，矩阵对称 */	//有向图就要分开设定上三角/下三角了
	}
}

int main(void)
{    
	MGraph G;    
	CreateMGraph(&G);
	
	return 0;
}

/*
* 在图中的数据元素，是顶点。		不允许空图这样的存在。集合V有穷非空
* 但是边集可以是空的（所有点都互不关联）
* 在图中，若不存在顶点到其自身的边，且同一条边不重复出现，则这样的图叫【简单图】
（不指向自己，也不会有两条重复的路径（有一条无用））。		顶点就是点

* 在无向图中，如果任意两个点都存在边，则整个图就是无向完全图。
* 在有向图中，如果任意两个点都存在方向相反的两条弧，则整个图就是有向完全图。
* 有很少边/弧的图就是稀疏图，反之就是稠密图
* 有些图的边/弧有数字，这个数字称之为权。
* 这种带权的图称为网。
* 
* 路径的长度就是路径上的边/弧的数目。（无权的话）
* 第一个顶点与最后一个顶点相同的路径称为环（也可以称之为回路）
* 序列中顶点不重复的路径称为简单路径（类似一笔画）
* 除了第一个点和最后一个点外，其余顶点不重复出现的回路，就是简单回路/简单环。
* 
* 如果任意两个点都是有桥可搭的，那么就称为是连通图（无向图，如果有向图也是这样的话，那么就是强连通图）
* 无向图中的极大连通子图，称为连通分量（有向图就是强连通分量）
* 
* 无向图中连通且n个顶点，n-1条边，称为生成树。
* 有向图中，一个顶点入度为0，其余顶点入度为1，称为有向树。
* 入度为0只有root结点，入度为1是树的非根结点的双亲只有一个。（只有一个孩子但不是根结点的结点（唯一一个这样的））
* 一个有向图由若干有向树构成生成森林。
*/

//图，不可能用顺序表的形式来存储的，链表也会因度数相差问题而不适合使用，所以只能新开其他的想法。


//邻接矩阵用的是两个数组来表示图。
//一个一维数组存储图中的顶点信息，一个二维数组用来存储图中的边/弧信息