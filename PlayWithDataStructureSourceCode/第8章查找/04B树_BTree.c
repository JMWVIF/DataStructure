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

#define m 3 /* B树的阶，暂设为3 */ 
#define N 17 /* 数据元素个数 */ 
#define MAX 5 /* 字符串最大长度+1 */

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */ 

typedef struct BTNode
{
	int keynum; /* 结点中关键字个数，即结点的大小 */	//大小为1那就是二叉，2就是三叉，3就是四叉，B就是(n+1)叉
	struct BTNode *parent; /* 指向双亲结点 */		//这是一种指针的写法，相当于这个指针在指向BTNode（结构体本体）
	struct Node /* 结点向量类型 */				//结构体嵌套
	{
		 int key; /* 关键字向量 */ 
		 struct BTNode *ptr; /* 子树指针向量 */ 
		 int recptr; /* 记录指针向量 */ 
	}node[m+1]; /*  key,recptr的0号单元不用 */ 
}BTNode,*BTree; /*  B树结点和B树的类型 */ 

typedef struct
{
	BTNode *pt; /* 指向找到的结点 */ 
	int i;		/* 1..m，在结点中的关键字序号 */ 
	int tag;	/* 1:查找成功，O:查找失败 */ 
}Result;		/* B树的查找结果类型 */ 

/* 在p->node[1..keynum].key中查找i,使得p->node[i].key <= K ＜ p->node[i+1].key */ 
int Search(BTree p, int K)
{ 
	int i=0,j;
	for(j=1;j<=p->keynum;j++)
	 if(p->node[j].key<=K)
	   i=j;
	return i;	//让K在p->node[i].key到p->node[i+1].key之间
}

/* 在m阶B树T上查找关键字K，返回结果(pt,i,tag) */ 
/* 若查找成功，则特征值tag=1，指针pt所指结点中第i个关键字等于K； */
/* 否则特征值tag=0，等于K的关键字应插入在指针Pt所指结点中第i和第i+1个关键字之间。*/
Result SearchBTree(BTree T, int K)
{ 
	BTree p=T,q=NULL; /* 初始化，p指向待查结点，q指向p的双亲 */
	Status found=FALSE;
	int i=0;
	Result r;	//B树的查找结果类型
	while(p&&!found)	//p存在 && 没找到
	{
	 i=Search(p,K); /* p->node[i].key ≤ K < p->node[i+1].key */
	 if(i>0 && p->node[i].key==K) /* 找到待查关键字 */		//指针pt所指结点中第i个关键字等于K
	   found=TRUE;
	 else
	 {
	   q=p;
	   p=p->node[i].ptr;	//p指向子树的指针向量（指针下移）
	 }
	}
	r.i=i;	
	if(found) /* 查找成功 */
	{
	 r.pt=p;	//找到的结点为p
	 r.tag=1;	//特征值为1
	}
	else /* 查找不成功，返回K的插入位置信息 */ 
	{
	 r.pt=q;	//找到的结点还是q
	 r.tag=0;	//无特征值（为0）
	}
	return r;
}

/* 将【r->key】、【r】和【ap】分别插入到【q->key[i+1]】、【q->recptr[i+1]】和【q->ptr[i+1]】中 */
//这是死板的插入写法，死记硬背即可
void Insert(BTree *q,int i,int key,BTree ap)
{ 
	int j;
	for(j=(*q)->keynum;j>i;j--) /* 空出(*q)->node[i+1] */
		(*q)->node[j+1]=(*q)->node[j];
	(*q)->node[i+1].key=key;
	(*q)->node[i+1].ptr=ap;
	(*q)->node[i+1].recptr=key;
	(*q)->keynum++;
}

/* 将结点q分裂成两个结点，前一半保留，后一半移入新生结点ap */ 
void split(BTree *q,BTree *ap)
{ 
	int i,s=(m+1)/2;
	*ap=(BTree)malloc(sizeof(BTNode)); /* 生成新结点ap */ 
	(*ap)->node[0].ptr = (*q)->node[s].ptr; /* 后一半移入ap */  //因为s=(m+1)/2
	for(i=s+1;i<=m;i++)		//遍历后一半
	{
		 (*ap)->node[i-s]=(*q)->node[i];	//分裂的复制法
		 if((*ap)->node[i-s].ptr)			//分裂的复制法
			(*ap)->node[i-s].ptr->parent=*ap;
	}
	(*ap)->keynum=m-s;	//前一半+1（加的那个是s）
	(*ap)->parent=(*q)->parent;		//分裂的复制法
	(*q)->keynum=s-1; /* q的前一半保留，修改keynum */ 
}

/* 生成含信息(T,r,ap)的新的根结点&T，原T和ap为子树指针 */ 
//这是死板的插入写法，死记硬背即可
void NewRoot(BTree *T,int key,BTree ap)
{ 
	BTree p;
	p=(BTree)malloc(sizeof(BTNode));
	p->node[0].ptr=*T;
	*T=p;
	if((*T)->node[0].ptr)
		(*T)->node[0].ptr->parent=*T;
	(*T)->parent=NULL;
	(*T)->keynum=1;
	(*T)->node[1].key=key;
	(*T)->node[1].recptr=key;
	(*T)->node[1].ptr=ap;
	if((*T)->node[1].ptr)
		(*T)->node[1].ptr->parent=*T;
}

