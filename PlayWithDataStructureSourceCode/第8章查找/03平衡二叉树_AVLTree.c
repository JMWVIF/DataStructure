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

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */ 


/* 二叉树的二叉链表结点结构定义 */
typedef  struct BiTNode	/* 结点结构 */
{
	int data;	/* 结点数据 */
	int bf; /* 结点的平衡因子 */ 
	struct BiTNode *lchild, *rchild;	/* 左右孩子指针 */
} BiTNode, *BiTree;


/* 对以p为根的二叉排序树作右旋处理 */
/* 处理之后p指向新的树根结点，即旋转处理之前的左子树的根结点 */
//步骤：①将A的左孩子B提升为新的根结点；②将原来的根结点A降为B的右孩子；③各子树按大小关系连接(BL和AR不变，BR调整为A的左子树)。
//这个死记硬背即可，代码很死
void R_Rotate(BiTree *P)
{ 
	BiTree L;
	L=(*P)->lchild;			/* L指向P的左子树根结点 */ 
	(*P)->lchild=L->rchild; /* L的右子树挂接为P的左子树 */ 
	L->rchild=(*P);				//P树成为L的右子树
	*P=L;					/* P指向新的根结点 */ 
}

/* 对以P为根的二叉排序树作左旋处理 */
/* 处理之后P指向新的树根结点，即旋转处理之前的右子树的根结点0 */
//步骤：①将A的右孩子B提升为新的根结点；②将原来的根结点A降为B的左孩子；③各子树按大小关系连接(AL和BR不变，BL调整为A的右子树)。
void L_Rotate(BiTree *P)
{ 
	BiTree R;
	R=(*P)->rchild;			/* R指向P的右子树根结点 */ 
	(*P)->rchild=R->lchild; /* R的左子树挂接为P的右子树 */ 
	R->lchild=(*P);				//P树成为R的左子树
	*P=R;					/* P指向新的根结点 */ 
}

#define LH +1 /* 左高 */ 
#define EH 0  /* 等高 */		//equal high 
#define RH -1 /* 右高 */ 

/* 对以指针T所指结点为根的二叉树作左平衡旋转处理 */
/* 本算法结束时，指针T指向新的根结点 */
void LeftBalance(BiTree *T)
{ 
	BiTree L,Lr;
	L=(*T)->lchild; /* L指向T的左子树根结点 */		//L是T的左孩子
	switch(L->bf)		//L的bf值
	{/* 检查T的左子树的平衡度，并作相应平衡处理 */ 
		 case LH: /* 新结点插入在T的左孩子的左子树上，要作单右旋处理 */		//L与根结点的BF值相同，那么改BF后，直接右旋即可
			(*T)->bf=L->bf=EH;		//bf改为0
			R_Rotate(T);
			break;
		 case RH: /* 新结点插入在T的左孩子的右子树上，要作双旋处理 */		//L与根结点的BF值相反，那么改BF后，要双旋（先左后右）
			Lr=L->rchild; /* Lr指向T的左孩子的右子树根 */		//Lr是L的右子树，是T的左子树的右子树
			switch(Lr->bf)
			{ /* 修改T及其左孩子的平衡因子 */		//Lr+L+T=0
				case LH: (*T)->bf=RH;		//Lr为1，那么T为-1，L为0
						 L->bf=EH;
						 break;
				case EH: (*T)->bf=L->bf=EH; //Lr的BF为0，那么T与L的BL也是0
						 break;
				case RH: (*T)->bf=EH;		//Lr为-1，那么T为0，L为1
						 L->bf=LH;
						 break;
			}
			Lr->bf=EH;		//Lr的BF改成0，为了后面的平衡作预处理
			L_Rotate(&(*T)->lchild); /* 对T的左子树（L树）作左旋平衡处理 */		//先左旋，是因为保证T结点与L结点的BF值相同
			R_Rotate(T); /* 对T作右旋平衡处理 */ 
	}
}

/* 对以指针T所指结点为根的二叉树作右平衡旋转处理 */ 
/* 本算法结束时，指针T指向新的根结点 */ 
void RightBalance(BiTree *T)
{ 
	BiTree R,Rl;
	R=(*T)->rchild; /* R指向T的右子树根结点 */ 
	switch(R->bf)
	{ /* 检查T的右子树的平衡度，并作相应平衡处理 */ 
	 case RH: /* 新结点插入在T的右孩子的右子树上，要作单左旋处理 */ 
			  (*T)->bf=R->bf=EH;
			  L_Rotate(T);
			  break;
	 case LH: /* 新结点插入在T的右孩子的左子树上，要作双旋处理 */		//先右再左
			  Rl=R->lchild; /* Rl指向T的右孩子的左子树根 */ 
			  switch(Rl->bf)
			  { /* 修改T及其右孩子的平衡因子 */ 
				case RH: (*T)->bf=LH;
						 R->bf=EH;
						 break;
				case EH: (*T)->bf=R->bf=EH;
						 break;
				case LH: (*T)->bf=EH;
						 R->bf=RH;
						 break;
			  }
			  Rl->bf=EH;
			  R_Rotate(&(*T)->rchild); /* 对T的右子树作右旋平衡处理 */ 
			  L_Rotate(T); /* 对T作左旋平衡处理 */ 
	}
}

