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
#define MAX_TREE_SIZE 100 /* 二叉树的最大结点数 */

typedef int Status;		/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int TElemType;  /* 树结点的数据类型，目前暂定为整型 */
typedef TElemType SqBiTree[MAX_TREE_SIZE]; /* 0号单元存储根结点 */

typedef struct
{
	int level,order; /* 结点的层,本层序号(按满二叉树计算) */
}Position;

//////////////////树的双亲表示法//////////////////
typedef struct PTNode {	//结点的结构
	TElemType data;		//结点数据
	int parent;			//双亲位置
}PTNode;

typedef struct       //树的结构
{
	PTNode nodes[MAX_TREE_SIZE];	//结点数组
	int r, n;			//根的位置     结点数
};
////////////////////////////////////////////////

//////////////////树的孩子表示法//////////////////
typedef struct CTNode	//孩子结点
{
	int child;
	struct CTNode* next;
}*ChildPtr;

typedef struct       //表头结构
{
	TElemType data;
	ChildPtr firstchild;
}CTBox;

typedef struct       //树结构
{
	CTBox nodes[MAX_TREE_SIZE];	   //结点数组
	int r, n;			//根的位置     结点数
}CTree;
////////////////////////////////////////////////

//////////////////树的孩子兄弟表示法(让树变成了二叉树，便于查找)//////////////////
typedef struct CSNode	
{
	TElemType data;
	struct CSNode* firstchild,*rightsib;
}CSNode,*CSTree;
///////////////////////////////////////////////////

TElemType Nil=0; /* 设整型以0为空 */		//int Nil = 0;

Status visit(TElemType c)
{
	printf("%d ",c);
	return OK;
}

/* 构造空二叉树T。因为T是固定数组，不会改变，故不需要& */
Status InitBiTree(SqBiTree T)
{
	int i;
	for(i=0;i<MAX_TREE_SIZE;i++)
		T[i]=Nil; /* 初值为空 */
	return OK;
}

/* 按层序次序输入二叉树中结点的值(字符型或整型), 构造顺序存储的二叉树T */
Status CreateBiTree(SqBiTree T)
{ 
	int i=0;
 	printf("请按层序输入结点的值(整型)，0表示空结点，输999结束。结点数≤%d:\n",MAX_TREE_SIZE);
	while(i<10)
	{
		T[i]=i+1;
		if(i!=0 && T[(i+1)/2-1]==Nil && T[i]!=Nil) /* 此结点(不空)无双亲，且不是根 */
			//T[(i+1)/2-1]==Nil    这个就是没有双亲的意思
		{
			printf("出现无双亲的非根结点%d\n",T[i]);
			exit(ERROR);
		}
		i++;
	}
	while(i<MAX_TREE_SIZE)
	{
		T[i]=Nil; /* 将空赋值给T的后面的结点 */
		i++;
	}

	return OK;
}

#define ClearBiTree InitBiTree /* 在顺序存储结构中，两函数完全一样 */
//可以用 #define的方法去复制这个函数

/* 初始条件: 二叉树T存在 */
/* 操作结果: 若T为空二叉树,则返回TRUE,否则FALSE */
Status BiTreeEmpty(SqBiTree T)
{ 
	if(T[0]==Nil) /* 根结点为空,则树空 */
		return TRUE;
	else
		return FALSE;
}

/* 初始条件: 二叉树T存在。操作结果: 返回T的深度 */
int BiTreeDepth(SqBiTree T)
{ 
   int i,j=-1;
   for(i=MAX_TREE_SIZE-1;i>=0;i--) /* 找到最后一个结点 */
     if(T[i]!=Nil)
       break;
   i++; 
   do
     j++;
   while(i>=powl(2,j));/* 计算2的j次幂。*/		 //因为是二叉树，所以遵循幂的规律，所以以此反利用
   return j;
}

/* 初始条件: 二叉树T存在 */
/* 操作结果:  当T不空,用e返回T的根,返回OK;否则返回ERROR,e无定义 */
Status Root(SqBiTree T,TElemType *e)
{ 
	if(BiTreeEmpty(T)) /* T空 */
		return ERROR;
	else
	{	
		*e=T[0];
		return OK;
	}
}

/* 初始条件: 二叉树T存在,e是T中某个结点(的位置) */
/* 操作结果: 返回处于位置e(层,本层序号)的结点的值 */
TElemType Value(SqBiTree T,Position e)
{ 
	 return T[(int)powl(2,e.level-1)+e.order-2];		
	 //这个在main里自己给你设定好了，只是为了main里既定好的数值而输出
}