/* 在m阶B树T上结点*q的key[i]与key[i+1]之间插入关键字K的指针r。若引起 */ 
/* 结点过大,则沿双亲链进行必要的结点分裂调整,使T仍是m阶B树。 */
void InsertBTree(BTree *T,int key,BTree q,int i)
{ 
	BTree ap=NULL;
	Status finished=FALSE;
	int s;
	int rx;
	rx=key;
	while(q && !finished)	//q存在 && 没有结束
	{
		Insert(&q,i,rx,ap);
		/* 将【r->key】、【r】和【ap】分别插入到【q->key[i+1]】、【q->recptr[i+1]】和【q->ptr[i+1]】中 */
		if(q->keynum<m)
			finished=TRUE; /* 插入完成 */ 
		else
		{ /* 分裂结点*q */ 
			s=(m+1)/2;
			rx=q->node[s].recptr;	//rx就是q结点的右子树s的指针向量
			split(&q,&ap); /* 将q->key[s+1..m],q->ptr[s..m]和q->recptr[s+1..m]移入【新结点*ap】 */
			q=q->parent;	//q指向自己双亲
			if(q)
				i=Search(q,key); /* 在双亲结点*q中查找rx->key的插入位置 */
		}
	}
	if(!finished) /* T是空树(参数q初值为NULL)或根结点已分裂为结点*q和*ap */ 
		NewRoot(T,rx,ap); /* 生成含信息(T, rx, ap)的新的根结点*T，原T和ap为子树指针 */
}


void print(BTNode c,int i) /* TraverseDSTable()调用的函数 */
{
	printf("(%d)",c.node[i].key);
}

int main()
{
	int r[N]={22,16,41,58,8,11,12,16,17,22,23,31,41,52,58,59,61};
	BTree T=NULL;
	Result s;
	int i;
	for(i=0;i<N;i++)
	{
		s=SearchBTree(T,r[i]);
		if(!s.tag)
			InsertBTree(&T,r[i],s.pt,s.i);
	}
	printf("\n请输入待查找记录的关键字: ");
	scanf("%d",&i);
	s=SearchBTree(T,i);
	if(s.tag)
		print(*(s.pt),s.i);
	else
		printf("没找到");
	printf("\n");

	return 0;
}

//B树就是Balance Tree，平衡树
//B树的操作效率取决于访问磁盘的次数,关键字总数相同的情况下B树的高度越小，磁盘I/O所花的时间越少

/*一个m阶的B树具有如下属性：
1）每个节点至多有M个子节点；
2）有K个子节点的非叶子节点中包含K-1个键（Key）;
3）根节点至少有两个子节点（如果此时B-树不仅只有根节点）；
4）每个非叶子节点（根节点除外）至少有Ceil[M/2]个子节点；这里Ceil表示向上取整；
5）所有的叶子节点都在同一层。
*/

//B树因为是中序遍历，所以每一次都要遍历n遍的父级结点，效率低下



/*一个m阶的B+树具有以下特征：
1. 有k个子树的中间节点包含有k个元素（B树是k-1个元素），每个元素不保存数据，只用来索引，所有数据都保存在叶子节点中。
2. 所有的叶子节点中包含了全部元素的信息，及指向含这些元素记录的指针，且叶子节点本身依关键字的大小自小而大顺序链接。（链表）
3. 所有的中间节点元素都同时存在于子节点，在子节点元素中是最大（或最小）元素。
4. B+树查找时是自上向下查找，B-树是从下向上查找（中序遍历）。
*/

/*数据库索引采用B+树的主要原因:
B树在提高了IO性能的同时并没有解决元素遍历的效率低下的问题。
正是为了解决这个问题，B+树应用而生。
B+树只需要去遍历叶子节点就可以实现整棵树的遍历。
而且在数据库中基于范围的查询是非常频繁的，而B树不支持这样的操作
*/

/*B树与B+树的区别：
在B+树中，具有n个关键字的节点只含有n棵子树，即每个关键字对应一个子树；
而在B树中，具有n个关键字的节点只含有n+1棵子树。

在B+树中，每个结点（非根节点）关键字个数n的范围是m/2(向上取整)<=n<=m(根结点：1<=n<=m)；
而在B树中，每个结点（非根节点）关键字个数n的范围是m/2(向上取整)-1<=n<=m-1(根结点：1<=n<=m-1)。

在B+树中，只有【叶结点】包含信息，所有【非叶结点】仅起到索引作用，
非叶结点中的每个索引项只含有对应子树的最大关键字和指向该子树的指针，
不含有该关键字对应记录的存储地址。

在B+树中，叶结点包含了全部关键字，即在非叶结点中出现的关键字也会出现在叶节点中；
而在B树中，叶结点包含的关键字和其他结点包含的关键字是不重复的。
*/