/* 若在平衡的二叉排序树T中不存在和e有相同关键字的结点，则插入一个 */ 
/* 数据元素为e的新结点，并返回1，否则返回0。*/ 
/* 若因插入而使二叉排序树失去平衡，则作平衡旋转处理，布尔变量taller反映T长高与否。*/
Status InsertAVL(BiTree *T,int e,Status *taller)
{  
	if(!*T)
	{ /* 插入新结点，树“长高”，置taller为TRUE */ 
		 *T=(BiTree)malloc(sizeof(BiTNode));//T为空时，向内存申请一个结点的空间，以BiTree的结构体出现
		 (*T)->data=e; 
		 (*T)->lchild=(*T)->rchild=NULL;	//为确保稳定性而设NULL
		 (*T)->bf=EH;						//初始化为0
		 *taller=TRUE;
	}
	else
	{
		if (e==(*T)->data)
		{ /* 树中已存在和e有相同关键字的结点则不再插入 */ 
			*taller=FALSE; 
			return FALSE;
		}
		if (e < (*T)->data)
		{ /* 应继续在T的【左子树】中进行搜索 */
			if(!InsertAVL(&(*T)->lchild,e,taller)) /* 未插入 */	
				return FALSE;		//递归调用本函数，直到找到（找到后e成为旧结点），则返回FALSE

			if(*taller) /* 已插入到T的左子树中且左子树“长高” */		//已插入	
				switch((*T)->bf) /* 检查T的平衡度 */ 
				{
					case LH: /* 原本左子树比右子树高，需要作左平衡处理 */ 
							LeftBalance(T);		//双左/双右临门就用函数
							*taller=FALSE; 
							break;
					case EH: /* 原本左、右子树等高，现因左子树增高而使树增高 */ 
//因为插入后T的BF为0或者-1说明新插入的结点没有让整颗二叉树失去平衡性，只需修改T的BF值即可
							(*T)->bf=LH;		//等高以“返祖”
							*taller=TRUE; //树要增高
							break;
					case RH: /* 原本右子树比左子树高，现左、右子树等高 */  
							(*T)->bf=EH;		//左右互抵就设0
							*taller=FALSE; 
							break;
				}
		}
		else    //相当于是if (e > (*T)->data)
		{ /* 应继续在T的【右子树】中进行搜索 */ 
			if(!InsertAVL(&(*T)->rchild,e,taller)) /* 未插入 */ 
				return FALSE;
			if(*taller) /* 已插入到T的右子树且右子树“长高” */ 
				switch((*T)->bf) /* 检查T的平衡度 */ 
				{
					case LH: /* 原本左子树比右子树高，现左、右子树等高 */ 
							(*T)->bf=EH;		//左右互抵就设0
							*taller=FALSE;
							break;
					case EH: /* 原本左、右子树等高，现因右子树增高而使树增高 */
							(*T)->bf=RH;		//等高以“返祖”
							*taller=TRUE; 
							break;
					case RH: /* 原本右子树比左子树高，需要作右平衡处理 */ 
							RightBalance(T);	//双左/双右临门就用函数
							*taller=FALSE; 
							break;
				}
		}
	}
	return TRUE;
}


int main(void)
{    
	int i;
	int a[10]={3,2,1,4,5,6,7,10,9,8};
	BiTree T=NULL;
	Status taller;
	for(i=0;i<10;i++)
	{
		InsertAVL(&T,a[i],&taller);
	}
	printf("本样例建议断点跟踪查看平衡二叉树结构");
	return 0;
}

//平衡二叉树的每一个结点的左子树与右子树高度差<=1，故平衡因子BF只有-1、0、1之分
//平衡二叉树就是AVL树
 
//平衡二叉树的查找、插入、删除的时间复杂度都为O(logn)
//平衡二叉树的查找效率比二叉排序树高很多

//数组、链表->二叉树->平衡二叉树（面试最常用）->红黑树
//平衡二叉树与红黑树用于内存，B树用于磁盘