/* 初始条件: 二叉树T存在,e是T中某个结点(的位置) */
/* 操作结果: 给处于位置e(层,本层序号)的结点赋新值value */
Status Assign(SqBiTree T,Position e,TElemType value)
{ 
	int i=(int)powl(2,e.level-1)+e.order-2; /* 将层、本层序号转为矩阵的序号 */
	//必须是双亲不空，叶子e空才可以，所以加if的条件
	if(value!=Nil && T[(i+1)/2-1]==Nil) /* 给叶子赋非空值但双亲为空 */
		return ERROR;
	else if(value==Nil && (T[i*2+1]!=Nil || T[i*2+2]!=Nil)) /*  给双亲赋空值但有叶子（不空） */
		return ERROR;
	T[i]=value;
	return OK;
}

/* 初始条件: 二叉树T存在,e是T中某个结点 */
/* 操作结果: 若e是T的非根结点,则返回它的双亲,否则返回＂空＂ */
TElemType Parent(SqBiTree T,TElemType e)
{ 
	int i;
	if(T[0]==Nil) /* 空树 */
		return Nil;
	for(i=1;i<=MAX_TREE_SIZE-1;i++)
		if(T[i]==e) /* 找到e */
			return T[(i+1)/2-1];		//双亲
	return Nil; /* 没找到e */
}


/* 初始条件: 二叉树T存在,e是T中某个结点 */
/* 操作结果: 返回e的左孩子。若e无左孩子,则返回＂空＂ */
TElemType LeftChild(SqBiTree T,TElemType e)
{ 
	int i;
	if(T[0]==Nil) /* 空树 */
		return Nil;
	for(i=0;i<=MAX_TREE_SIZE-1;i++)
		if(T[i]==e) /* 找到e */
			return T[i*2+1];			//+1就是左孩子
	return Nil; /* 没找到e */
}

/* 初始条件: 二叉树T存在,e是T中某个结点 */
/* 操作结果: 返回e的右孩子。若e无右孩子,则返回＂空＂ */
TElemType RightChild(SqBiTree T,TElemType e)
{ 
	int i;
	if(T[0]==Nil) /* 空树 */
		return Nil;
	for(i=0;i<=MAX_TREE_SIZE-1;i++)
		if(T[i]==e) /* 找到e */
			return T[i*2+2];			//+2就是右孩子
	return Nil; /* 没找到e */
}

/* 初始条件: 二叉树T存在,e是T中某个结点 */
/* 操作结果: 返回e的左兄弟。若e是T的左孩子或无左兄弟,则返回＂空＂ */
TElemType LeftSibling(SqBiTree T,TElemType e)
{ 
	int i;
	if(T[0]==Nil) /* 空树 */
		return Nil;
	for(i=1;i<=MAX_TREE_SIZE-1;i++)
		if(T[i]==e&&i%2==0) /* 找到e且其序号为偶数(是右孩子) */
			return T[i-1];		//不*2反倒-1是左兄弟
	return Nil; /* 没找到e */
}

/* 初始条件: 二叉树T存在,e是T中某个结点 */
/* 操作结果: 返回e的右兄弟。若e是T的右孩子或无右兄弟,则返回＂空＂ */
TElemType RightSibling(SqBiTree T,TElemType e)
{ 
	int i;
	if(T[0]==Nil) /* 空树 */
		return Nil;
	for(i=1;i<=MAX_TREE_SIZE-1;i++)
		if(T[i]==e&&i%2) /* 找到e且其序号为奇数(是左孩子) */	 //i%2而自动被&&所检测到真假
			return T[i+1];		//不*2反倒+1是右兄弟
	return Nil; /* 没找到e */
}


//顺序二叉树的遍历完全就是死的，因为只有完全二叉树才符合条件，死背下来就行。

/* PreOrderTraverse()调用 */
void PreTraverse(SqBiTree T,int e)
{ 
	visit(T[e]);
	if(T[2*e+1]!=Nil) /* 左子树不空 */
		PreTraverse(T,2*e+1);			//无脑递归式遍历
	if(T[2*e+2]!=Nil) /* 右子树不空 */
		PreTraverse(T,2*e+2);
}

/* 初始条件: 二叉树存在 */
/* 操作结果: 先序遍历T。 */
Status PreOrderTraverse(SqBiTree T)
{ 
	if(!BiTreeEmpty(T)) /* 树不空 */
	 PreTraverse(T,0);
	printf("\n");
	return OK;
}



