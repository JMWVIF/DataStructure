#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100 /* �洢�ռ��ʼ������ */
#define MAX_TREE_SIZE 100 /* ��������������� */

typedef int Status;		/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef int TElemType;  /* �������������ͣ�Ŀǰ�ݶ�Ϊ���� */
typedef TElemType SqBiTree[MAX_TREE_SIZE]; /* 0�ŵ�Ԫ�洢����� */

typedef struct
{
	int level,order; /* ���Ĳ�,�������(��������������) */
}Position;

//////////////////����˫�ױ�ʾ��//////////////////
typedef struct PTNode {	//���Ľṹ
	TElemType data;		//�������
	int parent;			//˫��λ��
}PTNode;

typedef struct       //���Ľṹ
{
	PTNode nodes[MAX_TREE_SIZE];	//�������
	int r, n;			//����λ��     �����
};
////////////////////////////////////////////////

//////////////////���ĺ��ӱ�ʾ��//////////////////
typedef struct CTNode	//���ӽ��
{
	int child;
	struct CTNode* next;
}*ChildPtr;

typedef struct       //��ͷ�ṹ
{
	TElemType data;
	ChildPtr firstchild;
}CTBox;

typedef struct       //���ṹ
{
	CTBox nodes[MAX_TREE_SIZE];	   //�������
	int r, n;			//����λ��     �����
}CTree;
////////////////////////////////////////////////

//////////////////���ĺ����ֵܱ�ʾ��(��������˶����������ڲ���)//////////////////
typedef struct CSNode	
{
	TElemType data;
	struct CSNode* firstchild,*rightsib;
}CSNode,*CSTree;
///////////////////////////////////////////////////

TElemType Nil=0; /* ��������0Ϊ�� */		//int Nil = 0;

Status visit(TElemType c)
{
	printf("%d ",c);
	return OK;
}

/* ����ն�����T����ΪT�ǹ̶����飬����ı䣬�ʲ���Ҫ& */
Status InitBiTree(SqBiTree T)
{
	int i;
	for(i=0;i<MAX_TREE_SIZE;i++)
		T[i]=Nil; /* ��ֵΪ�� */
	return OK;
}

/* �������������������н���ֵ(�ַ��ͻ�����), ����˳��洢�Ķ�����T */
Status CreateBiTree(SqBiTree T)
{ 
	int i=0;
 	printf("�밴�����������ֵ(����)��0��ʾ�ս�㣬��999�������������%d:\n",MAX_TREE_SIZE);
	while(i<10)
	{
		T[i]=i+1;
		if(i!=0 && T[(i+1)/2-1]==Nil && T[i]!=Nil) /* �˽��(����)��˫�ף��Ҳ��Ǹ� */
			//T[(i+1)/2-1]==Nil    �������û��˫�׵���˼
		{
			printf("������˫�׵ķǸ����%d\n",T[i]);
			exit(ERROR);
		}
		i++;
	}
	while(i<MAX_TREE_SIZE)
	{
		T[i]=Nil; /* ���ո�ֵ��T�ĺ���Ľ�� */
		i++;
	}

	return OK;
}

#define ClearBiTree InitBiTree /* ��˳��洢�ṹ�У���������ȫһ�� */
//������ #define�ķ���ȥ�����������

/* ��ʼ����: ������T���� */
/* �������: ��TΪ�ն�����,�򷵻�TRUE,����FALSE */
Status BiTreeEmpty(SqBiTree T)
{ 
	if(T[0]==Nil) /* �����Ϊ��,������ */
		return TRUE;
	else
		return FALSE;
}

/* ��ʼ����: ������T���ڡ��������: ����T����� */
int BiTreeDepth(SqBiTree T)
{ 
   int i,j=-1;
   for(i=MAX_TREE_SIZE-1;i>=0;i--) /* �ҵ����һ����� */
     if(T[i]!=Nil)
       break;
   i++; 
   do
     j++;
   while(i>=powl(2,j));/* ����2��j���ݡ�*/		 //��Ϊ�Ƕ�������������ѭ�ݵĹ��ɣ������Դ˷�����
   return j;
}

/* ��ʼ����: ������T���� */
/* �������:  ��T����,��e����T�ĸ�,����OK;���򷵻�ERROR,e�޶��� */
Status Root(SqBiTree T,TElemType *e)
{ 
	if(BiTreeEmpty(T)) /* T�� */
		return ERROR;
	else
	{	
		*e=T[0];
		return OK;
	}
}

/* ��ʼ����: ������T����,e��T��ĳ�����(��λ��) */
/* �������: ���ش���λ��e(��,�������)�Ľ���ֵ */
TElemType Value(SqBiTree T,Position e)
{ 
	 return T[(int)powl(2,e.level-1)+e.order-2];		
	 //�����main���Լ������趨���ˣ�ֻ��Ϊ��main��ȶ��õ���ֵ�����
}

