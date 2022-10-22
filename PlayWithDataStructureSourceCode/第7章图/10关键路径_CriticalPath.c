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

typedef int Status;	/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */  

int *etv,*ltv; /* ���¼����緢��ʱ�䡿�͡��¼���ٷ���ʱ�䡿���飬ȫ�ֱ��� */
//��Ϊ�����¼�����Ҫ��*etv֮����*ltv֮ǰ�������ǿ��Եģ�
int *stack2;   /* ���ڴ洢�������е�ջ */
int top2;	   /* ����stack2��ָ�� */

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
	G->numEdges=13;
	G->numVertexes=10;

	for (i = 0; i < G->numVertexes; i++)/* ��ʼ��ͼ */
	{
		G->vexs[i]=i;
	}

	for (i = 0; i < G->numVertexes; i++)/* ��ʼ��ͼ */
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

/* �����ڽӾ��󹹽��ڽӱ� */
void CreateALGraph(MGraph G,GraphAdjList *GL)
{
	int i,j;
	EdgeNode *e;

	*GL = (GraphAdjList)malloc(sizeof(graphAdjList));

	(*GL)->numVertexes=G.numVertexes;
	(*GL)->numEdges=G.numEdges;
	for(i=0;i<G.numVertexes;i++) /* ���붥����Ϣ����������� */
	{
		(*GL)->adjList[i].in=0;
		(*GL)->adjList[i].data=G.vexs[i];
		(*GL)->adjList[i].firstedge=NULL; 	/* ���߱���Ϊ�ձ� */
	}
	
	for(i=0;i<G.numVertexes;i++) /* �����߱� */
	{ 
		for(j=0;j<G.numVertexes;j++)
		{
			if (G.arc[i][j]!=0 && G.arc[i][j]<INFINITY)
			{
				e=(EdgeNode *)malloc(sizeof(EdgeNode));
				e->adjvex=j;					/* �ڽ����Ϊj */   
				e->weight=G.arc[i][j];
				e->next=(*GL)->adjList[i].firstedge;	/* ����ǰ�����ϵ�ָ��Ľ��ָ�븳ֵ��e */
				(*GL)->adjList[i].firstedge=e;		/* ����ǰ�����ָ��ָ��e  */  
				(*GL)->adjList[j].in++;
			}
		}
	}
}


/* �������� */
Status TopologicalSort(GraphAdjList GL)
{    /* ��GL�޻�·������������������в�����1�����л�·����0 */    
	EdgeNode *e;    
	int i,k,gettop;   
	int top=0;  /* ����ջָ���±�  */
	int count=0;/* ����ͳ���������ĸ��� */   
	int *stack;	/* ��ջ�����Ϊ0�Ķ�����ջ  */   
	stack=(int *)malloc(GL->numVertexes * sizeof(int) );    
	for(i = 0; i < GL->numVertexes; i++)                
		if(0 == GL->adjList[i].in) /* �����Ϊ0�Ķ�����ջ */           
			stack[++top]=i;    

	top2=0;    //��ʼ��top2
	etv=(int *)malloc(GL->numVertexes * sizeof(int) ); /* �¼����緢��ʱ������ */    
	for(i=0; i < GL->numVertexes; i++)        
		etv[i]=0;    /* ��ʼ��etv���� */
	stack2=(int *)malloc(GL->numVertexes * sizeof(int) );/* ��ʼ����������ջ(stack2) */

	printf("TopologicalSort:\t");
	while(top!=0)    //��ջ��������Ԫ��ʱ��ʼ��ѭ��
	{        
		gettop=stack[top--];      //��ȡtopֵ���һ�ȡ֮�˶����ջҪ��1������Ҫ--
		printf("%d -> ",GL->adjList[gettop].data);	//��ӡ�˶��� 
		count++;        /* ���i�Ŷ��㣬������ */ 

		stack2[++top2]=gettop;        /* �������Ķ������ѹ���������е�ջ */	//�ڶ���ջ�����������е�ջ
		/* ��¼������������������(�����ж��Ƿ���ڻ�·) */

		for(e = GL->adjList[gettop].firstedge; e; e = e->next)        
		{            
			k=e->adjvex;            
			if( !(--GL->adjList[k].in) )        /* ��i�Ŷ�����ڽӵ����ȼ�1�������1��Ϊ0������ջ */                
				stack[++top]=k; 

			/* ���ĳһ�������ж����ȣ�����¼���Ҫ�ȴ��⼸�������ɲ�����Ч */
			/* �������ж�����и�����·���������ԭ����etv */		//���߱������ִ��
			if((etv[gettop] + e->weight) > etv[k])    /* ��������¼������緢��ʱ��etvֵ */                
				etv[k] = etv[gettop] + e->weight;   
		}    
	}    
	printf("\n");   
	if(count < GL->numVertexes)        
		return ERROR;    
	else       
		return OK;
}