/* InOrderTraverse()调用 */
void InTraverse(SqBiTree T,int e)
{ 
	if(T[2*e+1]!=Nil) /* 左子树不空 */
		InTraverse(T,2*e+1);
	visit(T[e]);
	if(T[2*e+2]!=Nil) /* 右子树不空 */
		InTraverse(T,2*e+2);
}

/* 初始条件: 二叉树存在 */
/* 操作结果: 中序遍历T。 */
Status InOrderTraverse(SqBiTree T)
{ 
	if(!BiTreeEmpty(T)) /* 树不空 */
		InTraverse(T,0);
	printf("\n");
	return OK;
}

/* PostOrderTraverse()调用 */
void PostTraverse(SqBiTree T,int e)
{ 
	if(T[2*e+1]!=Nil) /* 左子树不空 */
		PostTraverse(T,2*e+1);
	if(T[2*e+2]!=Nil) /* 右子树不空 */
		PostTraverse(T,2*e+2);
	visit(T[e]);
}

/* 初始条件: 二叉树T存在 */
/* 操作结果: 后序遍历T。 */
Status PostOrderTraverse(SqBiTree T)
{ 
	if(!BiTreeEmpty(T)) /* 树不空 */
		PostTraverse(T,0);
	printf("\n");
	return OK;
}

/* 层序遍历二叉树 */
void LevelOrderTraverse(SqBiTree T)
{ 
	int i=MAX_TREE_SIZE-1,j;
	while(T[i]==Nil)
		i--; /* 找到最后一个非空结点的序号 */
	for(j=0;j<=i;j++)  /* 从根结点起,按层序遍历二叉树 */
		if(T[j]!=Nil)
			visit(T[j]); /* 只遍历非空的结点 */
	printf("\n");
}

/* 逐层、按本层序号输出二叉树 */
void Print(SqBiTree T)
{ 
	int j,k;
	Position p;
	TElemType e;
	for(j=1;j<=BiTreeDepth(T);j++)
	{
		printf("第%d层: ",j);
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
	printf("建立二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
	i=Root(T,&e);
	if(i)
		printf("二叉树的根为：%d\n",e);
	else
		printf("树空，无根\n");
	printf("层序遍历二叉树:\n");
	LevelOrderTraverse(T);
	printf("前序遍历二叉树:\n");
	PreOrderTraverse(T);
	printf("中序遍历二叉树:\n");
	InOrderTraverse(T);
	printf("后序遍历二叉树:\n");
	PostOrderTraverse(T);
	printf("修改结点的层号3本层序号2。");
	p.level=3;
	p.order=2;
	e=Value(T,p);
	printf("待修改结点的原值为%d请输入新值:50 ",e);
	e=50;
	Assign(T,p,e);
	printf("前序遍历二叉树:\n");
	PreOrderTraverse(T);
	printf("结点%d的双亲为%d,左右孩子分别为",e,Parent(T,e));
	printf("%d,%d,左右兄弟分别为",LeftChild(T,e),RightChild(T,e));
	printf("%d,%d\n",LeftSibling(T,e),RightSibling(T,e));
	ClearBiTree(T);
	printf("清除二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
	i=Root(T,&e);
	if(i)
		printf("二叉树的根为：%d\n",e);
	else
		printf("树空，无根\n");
	
	return 0;
}

/*
* 二叉树的性质：
* 1.在二叉树的第i层最多有2^(i-1)个结点（i>=1）
* 2.深度为k的二叉树，最多有2^k -1个结点(k>=1)
* 3.对任何一颗二叉树T，如果其终端结点数为n0，度为2的结点数为n2，则 n0 = n2 + 1      终端结点数就是叶子数，度就是当前结点的分叉数
* 4.具有n个结点的完全二叉树的深度为[log2n]+1  （[x]为不大于x的最大整数）
* 5.若对一棵有n个节点的完全二叉树进行顺序编号（1≤i≤n），那么，对于编号为i（i≥1）的节点：
	当i=1时，该节点为根，它无双亲节点。
	当i>1时，该节点的双亲节点的编号为i/2。
	若2i≤n，则有编号为2i的左节点，否则没有左节点。
	若2i+1≤n，则有编号为2i+1的右节点，否则没有右节点。
*/

//顺序结构一般只适用于完全二叉树（因为是必须要顺序的）