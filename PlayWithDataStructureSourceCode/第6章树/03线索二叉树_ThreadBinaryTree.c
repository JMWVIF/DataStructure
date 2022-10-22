#include "string.h"
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

typedef int Status;	/* Status�Ǻ���������,��ֵ�Ǻ������״̬����,��OK�� */
typedef char TElemType;
typedef enum {Link,Thread} PointerTag;
//Link==0��ʾָ�����Һ���ָ��,Thread==1��ʾָ��ǰ�����̵�����	 
typedef  struct BiThrNode	/* ���������洢���ṹ */
{
	TElemType data;	/* ������� */
	struct BiThrNode *lchild, *rchild;	/* ���Һ���ָ�� */
	PointerTag LTag;	//LTag��RTagֻ�ܷ�0/1����Ϊ��boolֵ��
	PointerTag RTag;		/* ���ұ�־ */
	//LTagΪ0ʱָ��ý������ӣ�Ϊ1ʱָ��ý���ǰ����
	//RTagΪ0ʱָ��ý����Һ��ӣ�Ϊ1ʱָ��ý��ĺ�̡�
} BiThrNode, *BiThrTree;

TElemType Nil='#'; /* �ַ����Կո��Ϊ�� */

Status visit(TElemType e)
{
	printf("%c ",e);
	return OK;
}

/* ��ǰ����������������н���ֵ,�������������T */
/* 0(����)/�ո�(�ַ���)��ʾ�ս�� */
Status CreateBiThrTree(BiThrTree *T)
{ 
	TElemType h;
	scanf("%c",&h);

	if(h==Nil)
		*T=NULL;
	else
	{
		*T=(BiThrTree)malloc(sizeof(BiThrNode));
		if(!*T)
			exit(OVERFLOW);
		(*T)->data=h; /* ���ɸ����(ǰ��) */
		CreateBiThrTree(&(*T)->lchild); /* �ݹ鹹�������� */
		if((*T)->lchild) /* ������ */
			(*T)->LTag=Link;	//��ָ
		CreateBiThrTree(&(*T)->rchild); /* �ݹ鹹�������� */
		if((*T)->rchild) /* ���Һ��� */
			(*T)->RTag=Link;	//��ָ
	}
	return OK;
}
//����������ֻ�������������
BiThrTree pre; /* ȫ�ֱ���,ʼ��ָ��ոշ��ʹ��Ľ�� */
/* ��������������������� */
void InThreading(BiThrTree p)
{ 
	if(p)
	{
		InThreading(p->lchild); /* �ݹ������������� */
		////////////////////////////////////////////////////
		if(!p->lchild) /* û������ */	
		{
			p->LTag=Thread; /* ǰ������ */	//��p->LTag����Ϊ1�������������ָ��ǰ��/��̵�������
			p->lchild=pre; /* ����ָ�롾ָ��ǰ���� */		//pre��ֵ��p������
		}
		if(!pre->rchild) /* ǰ��û���Һ��� */
		{
			pre->RTag=Thread; /* ������� */
			pre->rchild=p; /* ǰ���Һ���ָ�롾ָ����(��ǰ���p)�� */
		}
		pre=p; /* ����preָ��p��ǰ�����Ա���һ��ʹ�� */
		////////////////////////////////////////////////////
		//printf("%c",T->data);	//ֻ�ǽ���ӡ���Ĺ��ܣ��ĳ����������Ĺ���
		InThreading(p->rchild); /* �ݹ������������� */
	}
}

/* �������������T,����������������,Thrtָ��ͷ��� */
Status InOrderThreading(BiThrTree *Thrt,BiThrTree T)
{ 
	*Thrt=(BiThrTree)malloc(sizeof(BiThrNode));
	if(!*Thrt)
		exit(OVERFLOW);
	(*Thrt)->LTag=Link; /* ��ͷ��� */		
	(*Thrt)->RTag=Thread;		//�������     ��(*Thrt)->RTag����Ϊ1�������������ָ��ǰ��/��̵�������
	(*Thrt)->rchild=(*Thrt); /* ��ָ���ָ */		//��ָ�ң��Ҿ�ָ��
	if(!T) /* ����������,����ָ���ָ */
		(*Thrt)->lchild=*Thrt;					//��ָ�ң��Ҿ�ָ��
	else  //�������ǿ�ʱ
	{
		(*Thrt)->lchild=T;	//ͷ�������Ӿ��Ƕ�����T�ĸ����

		pre=(*Thrt);		/* ����preָ��(*Thrt)��ǰ�����Ա���һ��ʹ�� */		
		InThreading(T); /* ��������������������� */						//��������Ϊ��һ�з���
		pre->rchild=*Thrt;		//ǰ���Һ���ָ�롾ָ����(��ǰ���*Thrt)�� 

		pre->RTag=Thread; /* ���һ����������� */
		(*Thrt)->rchild=pre;	//�Һ���ָ�롾ָ��ǰ������ָ��ͷ���ȥ��
	}
	return OK;
}
//ͷ����ǰ��������������ĺ��ӣ���������������ҵĺ���


//Tָ��ͷ��㣬ͷ�������lchildָ�����㣨���󣩣�ͷ�������rchildָ��������������һ����㣨���ң�
//��������������������ʾ�Ķ�����T��һ�Զ�������
/* �����������������T(ͷ���)�ķǵݹ��㷨 */
Status InOrderTraverse_Thr(BiThrTree T)
{ 
	BiThrTree p;
	p=T->lchild; /* pָ������ */	//��p��ʼ����
	while(p!=T)	 /* �������������ʱ,p==T */	//һ��������������������ʱ
	{ 
		while(p->LTag==Link)	//һֱ��������������Ľ��ָ��ͷ����Խ������������������ӡ�����ĵ�һ�����������㣩
			p=p->lchild;
		if(!visit(p->data)) /* ������������Ϊ�յĽ�� */
			return ERROR;
		while(p->RTag==Thread && p->rchild!=T)	//�������Rtag����Thread��1��&& ֱ������Ϊֹ�������᷵�ص�ͷ�����
		{//��ʼָ���̣�Ҳ����������������ĵڶ���������ĸ���㣩��   ��ΪThread���Ǻ��
			p=p->rchild;	//��ʼָ���Һ����ˣ������͵������������һ������ӡ����
			visit(p->data); /* ���ʺ�̽�� */		//��ӡ���
		}
		p=p->rchild;
	}
	return OK;
}

int main()
{
	BiThrTree H,T;
	printf("�밴ǰ�����������(��:'ABDH##I##EJ###CF##G##')\n");
 	CreateBiThrTree(&T); /* ��ǰ����������� */
	InOrderThreading(&H,T); /* �������,������������������ */
	printf("�������(���)����������:\n");
	InOrderTraverse_Thr(H); /* �������(���)���������� */
	printf("\n");
	
	return 0;
}


/*
*ָ��ǰ���ͺ�̵�ָ�룬������
*���������Ķ�����������������
*���һ�Զ���������������������
 
*�����������������ÿ�ָ����������������Ϊָ��ǰ��/��̵�����������ָ���Ҿ�ָ��ȥ��
*�������Ĺ��̾����ڱ����Ĺ������޸Ŀ�ָ��Ĺ��̡�
* 
*��������˿�ָ����Ŀռ䣨ʡ�գ���ֻ��һ�α������������õ�ǰ��/��̵���Ϣ��ʡʱ��
*
* 
*��ʵ�������У�������õĶ�������Ҫ�����������������߲��ҽ��ʱ��Ҫĳ�֡����������е�ǰ��/��̡�
*��ô��������������
*/