/* ��ؼ�·��,GLΪ�����������G�ĸ���ؼ�� */
void CriticalPath(GraphAdjList GL) 
{    
	EdgeNode *e;    
	int i,gettop,k,j;    
	int ete,lte;  /* ����������緢��ʱ�䡿�͡���ٷ���ʱ�䡿���� */  

	/* ���øĽ������������ */
	/* ���etv����(�¼����緢��ʱ��)��stack2(��������) */
	TopologicalSort(GL);   /* ���������У���������etv��stack2��ֵ */

	/* ��ʼ��ltv(�¼�������ʱ��)��Ϊ����ʱ��(ltv���ɻ�㿪ʼ���Ƶ�) */
	ltv=(int *)malloc(GL->numVertexes*sizeof(int));/* �¼�������ʱ������ */   
	for(i=0; i < GL->numVertexes; i++)
		ltv[i]=etv[GL->numVertexes-1];    /* ��ʼ��ltv��etvջβ��ֵ */
		/* ���ķ���ʱ��(���etv=ltv) */

	printf("etv:\t");   
	for(i=0; i < GL->numVertexes; i++)        
		printf("%d -> ",etv[i]);    
	printf("\n"); 

	/* �ӻ�㵹�Ƽ���ltv */
	while(top2!=0)    /* ��ջ����ltv */    //����ltv
	{        
		gettop=stack2[top2--];  //���������г�ջ������ȳ� ����һ����ջ���ǻ�㣩

		/* �����firstedge����ֱ�ӳ�ջ����һ���� */
		/* ֻ�С��г��ȵĶ��㡿��firstedge�Ų�Ϊ�� */
		for(e = GL->adjList[gettop].firstedge; e; e = e->next)                
		{/* ��������¼�����ٷ���ʱ��ltvֵ */            
			k=e->adjvex;
			/* ���ĳһ�������ж�����ȣ����ڼ���ltvʱ��Ҫѡ��ͨ���⼸��������õ�ltv����Сֵ */
			/* ���û��ѡ�����е���Сֵ����������С��ltv���������ȵ�·�������»����ʱ */
			/* �������ж�����и�С��ltv����������ԭ����ltv�����̿�ʼִ�е�ʱ�䣩 */
			if(ltv[k] - e->weight < ltv[gettop])    //           
				ltv[gettop] = ltv[k] - e->weight;        
		}   
	}    
	
	printf("ltv:\t");   
	for(i=0; i < GL->numVertexes; i++)        
		printf("%d -> ",ltv[i]);    
	printf("\n"); 

	/* ͨ��etv��ltv ��ete��lte��ete��lteֻ�����ǻ��ı������ѣ�ֻ�������翪ʼ����ٿ�ʼ�����ؼ�����ã� */
	for(j=0; j < GL->numVertexes; j++)        /* ��ete,lte�͹ؼ�� */        
	{            
		for(e = GL->adjList[j].firstedge; e; e = e->next)            
		{                
			k=e->adjvex;
			/* ����(�¼�)��etv�����ĳ��ȵĻ�(�)��ete */
			ete = etv[j];        /* ����緢��ʱ�䣨����Ҫ��etv[j]ִ�к���ܿ�ʼ�� */

			/* ��(�)��lte������ָ�����һ������(�¼�)��ltv-����Ȩֵweight */
			lte = ltv[k] - e->weight; /* ���ٷ���ʱ�䣨ʱ�������ƣ����˶��ѣ� */

			/* ete = lte���¼���Ϊ�ؼ�� ���ӳ�Ϊ�ؼ�·�� */
			if(ete == lte)    /* ������ȼ����ڹؼ�·���ϡ���û���κο��� */		//�����¾㱸��ֻǷ���硱                    
				printf("<v%d - v%d> length: %d \n",GL->adjList[j].data,GL->adjList[k].data,e->weight); 
				//����ؼ�·�� 
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


//��һ����ʾ���̵Ĵ�Ȩ����ͼ�У��ö����ʾ�¼���������߱�ʾ����ñ��ϵ�Ȩֵ��ʾ��ĳ���ʱ��
//��������ͼ�ı߱�ʾ�����������AOE��

//AOV���Ƕ����ʾ���������ֻ�����֮�����Լ��ϵ
//AOE�����ñ߱�ʾ����������ϵ�Ȩֵ��ʾ��ĳ���ʱ��

//����AOE����Ҫ�����ڻ֮����Լ��ϵû��ì�ܵĻ����ϵ