/* ��ʼ����: ������T����,e��T��ĳ�����(��λ��) */
/* �������: ������λ��e(��,�������)�Ľ�㸳��ֵvalue */
Status Assign(SqBiTree T,Position e,TElemType value)
{ 
	int i=(int)powl(2,e.level-1)+e.order-2; /* ���㡢�������תΪ�������� */
	//������˫�ײ��գ�Ҷ��e�ղſ��ԣ����Լ�if������
	if(value!=Nil && T[(i+1)/2-1]==Nil) /* ��Ҷ�Ӹ��ǿ�ֵ��˫��Ϊ�� */
		return ERROR;
	else if(value==Nil && (T[i*2+1]!=Nil || T[i*2+2]!=Nil)) /*  ��˫�׸���ֵ����Ҷ�ӣ����գ� */
		return ERROR;
	T[i]=value;
	return OK;
}

/* ��ʼ����: ������T����,e��T��ĳ����� */
/* �������: ��e��T�ķǸ����,�򷵻�����˫��,���򷵻أ��գ� */
TElemType Parent(SqBiTree T,TElemType e)
{ 
	int i;
	if(T[0]==Nil) /* ���� */
		return Nil;
	for(i=1;i<=MAX_TREE_SIZE-1;i++)
		if(T[i]==e) /* �ҵ�e */
			return T[(i+1)/2-1];		//˫��
	return Nil; /* û�ҵ�e */
}


/* ��ʼ����: ������T����,e��T��ĳ����� */
/* �������: ����e�����ӡ���e������,�򷵻أ��գ� */
TElemType LeftChild(SqBiTree T,TElemType e)
{ 
	int i;
	if(T[0]==Nil) /* ���� */
		return Nil;
	for(i=0;i<=MAX_TREE_SIZE-1;i++)
		if(T[i]==e) /* �ҵ�e */
			return T[i*2+1];			//+1��������
	return Nil; /* û�ҵ�e */
}

/* ��ʼ����: ������T����,e��T��ĳ����� */
/* �������: ����e���Һ��ӡ���e���Һ���,�򷵻أ��գ� */
TElemType RightChild(SqBiTree T,TElemType e)
{ 
	int i;
	if(T[0]==Nil) /* ���� */
		return Nil;
	for(i=0;i<=MAX_TREE_SIZE-1;i++)
		if(T[i]==e) /* �ҵ�e */
			return T[i*2+2];			//+2�����Һ���
	return Nil; /* û�ҵ�e */
}

/* ��ʼ����: ������T����,e��T��ĳ����� */
/* �������: ����e�����ֵܡ���e��T�����ӻ������ֵ�,�򷵻أ��գ� */
TElemType LeftSibling(SqBiTree T,TElemType e)
{ 
	int i;
	if(T[0]==Nil) /* ���� */
		return Nil;
	for(i=1;i<=MAX_TREE_SIZE-1;i++)
		if(T[i]==e&&i%2==0) /* �ҵ�e�������Ϊż��(���Һ���) */
			return T[i-1];		//��*2����-1�����ֵ�
	return Nil; /* û�ҵ�e */
}

/* ��ʼ����: ������T����,e��T��ĳ����� */
/* �������: ����e�����ֵܡ���e��T���Һ��ӻ������ֵ�,�򷵻أ��գ� */
TElemType RightSibling(SqBiTree T,TElemType e)
{ 
	int i;
	if(T[0]==Nil) /* ���� */
		return Nil;
	for(i=1;i<=MAX_TREE_SIZE-1;i++)
		if(T[i]==e&&i%2) /* �ҵ�e�������Ϊ����(������) */	 //i%2���Զ���&&����⵽���
			return T[i+1];		//��*2����+1�����ֵ�
	return Nil; /* û�ҵ�e */
}


//˳��������ı�����ȫ�������ģ���Ϊֻ����ȫ�������ŷ��������������������С�

/* PreOrderTraverse()���� */
void PreTraverse(SqBiTree T,int e)
{ 
	visit(T[e]);
	if(T[2*e+1]!=Nil) /* ���������� */
		PreTraverse(T,2*e+1);			//���Եݹ�ʽ����
	if(T[2*e+2]!=Nil) /* ���������� */
		PreTraverse(T,2*e+2);
}

/* ��ʼ����: ���������� */
/* �������: �������T�� */
Status PreOrderTraverse(SqBiTree T)
{ 
	if(!BiTreeEmpty(T)) /* ������ */
	 PreTraverse(T,0);
	printf("\n");
	return OK;
}



