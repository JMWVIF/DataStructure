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

#define MAXSIZE 100 /* 存储空间初始分配量 */

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码,如OK等 */
typedef char TElemType;
typedef enum {Link,Thread} PointerTag;
//Link==0表示指向左右孩子指针,Thread==1表示指向前驱或后继的线索	 
typedef  struct BiThrNode	/* 二叉线索存储结点结构 */
{
	TElemType data;	/* 结点数据 */
	struct BiThrNode *lchild, *rchild;	/* 左右孩子指针 */
	PointerTag LTag;	//LTag与RTag只能放0/1，因为是bool值。
	PointerTag RTag;		/* 左右标志 */
	//LTag为0时指向该结点的左孩子，为1时指向该结点的前驱。
	//RTag为0时指向该结点的右孩子，为1时指向该结点的后继。
} BiThrNode, *BiThrTree;

TElemType Nil='#'; /* 字符型以空格符为空 */

Status visit(TElemType e)
{
	printf("%c ",e);
	return OK;
}

/* 按前序输入二叉线索树中结点的值,构造二叉线索树T */
/* 0(整型)/空格(字符型)表示空结点 */
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
		(*T)->data=h; /* 生成根结点(前序) */
		CreateBiThrTree(&(*T)->lchild); /* 递归构造左子树 */
		if((*T)->lchild) /* 有左孩子 */
			(*T)->LTag=Link;	//开指
		CreateBiThrTree(&(*T)->rchild); /* 递归构造右子树 */
		if((*T)->rchild) /* 有右孩子 */
			(*T)->RTag=Link;	//开指
	}
	return OK;
}
//线索二叉树只用中序遍历即可
BiThrTree pre; /* 全局变量,始终指向刚刚访问过的结点 */
/* 中序遍历进行中序线索化 */
void InThreading(BiThrTree p)
{ 
	if(p)
	{
		InThreading(p->lchild); /* 递归左子树线索化 */
		////////////////////////////////////////////////////
		if(!p->lchild) /* 没有左孩子 */	
		{
			p->LTag=Thread; /* 前驱线索 */	//将p->LTag定义为1，完成线索化（指向前驱/后继的线索）
			p->lchild=pre; /* 左孩子指针【指向前驱】 */		//pre赋值给p的左孩子
		}
		if(!pre->rchild) /* 前驱没有右孩子 */
		{
			pre->RTag=Thread; /* 后继线索 */
			pre->rchild=p; /* 前驱右孩子指针【指向后继(当前结点p)】 */
		}
		pre=p; /* 保持pre指向p的前驱，以便下一次使用 */
		////////////////////////////////////////////////////
		//printf("%c",T->data);	//只是将打印结点的功能，改成了线索化的功能
		InThreading(p->rchild); /* 递归右子树线索化 */
	}
}

/* 中序遍历二叉树T,并将其中序线索化,Thrt指向头结点 */
Status InOrderThreading(BiThrTree *Thrt,BiThrTree T)
{ 
	*Thrt=(BiThrTree)malloc(sizeof(BiThrNode));
	if(!*Thrt)
		exit(OVERFLOW);
	(*Thrt)->LTag=Link; /* 建头结点 */		
	(*Thrt)->RTag=Thread;		//后继线索     将(*Thrt)->RTag定义为1，完成线索化（指向前驱/后继的线索）
	(*Thrt)->rchild=(*Thrt); /* 右指针回指 */		//你指我，我就指你
	if(!T) /* 若二叉树空,则左指针回指 */
		(*Thrt)->lchild=*Thrt;					//你指我，我就指你
	else  //二叉树非空时
	{
		(*Thrt)->lchild=T;	//头结点的左孩子就是二叉树T的根结点

		pre=(*Thrt);		/* 保持pre指向(*Thrt)的前驱，以便下一次使用 */		
		InThreading(T); /* 中序遍历进行中序线索化 */						//上下两行为这一行服务
		pre->rchild=*Thrt;		//前驱右孩子指针【指向后继(当前结点*Thrt)】 

		pre->RTag=Thread; /* 最后一个结点线索化 */
		(*Thrt)->rchild=pre;	//右孩子指针【指向前驱】（指回头结点去）
	}
	return OK;
}
//头结点的前驱是整棵树最左的孩子，后继是整棵树最右的孩子


//T指向头结点，头结点左链lchild指向根结点（最左），头结点右链rchild指向中序遍历的最后一个结点（最右）
//中序遍历二叉线索链表表示的二叉树T（一对多起来）
/* 中序遍历二叉线索树T(头结点)的非递归算法 */
Status InOrderTraverse_Thr(BiThrTree T)
{ 
	BiThrTree p;
	p=T->lchild; /* p指向根结点 */	//让p开始遍历
	while(p!=T)	 /* 空树或遍历结束时,p==T */	//一般是整个树都遍历结束时
	{ 
		while(p->LTag==Link)	//一直伸向最左，以最左的结点指向头结点以结束（所以中序遍历打印出来的第一个就是最左结点）
			p=p->lchild;
		if(!visit(p->data)) /* 访问其左子树为空的结点 */
			return ERROR;
		while(p->RTag==Thread && p->rchild!=T)	//最左结点的Rtag就是Thread（1）&& 直到最右为止，都不会返回到头结点上
		{//开始指向后继（也就是中序遍历出来的第二个（最左的父结点））   因为Thread就是后继
			p=p->rchild;	//开始指向右孩子了，这样就导致中序遍历的一步步打印出来
			visit(p->data); /* 访问后继结点 */		//打印后继
		}
		p=p->rchild;
	}
	return OK;
}

int main()
{
	BiThrTree H,T;
	printf("请按前序输入二叉树(如:'ABDH##I##EJ###CF##G##')\n");
 	CreateBiThrTree(&T); /* 按前序产生二叉树 */
	InOrderThreading(&H,T); /* 中序遍历,并中序线索化二叉树 */
	printf("中序遍历(输出)二叉线索树:\n");
	InOrderTraverse_Thr(H); /* 中序遍历(输出)二叉线索树 */
	printf("\n");
	
	return 0;
}


/*
*指向前驱和后继的指针，叫线索
*加上线索的二叉链表，叫线索链表
*如此一对多起来，就是线索二叉树
 
*线索二叉树本质是让空指针域利用起来，改为指向前驱/后继的线索。（你指我我就指回去）
*线索化的过程就是在遍历的过程中修改空指针的过程。
* 
*充分利用了空指针域的空间（省空），只需一次遍历，就能受用到前驱/后继的信息（省时）
*
* 
*在实际问题中，如果所用的二叉树需要【经常遍历】，或者查找结点时需要某种【遍历序列中的前驱/后继】
*那么就用线索二叉树
*/
