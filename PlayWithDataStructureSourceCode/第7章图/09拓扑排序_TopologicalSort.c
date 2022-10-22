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

typedef int Status;	/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */

/* �ڽӾ���ṹ */
typedef struct
{
	int vexs[MAXVEX];
	int arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
}MGraph;

/* �ڽӱ�ṹ****************** */
typedef struct EdgeNode /* �߱���  */
{
	int adjvex;    /* �ڽӵ��򣬴洢�ö����Ӧ���±� */
	int weight;		/* ���ڴ洢Ȩֵ�����ڷ���ͼ���Բ���Ҫ */
	struct EdgeNode *next; /* ����ָ����һ���ڽӵ� */
}EdgeNode;

typedef struct VertexNode /* ������� */
{
	int in;	/* ������� */
	int data; /* �����򣬴洢������Ϣ */
	EdgeNode *firstedge;/* �߱�ͷָ�� */
}VertexNode, AdjList[MAXVEX];

typedef struct
{
	AdjList adjList; 
	int numVertexes,numEdges; /* ͼ�е�ǰ�������ͱ��� */
}graphAdjList,*GraphAdjList;
/* **************************** */


void CreateMGraph(MGraph *G)/* ����ͼ */
{
	int i, j;
	
	/* printf("����������Ͷ�����:"); */
	G->numEdges=MAXEDGE;
	G->numVertexes=MAXVEX;

	for (i = 0; i < G->numVertexes; i++)/* ��ʼ��ͼ */
	{
		G->vexs[i]=i;
	}

	for (i = 0; i < G->numVertexes; i++)/* ��ʼ��ͼ */
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

/* �����ڽӾ��󹹽��ڽӱ� */
void CreateALGraph(MGraph G,GraphAdjList *GL)
{
	int i,j;
	EdgeNode *e;

	*GL = (GraphAdjList)malloc(sizeof(graphAdjList));

	(*GL)->numVertexes=G.numVertexes;
	(*GL)->numEdges=G.numEdges;
	for(i= 0;i <G.numVertexes;i++) /* ���붥����Ϣ����������� */
	{
		(*GL)->adjList[i].in=0;
		(*GL)->adjList[i].data=G.vexs[i];
		(*GL)->adjList[i].firstedge=NULL; 	/* ���߱���Ϊ�ձ� */
	}
	
	for(i=0;i<G.numVertexes;i++) /* �����߱� */
	{ 
		for(j=0;j<G.numVertexes;j++)
		{
			if (G.arc[i][j]==1)
			{
				e=(EdgeNode *)malloc(sizeof(EdgeNode));
				e->adjvex=j;					/* �ڽ����Ϊj */                        
				e->next=(*GL)->adjList[i].firstedge;	/* ��e��ָ��ָ�򡾵�ǰ������ָ��Ľ�㡿 */
				(*GL)->adjList[i].firstedge = e;		/* ����ǰ�����ָ��ָ��e */
				//�����δ�������������������Ӳ������
				(*GL)->adjList[j].in++;			//�������++
			}
		}
	}
}


/* ����������GL�޻�·������������������в�����1�����л�·����0�� */
Status TopologicalSort(GraphAdjList GL)
{    
	EdgeNode *e;    
	int i,k,gettop;   
	int top=0;  /* ����ջָ���±� */
	int count=0;/* ����ͳ���������ĸ��� */    
	int *stack;	/* ��ջ�������Ϊ0�Ķ�����ջ */   
	stack=(int *)malloc(GL->numVertexes * sizeof(int));    

	for(i = 0; i < GL->numVertexes; i++)		//�������ж���                
		if(GL->adjList[i].in == 0)	/* �����Ϊ0��ȫ�����㣬��ջ */
			stack[++top]=i;    //��ջ��ջ����1���൱����ջ����������ֵ
	while(top!=0)    //��ջ��������Ԫ��ʱ��ʼ��ѭ��
	//���ѭ�������ö��������ѹ��ջ�У������»���ͼ�еĶ����������٣��Դﵽ���������Ŀ��
	{
		gettop=stack[top--];	//��ȡtopֵ���һ�ȡ֮�˶����ջҪ��1������Ҫ--
		printf("%d -> ",GL->adjList[gettop].data);   //��ӡ�˶���     
		count++;        /* ���i�Ŷ��㣬������ */        
		for(e = GL->adjList[gettop].firstedge; e; e = e->next)  //�Դ˶��㻡�����  
		//e �ȵ��� GL->adjList[gettop].firstedge ; eΪ��ͼ��� ; e��ָ����һ������
		//��Ϊ����ʲ�Ψһ������Ҫѭ�������ҵ����з��ϵĵ�  
		{
			k=e->adjvex;       //k��Ϊe������ڽ����     
			if( !(--GL->adjList[k].in) )  /* ��i�Ŷ�����ڽӵ����ȼ�1�������1��Ϊ0������ջ���Ա��´�ѭ��ʱ��� */                
				stack[++top]=k;      //��ջ  
		}
	}   
	printf("\n");   
	if(count < GL->numVertexes)    //�����������С�����ж�������˵�����ڻ�   
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

//�����������޻����޻�·����ͼ��������ĳЩ�������ܽ�����һ������
//ʱ�临�Ӷ�ΪO(n+e)