/* InOrderTraverse()���� */
void InTraverse(SqBiTree T,int e)
{ 
	if(T[2*e+1]!=Nil) /* ���������� */
		InTraverse(T,2*e+1);
	visit(T[e]);
	if(T[2*e+2]!=Nil) /* ���������� */
		InTraverse(T,2*e+2);
}

/* ��ʼ����: ���������� */
/* �������: �������T�� */
Status InOrderTraverse(SqBiTree T)
{ 
	if(!BiTreeEmpty(T)) /* ������ */
		InTraverse(T,0);
	printf("\n");
	return OK;
}

/* PostOrderTraverse()���� */
void PostTraverse(SqBiTree T,int e)
{ 
	if(T[2*e+1]!=Nil) /* ���������� */
		PostTraverse(T,2*e+1);
	if(T[2*e+2]!=Nil) /* ���������� */
		PostTraverse(T,2*e+2);
	visit(T[e]);
}

/* ��ʼ����: ������T���� */
/* �������: �������T�� */
Status PostOrderTraverse(SqBiTree T)
{ 
	if(!BiTreeEmpty(T)) /* ������ */
		PostTraverse(T,0);
	printf("\n");
	return OK;
}

/* ������������� */
void LevelOrderTraverse(SqBiTree T)
{ 
	int i=MAX_TREE_SIZE-1,j;
	while(T[i]==Nil)
		i--; /* �ҵ����һ���ǿս������ */
	for(j=0;j<=i;j++)  /* �Ӹ������,��������������� */
		if(T[j]!=Nil)
			visit(T[j]); /* ֻ�����ǿյĽ�� */
	printf("\n");
}

/* ��㡢������������������ */
void Print(SqBiTree T)
{ 
	int j,k;
	Position p;
	TElemType e;
	for(j=1;j<=BiTreeDepth(T);j++)
	{
		printf("��%d��: ",j);
		for(k=1;k<=powl(2,j-1);k++)
		{
			p.level=j;
			p.order=k;
			e=Value(T,p);
			if(e!=Nil)
				printf("%d:%d ",k,e);
		}
		printf("\n");
	}
}


int main()
{
	Status i;
	Position p;
	TElemType e;
	SqBiTree T;
	InitBiTree(T);
	CreateBiTree(T);
	printf("������������,���շ�%d(1:�� 0:��) �������=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
	i=Root(T,&e);
	if(i)
		printf("�������ĸ�Ϊ��%d\n",e);
	else
		printf("���գ��޸�\n");
	printf("�������������:\n");
	LevelOrderTraverse(T);
	printf("ǰ�����������:\n");
	PreOrderTraverse(T);
	printf("�������������:\n");
	InOrderTraverse(T);
	printf("�������������:\n");
	PostOrderTraverse(T);
	printf("�޸Ľ��Ĳ��3�������2��");
	p.level=3;
	p.order=2;
	e=Value(T,p);
	printf("���޸Ľ���ԭֵΪ%d��������ֵ:50 ",e);
	e=50;
	Assign(T,p,e);
	printf("ǰ�����������:\n");
	PreOrderTraverse(T);
	printf("���%d��˫��Ϊ%d,���Һ��ӷֱ�Ϊ",e,Parent(T,e));
	printf("%d,%d,�����ֱֵܷ�Ϊ",LeftChild(T,e),RightChild(T,e));
	printf("%d,%d\n",LeftSibling(T,e),RightSibling(T,e));
	ClearBiTree(T);
	printf("�����������,���շ�%d(1:�� 0:��) �������=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
	i=Root(T,&e);
	if(i)
		printf("�������ĸ�Ϊ��%d\n",e);
	else
		printf("���գ��޸�\n");
	
	return 0;
}

/*
* �����������ʣ�
* 1.�ڶ������ĵ�i�������2^(i-1)����㣨i>=1��
* 2.���Ϊk�Ķ������������2^k -1�����(k>=1)
* 3.���κ�һ�Ŷ�����T��������ն˽����Ϊn0����Ϊ2�Ľ����Ϊn2���� n0 = n2 + 1      �ն˽��������Ҷ�������Ⱦ��ǵ�ǰ���ķֲ���
* 4.����n��������ȫ�����������Ϊ[log2n]+1  ��[x]Ϊ������x�����������
* 5.����һ����n���ڵ����ȫ����������˳���ţ�1��i��n������ô�����ڱ��Ϊi��i��1���Ľڵ㣺
	��i=1ʱ���ýڵ�Ϊ��������˫�׽ڵ㡣
	��i>1ʱ���ýڵ��˫�׽ڵ�ı��Ϊi/2��
	��2i��n�����б��Ϊ2i����ڵ㣬����û����ڵ㡣
	��2i+1��n�����б��Ϊ2i+1���ҽڵ㣬����û���ҽڵ㡣
*/

//˳��ṹһ��ֻ��������ȫ����������Ϊ�Ǳ���Ҫ˳��ģ