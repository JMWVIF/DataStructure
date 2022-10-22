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
typedef int Boolean; /* Boolean是布尔类型,其值是TRUE或FALSE */

typedef char VertexType; /* 顶点类型应由用户定义 */
typedef int EdgeType; /* 边上的权值类型应由用户定义 */

#define MAXSIZE 9 /* 存储空间初始分配量 */
#define MAXEDGE 15
#define MAXVEX 9
#define INFINITY 0x3f3f3f3f

typedef struct
{
	VertexType vexs[MAXVEX];		/* 顶点表 */
	EdgeType arc[MAXVEX][MAXVEX];	/* 邻接矩阵，可看作边表 */
	int numVertexes, numEdges;		/* 图中当前的顶点数和边数 */ 
}MGraph;

/* 用到的队列结构与函数********************************** */

/* 循环队列的顺序存储结构 */
typedef struct
{
	int data[MAXSIZE];
	int front;    	/* 头指针 */
	int rear;		/* 尾指针，若队列不空，指向队列尾元素的下一个位置 */
}Queue;

/* 初始化一个空队列Q */
Status InitQueue(Queue *Q)
{
	Q->front=0;
	Q->rear=0;
	return  OK;
}

/* 若队列Q为空队列,则返回TRUE,否则返回FALSE */
Status QueueEmpty(Queue Q)
{ 
	if(Q.front==Q.rear) /* 队列空的标志 */
		return TRUE;
	else
		return FALSE;
}

/* 若队列未满，则插入元素e为Q新的队尾元素 */
Status EnQueue(Queue *Q,int e)
{
	if ((Q->rear+1)%MAXSIZE == Q->front)	/* 队列满的判断 */
		return ERROR;
	Q->data[Q->rear]=e;			/* 将元素e赋值给队尾 */
	Q->rear=(Q->rear+1)%MAXSIZE;/* rear指针向后移一位置， */
								/* 若到最后则转到数组头部 */
	return  OK;
}

/* 若队列不空，则删除Q中队头元素，用e返回其值 */
Status DeQueue(Queue *Q,int *e)
{
	if (Q->front == Q->rear)			/* 队列空的判断 */
		return ERROR;
	*e=Q->data[Q->front];				/* 将队头元素赋值给e */
	Q->front=(Q->front+1)%MAXSIZE;	/* front指针向后移一位置， */
									/* 若到最后则转到数组头部 */
	return  OK;
}
/* ****************************************************** */


void CreateMGraph(MGraph *G)
{
	int i, j;

	G->numEdges=15;
	G->numVertexes=9;

	/* 读入顶点信息，建立顶点表 */
	G->vexs[0]='A';
	G->vexs[1]='B';
	G->vexs[2]='C';
	G->vexs[3]='D';
	G->vexs[4]='E';
	G->vexs[5]='F';
	G->vexs[6]='G';
	G->vexs[7]='H';
	G->vexs[8]='I';


	for (i = 0; i < G->numVertexes; i++)/* 初始化图 */	//先全部初始化为0
	{
		for ( j = 0; j < G->numVertexes; j++)
		{
			G->arc[i][j]=0;
		}
	}

	G->arc[0][1]=1;
	G->arc[0][5]=1;

	G->arc[1][2]=1; 
	G->arc[1][8]=1; 
	G->arc[1][6]=1; 
	
	G->arc[2][3]=1; 
	G->arc[2][8]=1; 
	
	G->arc[3][4]=1;
	G->arc[3][7]=1;
	G->arc[3][6]=1;
	G->arc[3][8]=1;

	G->arc[4][5]=1;
	G->arc[4][7]=1;

	G->arc[5][6]=1; 
	
	G->arc[6][7]=1; 

	
	for(i = 0; i < G->numVertexes; i++)
	{
		for(j = i; j < G->numVertexes; j++)
		{
			G->arc[j][i] =G->arc[i][j];		//无向图就是这么搞的
		}
	}

}
///////////////////////////////////////////////////////////////////
Boolean visited[MAXVEX]; /* 访问标志的数组 */
//1. 标识顶点是否被标记过;
//2. 选择从某一个顶点开始(注意:非连通图的情况)
//3. 进入递归,打印i点信息,标识; 边表
//4. [i][j] 是否等于1,若不变，则为遍历过，visited值就为1

/* 邻接矩阵的深度优先递归算法 */		//DFS
void DFS(MGraph G, int i)
{
	int j;
 	visited[i] = TRUE;		//设置为访问过（避免重复）
 	printf("%c ", G.vexs[i]);/* 打印顶点，也可以其它操作 */
	for(j = 0; j < G.numVertexes; j++)
		if(G.arc[i][j] == 1 && !visited[j])		//这条路径可用 && 没有访问过此结点
 			DFS(G, j);/* 对没有访问过的邻接顶点递归调用 */
}

/* 邻接矩阵的深度遍历操作 */
void DFSTraverse(MGraph G)
{
	int i;
 	for(i = 0; i < G.numVertexes; i++)
 		visited[i] = FALSE; /* 初始所有顶点状态都是未访问过状态 */	//初始化
	for(i = 0; i < G.numVertexes; i++)
 		if(!visited[i])		/* 对未访问过的顶点调用DFS，若是连通图，只会执行一次 */ 
			DFS(G, i);		//调用函数，此代码就是跳到148行
}

///////////////////////////////////////////////////////////////////
/* 邻接矩阵的广度遍历算法 */		//BFS
void BFSTraverse(MGraph G)
{
	int i, j;
	Queue Q;
	for(i = 0; i < G.numVertexes; i++)
       	visited[i] = FALSE;
    InitQueue(&Q);		/* 初始化  辅助用的队列 */
    for(i = 0; i < G.numVertexes; i++)  /* 对每一个顶点做循环 */
    {
		if (!visited[i])	/* 若是未访问过就处理 */
		{
			visited[i]=TRUE;		/* 设置当前顶点访问过 */
			printf("%c ", G.vexs[i]);/* 打印顶点，也可以其它操作 */
			EnQueue(&Q,i);		/* 将此顶点入队列 */
			while(!QueueEmpty(Q))	/* 若当前队列不为空 */
			{
				DeQueue(&Q,&i);	/* 将队对元素出队列，赋值给i */
				for(j=0;j<G.numVertexes;j++)	//因为是层序遍历，所以只需要j
				{ 
					if(G.arc[i][j] == 1 && !visited[j])		//其它顶点与当前顶点存在边 && 未访问过
					{ 
 						visited[j]=TRUE;			/* 将找到的此顶点标记为已访问 */
						printf("%c ", G.vexs[j]);	/* 打印顶点 */
						EnQueue(&Q,j);				/* 将找到的此顶点入队列  */
					} 
				} 
			}
		}
	}
}


int main(void)
{    
	MGraph G;
	CreateMGraph(&G);
	printf("\n深度遍历：");
	DFSTraverse(G);
	printf("\n广度遍历：");
	BFSTraverse(G);
	return 0;
}


/*
* DFS其实就是一个递归的过程，以及可以转化为一棵树，对它做前序遍历的过程
* DFS如同先走一条路走到黑，之后从未找过的分支路再进行走
* BFS就是层序遍历，让图转化为树，再把树一层一层遍历出来
* 
* BFS与DFS的时间复杂度都是一样的，都是O(n^2)
* BFS与DFS的不同之处仅仅在于对顶点访问的顺序不同
* 
* DFS更适合目标比较明确，以找到目标为主要目的的情况（深度大成）
* BFS更适合再不断扩大遍历范围，以找到相对最优解的情况（广度大成）
*/