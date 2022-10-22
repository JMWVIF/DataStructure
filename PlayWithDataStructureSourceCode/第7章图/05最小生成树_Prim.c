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
	int arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
}MGraph;

void CreateMGraph(MGraph *G)/* 构件图 */
{
	int i, j;

	/* printf("请输入边数和顶点数:"); */
	G->numEdges=15;
	G->numVertexes=9;

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
			G->arc[j][i] =G->arc[i][j];
		}
	}

}

/* Prim算法生成最小生成树  */
void MiniSpanTree_Prim(MGraph G)
{
	int min, i, j, k;
	int adjvex[MAXVEX];		/* 保存相关顶点下标 */
	int lowcost[MAXVEX];	/* 保存相关顶点间边的权值 */
	lowcost[0] = 0;/* 初始化第一个权值为0，即v0加入生成树 */		//第一个下标为0，就是从顶点v0开始
			/* lowcost的值为0，在这里就是此下标的顶点已经加入生成树 */
	adjvex[0] = 0;			/* 初始化第一个顶点下标为0 */
	for(i = 1; i < G.numVertexes; i++)	/* 循环除下标为0外的全部顶点 */		//初始化
	{
		lowcost[i] = G.arc[0][i];	/* 将v0顶点与之有边的权值存入数组 */		//让v0能够得着边的，全部打入权值
		adjvex[i] = 0;					/* 初始化都为v0的下标 */			//都为v0的下标，这样才能完成初始化
	}	
	/////////////////////初始化完毕//////////////////////////
	for(i = 1; i < G.numVertexes; i++)
	{
		min = INFINITY;	/* 初始化最小权值为∞，通常设置为不可能的大数字，如0x3f3f3f3f */
		j = 1;
		k = 0;
		while(j < G.numVertexes)	/* 循环全部【顶点】 */		//每次遍历添加一个点
		{
			if(lowcost[j]!=0 && lowcost[j]<min)/* 权值不为0 && 权值小于min */
			{	
				min = lowcost[j];	/* 则让当前权值成为最小值 */	//新的min值
				k = j;			/* 将当前最小值的下标存入k */		//最小的下标给入k里，之后输出k（贪心边的权值）
			}
			j++;	//while循环需要
		}
		printf("(%d, %d)\n", adjvex[k], k);/* 打印当前顶点边中权值最小的边 */	//第一次打印第一条边
		lowcost[k] = 0;/* 将当前顶点的权值设置为0,表示此顶点已经完成任务 */		//完成任务
		for(j = 1; j < G.numVertexes; j++)	/* 循环所有【顶点】 */		//准确而言是v1时循环v1能够得着的，v2时能循环v2能够得着的，以此类推
		{//这一段for循环，不就是【重复】着初始化的写法吗？，只不过是有着【未】加入的条件而已
			if(lowcost[j]!=0 && G.arc[k][j] < lowcost[j])
			{/* 如果下标为k的顶点，其各边权值 < 此前这些【未】被加入生成树权值的顶点 */	
				lowcost[j] = G.arc[k][j];/* 将更小的权值存入lowcost相应位置 */		//替换用
				adjvex[j] = k;				/* 将下标为k的顶点存入adjvex */		//最小的下标给入k里
			}
		}
	}
}

int main(void)
{
	MGraph G;
	CreateMGraph(&G);
	MiniSpanTree_Prim(G);
	return 0;
}

//Prim算法就是简单的贪心算法
//先是集合S={1}，集合V={2，3，4，5，6，7，……}
//之后集合更新为S={1，2}，V={3，4，5，6，7}，并用点2去更新数组
//后面就可以用2来更新与其他点上更短的距离了（若虽然1能直接连，但用2连更短的话）

//时间复杂度为O(n^2)
//Prim与Kruskral只能用无向图

//Prim算法是以某顶点为起点，逐步找各顶点上最小权值的边来构建最小生成树的算法
//Kruskral算法主要对边进行操作，而Prim算法则是对节点进行操作