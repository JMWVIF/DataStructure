#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status; 

typedef int QElemType; /* QElemType类型根据实际情况而定，这里假设为int */

typedef struct QNode	/* 结点结构 */	//死记硬背即可
{
   QElemType data;
   struct QNode *next;
}QNode,*QueuePtr;

typedef struct			/* 队列的链表结构 */	//死记硬背即可
{
   QueuePtr front,rear; /* 队头、队尾指针 */	
}LinkQueue;

Status visit(QElemType c)
{
	printf("%d ",c);
	return OK;
}

/* 构造一个空队列Q */
Status InitQueue(LinkQueue *Q)
{ 
	Q->front=Q->rear=(QueuePtr)malloc(sizeof(QNode));	
	//因为是链，所以要用malloc来自动分配空间，以充分发挥链的优势
	if(!Q->front)
		exit(OVERFLOW);
	Q->front->next=NULL;
	return OK;
}

/* 销毁队列Q */
Status DestroyQueue(LinkQueue *Q)
{
	while(Q->front)		//以循环来逐个消除
	{
		 Q->rear=Q->front->next;  //让尾指针成为头指针的下一个地址
		 free(Q->front);		  //删除头指针
		 Q->front=Q->rear;		  //尾指针赋地址给头指针，以便下一次循环时，头紧贴尾
	}
	return OK;
}

/* 将Q清为空队列 */
Status ClearQueue(LinkQueue *Q)
{
	QueuePtr p,q;
	Q->rear=Q->front;		//让头指针与尾指针相同
	p=Q->front->next;		//头指针的下一个就是p
	Q->front->next=NULL;	
	//头指针的下一个变成NULL（防止删删删，忘把这头指针的下一个给删了。因为这是下列循环的死角，需要单独来这个指令去删除）
	while(p)		
	{			//以循环来逐个消除
		 q=p;
		 p=p->next;
		 free(q);
	}
	return OK;
}

/* 若Q为空队列,则返回TRUE,否则返回FALSE */
Status QueueEmpty(LinkQueue Q)
{ 
	if(Q.front==Q.rear)
		return TRUE;
	else
		return FALSE;
}

/* 求队列的长度 */
int QueueLength(LinkQueue Q)
{ 
	int i=0;
	QueuePtr p;
	p=Q.front;
	while(Q.rear!=p)
	{
		 i++;
		 p=p->next;
	}
	return i;
}

/* 若队列不空,则用e返回Q的队头元素,并返回OK,否则返回ERROR */
Status GetHead(LinkQueue Q,QElemType *e)
{ 
	QueuePtr p;
	if(Q.front==Q.rear)
		return ERROR;
	p=Q.front->next;
	*e=p->data;
	return OK;
}


/* 插入元素e为Q的新的队尾元素 */	//入队时，其实就是在链表尾部去插入结点
Status EnQueue(LinkQueue *Q,QElemType e)
{ 
	QueuePtr s=(QueuePtr)malloc(sizeof(QNode));		//s就是新结点（要插入的东西）
	if(!s) /* 存储分配失败 */
		exit(OVERFLOW);		//因存储分配失败而想当然的溢出
	s->data=e;				//*e存data的值
	s->next=NULL;			//毕竟是队尾插入，就要代替原来的队尾，给next做NULL
	Q->rear->next=s;	/* 把拥有元素e的新结点s（要插入的结点）赋值给原队尾结点的next */	  //完成插入动作
	Q->rear=s;		/* 把当前的s设置为队尾结点，rear指向s */		//rear的头衔赋给s（新结点），毕竟你要负当rear的责任
	return OK;
}

/* 若队列不空,删除Q的队头元素,用e返回其值,并返回OK,否则返回ERROR */
Status DeQueue(LinkQueue *Q,QElemType *e)
{
	QueuePtr p;
	if(Q->front==Q->rear)		//队空就没什么好删除的
		return ERROR;
	p=Q->front->next;		/* 将欲删除的队头结点暂存给p */		//B写上欲删除的标记
	//因为是从队头处删除，所以结点的下一个就是要删除的，结点本身还是作为结点（导航标签）来用
	*e=p->data;				/* 将欲删除的队头结点的值赋值给e */
	Q->front->next=p->next;/* 将原队头结点的后继p->next赋值给头结点后继 */    //连接AC
	if(Q->rear==p)		/* 若队头就是队尾，则删除后将rear指向头结点 */	//队头是头结点的下一个结点
		//意思是：若头结点的下一个就是队尾，则删除后将rear指向头结点（造成毁坏的目的）
		Q->rear=Q->front;
	free(p);
	return OK;
}

/* 从队头到队尾依次对队列Q中每个元素输出 */
Status QueueTraverse(LinkQueue Q)
{
	QueuePtr p;
	p=Q.front->next;
	while(p)
	{
		 visit(p->data);
		 p=p->next;
	}
	printf("\n");
	return OK;
}

int main()
{
	int i;
	QElemType d;
	LinkQueue q;
	i=InitQueue(&q);
	if(i)
		printf("成功地构造了一个空队列!\n");
	printf("是否空队列？%d(1:空 0:否)  ",QueueEmpty(q));
	printf("队列的长度为%d\n",QueueLength(q));
	EnQueue(&q,-5);
	EnQueue(&q,5);
	EnQueue(&q,10);
	printf("插入3个元素(-5,5,10)后,队列的长度为%d\n",QueueLength(q));
	printf("是否空队列？%d(1:空 0:否)  ",QueueEmpty(q));
	printf("队列的元素依次为：");
	QueueTraverse(q);
	i=GetHead(q,&d);
	if(i==OK)
	 printf("队头元素是：%d\n",d);
	DeQueue(&q,&d);
	printf("删除了队头元素%d\n",d);
	i=GetHead(q,&d);
	if(i==OK)
		printf("新的队头元素是：%d\n",d);
	ClearQueue(&q);
	printf("清空队列后,q.front=%u q.rear=%u q.front->next=%u\n",q.front,q.rear,q.front->next);
	DestroyQueue(&q);
	printf("销毁队列后,q.front=%u q.rear=%u\n",q.front, q.rear);
	
	return 0;
}

//队列的链式存储结构，其实就是线性表的单链表。
//只不过它只能尾入而头出。这就是链队列

/*
* 顺序队列与链队列：
* 时间上，都是O(1)
* 空间上，循环队列（顺序队列）必须要有一个固定的长度，所以不可避免有着空间浪费的问题
* 而链队列上，则是会有着因为需要一个指针域，会对空间上的开销外，没有其他空间浪费的问题
* 所以链队列更加灵活。
* 
* 如果你知道队列长度的最大值的话，那么就用顺序队列
* 如果无法预估队列长度的最大值的话，那么就用链队列
*/