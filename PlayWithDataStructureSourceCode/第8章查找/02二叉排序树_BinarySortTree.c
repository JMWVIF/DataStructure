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
	struct BiTNode *lchild, *rchild;	/* 左右孩子指针 */
} BiTNode, *BiTree;


/* 递归查找二叉排序树T中是否存在key, */
/* 指针f指向T的双亲，其初始调用值为NULL */
/* 若查找成功，则指针p指向该数据元素结点，并返回TRUE */
/* 否则指针p指向查找路径上访问的最后一个结点并返回FALSE */
Status SearchBST(BiTree T, int key, BiTree f, BiTree *p) 
{  
	if (!T)	/*  查找不成功 */
	{ 
		*p = f;  
		return FALSE; 
	}
	else if (key==T->data) /*  查找成功 */
	{ 
		*p = T;  
		return TRUE; 
	} 
	else if (key<T->data) 
		return SearchBST(T->lchild, key, T, p);  /*  在左子树中继续查找 */
	else  
		return SearchBST(T->rchild, key, T, p);  /*  在右子树中继续查找 */
}


/*  当二叉排序树T中不存在关键字等于key的数据元素时， */
/*  插入key并返回TRUE，否则返回FALSE */
Status InsertBST(BiTree *T, int key) 
{  
	BiTree p,s;
	if (!SearchBST(*T, key, NULL, &p)) /* 查找不成功 */		//开始进行插入操作 
	{
		s = (BiTree)malloc(sizeof(BiTNode));
		s->data = key;  		//插入的数值 
		s->lchild = s->rchild = NULL;  		//初始化s的左孩子和右孩子（毕竟本就没有孩子） 
		if (!p) 	//父级根本不存在（没有树T） 
			*T = s;			/*  插入s为新的根结点 */
		else if (key < p->data) 
			p->lchild = s;	/*  插入s为左孩子 */	//s是p的左孩子 
		else 
			p->rchild = s;  /*  插入s为右孩子 */	//s是p的右孩子 
		return TRUE;
	} 
	else 
		return FALSE;  /*  树中已有关键字相同的结点，不再插入 */
}

/* 从二叉排序树中删除结点p，并重接它的左或右子树。 */
Status Delete(BiTree *p)
{
	BiTree q,s;
	if((*p)->rchild==NULL) /* 右子树空则只需重接它的左子树（待删结点是叶子也走此分支) */		//对于叶子结点、右子树为空的结点
	{
		q=*p; 
		*p=(*p)->lchild; 		//左子树去子承父业 
		free(q);
	}
	else if((*p)->lchild==NULL) /* 只需重接它的右子树 */								//对于叶子结点、左子树为空的结点
	{
		q=*p; 
		*p=(*p)->rchild;		//右子树去子承父业 
		free(q);
	}
	else /* 左右子树均不空 */		//这个结点是既有左子树，又有右子树的节骨眼结点				//对于左右子树都不空的结点
	{
		q=*p;
		s=(*p)->lchild;	//先走到左子树
		while(s->rchild) /* 转左，然后向右到尽头（找待删结点的前驱） */		//一直找，直到左子树的最右结点
		{
			q=s;
			s=s->rchild;
		}
		(*p)->data = s->data; /* s指向被删结点的直接前驱（将被删结点前驱的值取代被删结点的值） */		//直接给你换了
		if(q!=*p)
			q->rchild=s->lchild; /* 重接q的右子树 */  //因为s结点被调动到q的父结点上了，所以s左结点给到q的右结点上
		else
			q->lchild=s->lchild; /* 重接q的左子树 */	//理由同上
		free(s);
	}
	return TRUE;
}

/* 若二叉排序树T中存在关键字等于key的数据元素时，则删除该数据元素结点, */
/* 并返回TRUE；否则返回FALSE。 */
Status DeleteBST(BiTree *T,int key)
{ 
	if(!*T) /* 不存在关键字等于key的数据元素 */ 
		return FALSE;		//删除失败，因为本就不存在，没必要删除 
	else
	{
		if (key==(*T)->data) /* 找到关键字等于key的数据元素 */ 
			return Delete(T);
		else if (key < (*T)->data)					//左删 
			return DeleteBST(&(*T)->lchild,key);
		else										//右删 
			return DeleteBST(&(*T)->rchild,key);
		 
	}
}

int main(void)
{    
	int i;
	int a[10]={62,88,58,47,35,73,51,99,37,93};
	BiTree T=NULL;
	
	for(i=0;i<10;i++)
	{
		InsertBST(&T, a[i]);
	}
	DeleteBST(&T,93);
	DeleteBST(&T,47);
    printf("本样例建议断点跟踪查看二叉排序树结构");
	return 0;
}

/*线性索引就是把索引项集合组织为线性结构，亦称为索引表
线性索引有三种：稠密索引、分块索引、倒排索引

稠密索引：是在线性索引中，将数据集中的每一个记录，对应一个索引项。（以指针为工具去查找）
对于稠密索引而言，索引项一定是按照关键码有序排列的
稠密索引只适用于数据集小的，因为要准备与数据集同等长度的索引规模


分块索引：是先把数据集的记录分成若干块，这些块都遵循着【块内无序】和【块间有序】的条件。
分块索引实际上是分层化的稠密索引，分成若干的块，一块管辖着一个范围。但是包含着块长（因为各个块长都是不定的）


倒排索引：记录号表（单词编号）存储具有相同次关键字（英文单词）的所有记录的记录号
可以是指向记录的指针，或者是该记录的主关键字。
现代搜索引擎的索引都是基于倒排索引，然后进行其他算法改良。
倒排索引的搜索速度非常快，但是记录号（单词）是不定长度的，维护比较困难，插入删除需额外再进行操作
*/

//这里构造一棵二叉排序树，其目的不在于为了排序，而是为了提高查找、插入、删除的效率
