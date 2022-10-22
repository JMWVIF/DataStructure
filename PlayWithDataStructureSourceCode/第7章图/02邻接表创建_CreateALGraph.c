#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXVEX 100 /* ��󶥵���,Ӧ���û����� */

typedef int Status;	/* Status�Ǻ���������,��ֵ�Ǻ������״̬����,��OK�� */
typedef char VertexType; /* ��������Ӧ���û����� */
typedef int EdgeType; /* ���ϵ�Ȩֵ����Ӧ���û����� */

typedef struct EdgeNode /* �߱���  */
{
	int adjvex;    /* �ڽӵ���,�洢�ö����Ӧ���±� */
	EdgeType info;		/* ���ڴ洢Ȩֵ,���ڷ���ͼ���Բ���Ҫ */
	struct EdgeNode *next; /* ����,ָ����һ���ڽӵ� */
}EdgeNode;

typedef struct VertexNode /* ������� */
{
	VertexType data; /* ������,�洢������Ϣ */
	EdgeNode *firstedge;/* �߱�ͷָ�� */
}VertexNode, AdjList[MAXVEX];					//��Ϊ�������飬��������ͷ�ľ���.����->
//������һ��һά�������洢��������죬�Ҹ���д����

typedef struct
{
	AdjList adjList;		//�ɴ����ú����G->adjList
	int numNodes,numEdges; /* ͼ�е�ǰ�������ͱ��� */
}GraphAdjList;

/* ����ͼ���ڽӱ�ṹ */
void  CreateALGraph(GraphAdjList *G)
{
	int i,j,k;
	EdgeNode *e;
	printf("���붥�����ͱ���:\n");
	scanf("%d,%d",&G->numNodes,&G->numEdges); /* ���붥�����ͱ��� */
	for(i = 0;i < G->numNodes;i++) /* ���붥����Ϣ,��������� */
	{
		scanf(&G->adjList[i].data); 	/* ���붥����Ϣ */
		G->adjList[i].firstedge=NULL; 	/* ���߱���Ϊ�ձ� */
	}
	
	
	for(k = 0;k < G->numEdges;k++)/* �����߱� */
	{
		printf("�����(vi,vj)�ϵĶ������:\n");
		scanf("%d,%d",&i,&j); /* �����(vi,vj)�ϵĶ������ */
		//�����õ���ͷ�巨����������ͼ��һ���߶��Ƕ�Ӧ��������
		e=(EdgeNode *)malloc(sizeof(EdgeNode)); /* ���ڴ�����ռ�,���ɱ߱��� */
		e->adjvex=j;					/* �ڽ����Ϊj */                         
		e->next=G->adjList[i].firstedge;	/* ��e��ָ��ָ��ǰ������ָ��Ľ�� */
		G->adjList[i].firstedge=e;		/* ����ǰ�����ָ��ָ��e */               
		
		//������ȫһ�µ��ظ�����ά��Ҫ��
		e=(EdgeNode *)malloc(sizeof(EdgeNode)); /* ���ڴ�����ռ�,���ɱ߱��� */
		e->adjvex=i;					/* �ڽ����Ϊi */                         
		e->next=G->adjList[j].firstedge;	/* ��e��ָ��ָ��ǰ������ָ��Ľ�� */
		G->adjList[j].firstedge=e;		/* ����ǰ�����ָ��ָ��e */               
	}
}

int main(void)
{    
	GraphAdjList G;    
	CreateALGraph(&G);
	
	return 0;
}

//�Ա�/��������ʽ�洢�������ڽӱ�
//Ŀ�����ڷ�ֹ�˷ѹ���洢�ռ䣬��Ϊ�ڽӾ������ϡ��ͼ�Ǻ��˷ѿռ��
//ʵ�ʿ��������У�һ����������ϡ��ͼ�������ճ������ڽӱ�

//�������ͼ��ͬʱ��ó�������ȵ����ԣ���Ҫ���ڽӱ�����ڽӱ��������������ʮ������