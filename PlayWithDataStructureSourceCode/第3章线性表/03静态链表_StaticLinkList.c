#include "string.h"
#include "ctype.h"      

#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 1000    /* 存储空间初始分配量 */

typedef int Status;           /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef char ElemType;        /* ElemType类型根据实际情况而定，这里假设为char */


Status visit(ElemType c)
{
    printf("%c ",c);
    return OK;
}

/* 线性表的静态链表存储结构 */
typedef struct      //让数组的每个下标都有着data与cur，data用来存储数据，cur用来当指针用
{
    ElemType data;
    int cur;  /* 游标(Cursor) ，为0时表示无指向 */
} Component,StaticLinkList[MAXSIZE];       //一个是赋给权限的名，一个是赋给权限的数组


/* 将一维数组space中各分量,链成一个备用链表，space[0].cur为头指针，"0"表示空指针 */
Status InitList(StaticLinkList space) 
{
	int i;
	for (i=0; i<MAXSIZE-1; i++)  
		space[i].cur = i+1;   //初始化好游标，且正常的cur都是比下标+1（口田->口田……）
	space[MAXSIZE-1].cur = 0; /* 目前静态链表为空，最后一个元素的cur为0（因为本来就不需要游标了） */
	return OK;
}

//备用链表是未被使用的数据元素
//数组的第一个元素与最后一个元素做特殊处理，不存数据(a[0].data = NULL;a[i].data = NULL;)
//数组的第一个元素a[0]的cur是存放在备用链表的第一个结点的下标。
//而数组的最后一个元素a[i]的cur则存放在第一个有数值的元素的下标(a[i].cur = 0)
//这相当于单链表中的头结点的作用
/* 若备用空间链表非空，则返回分配的结点下标，否则返回0 */
int Malloc_SSL(StaticLinkList space) 
{ 
	int i = space[0].cur;           		/* 当前数组第一个元素的cur存的值 */
	                                		/* 就是要返回的第一个备用空闲的下标 */
	if (space[0].cur)     //非空
//由于要拿出一个分量来使用了，所以我们就得把它的下一个分量用来做备用
	    space[0].cur = space[i].cur;      
	                                       
	return i;
}


/*  将下标为k的空闲结点回收到备用链表 */
void Free_SSL(StaticLinkList space, int k)  
{  
    space[k].cur = space[0].cur;    /* 把第一个元素的cur值赋给要删除的分量cur */     //直接NULL
    space[0].cur = k;               /* 把要删除的分量下标赋值给第一个元素的cur */     //cur改为优先放到这里的分量
}

/* 初始条件：静态链表L已存在。操作结果：返回L中数据元素个数 */
int ListLength(StaticLinkList L)
{
    int j=0;
    int i=L[MAXSIZE-1].cur;
    while(i)
    {
        i=L[i].cur;
        j++;
    }
    return j;
}

/*  在L中第i个元素之前插入新的数据元素e   */
Status ListInsert(StaticLinkList L, int i, ElemType e)   
{  
    int j, k, l;   
    k = MAXSIZE - 1;   /* 注意k首先是最后一个元素的下标 */
    if (i < 1 || i > ListLength(L) + 1)   
        return ERROR;   
    j = Malloc_SSL(L);   /* 获得空闲分量的下标 */
    if (j)   
    {   
		L[j].data = e;   /* 将数据赋值给此分量的data */
		for(l = 1; l <= i - 1; l++)   /* 找到第i个元素之前的位置 */
		   k = L[k].cur;           //执行链表的前i-1项的链接（L[999].cur = 1,L[1].cur = 2，……）
		L[j].cur = L[k].cur;    /* 把第i个元素之前的cur赋值给新元素的cur */    //两条链表，AB连接（L[7].cur = L[2].cur = 3）
		L[k].cur = j;           /* 把新元素的下标赋值给第i个元素之前元素的ur */    //BC连接(L[2].cur = 7)
        //以上四行代码是核心代码，死记硬背就行
        //()内的是模拟i = 7的情况下，把a[7].data 插入到a[2]与a[3]中
		return OK;   
    }   
    return ERROR;   
}

/*  删除在L中第i个数据元素   */
Status ListDelete(StaticLinkList L, int i)   
{ 
    int j, k;   
    if (i < 1 || i > ListLength(L))   
        return ERROR;   
    k = MAXSIZE - 1;   
    for (j = 1; j <= i - 1; j++)   
        k = L[k].cur;   //先遍历一遍
    j = L[k].cur;       //找出B
    L[k].cur = L[j].cur;        //AC连接
    Free_SSL(L, j);             //删除B（实际上是替换，以后只要不读取这个元素就行了）
    return OK;   
} 
/* 操作结果：依次对L的每个数据元素输出（看到visit就想到输出） */
Status ListTraverse(StaticLinkList L)
{
    int j=0;
    int i=L[MAXSIZE-1].cur;
    while(i)
    {
            visit(L[i].data);
            i=L[i].cur;
            j++;
    }
    return j;
    printf("\n");
    return OK;
}


int main()
{
    StaticLinkList L;
    Status i;
    i=InitList(L);
    printf("初始化L后：L.length=%d\n",ListLength(L));

    i=ListInsert(L,1,'F');
    i=ListInsert(L,1,'E');
    i=ListInsert(L,1,'D');
    i=ListInsert(L,1,'B');
    i=ListInsert(L,1,'A');

    printf("\n在L的表头依次插入FEDBA后：\nL.data=");
    ListTraverse(L); 

    i=ListInsert(L,3,'C');
    printf("\n在L的“B”与“D”之间插入“C”后：\nL.data=");
    ListTraverse(L); 

    i=ListDelete(L,1);
    printf("\n在L的删除“A”后：\nL.data=");
    ListTraverse(L); 

    printf("\n");

    return 0;
}

/*
* 静态链表相比于顺序存储结构，有着以下优点：
* 在插入和删除的操作时，只需要修改游标，不需要移动元素
从而改进了在顺序存储结构中插入与删除操作中，需要移动大量元素的缺点

缺点：
失去了链式存储结构中，随机存取的特性
以及没有malloc，所以并没有解决连续存储的分配，所带来的表长难以确定的问题。

总的来说，静态链表实际上是为了给没有指针的高级语言，设计
出来的一种实现单链表能力的想法，不过在日常上不常用
*/

/*
* 循环链表（衔尾蛇）与单链表的最主要差异只在循环的判断上
* if(p->next == NULL) return OK 就是单链表
* if(p->next != space[0] return 循环未结束)就是循环链表
* 
* 
* 双向链表： p->next->prior = p = p->prior->next 
* 只是一个结点里，前后都是指针域（比单链表多出来一个前置的指针域）
*/