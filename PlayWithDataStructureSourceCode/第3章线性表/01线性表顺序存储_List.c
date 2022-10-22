#include "stdio.h"    

#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20           /* 存储空间初始分配量 */

typedef int Status;          /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType;        /* ElemType类型根据实际情况而定，这里假设为int */


Status visit(ElemType c)       //把ElemType看成int即可
{
    printf("%d ",c);
    return OK;
}

typedef struct
{
	ElemType data[MAXSIZE];        /* 数组，存储数据元素 */  //等同于int data[20]
	int length;                    /* 线性表当前长度 */
}SqList;                           //SqList是结构体的类名

/* 初始化顺序线性表 */
Status InitList(SqList *L)          //L是SqList的值（相当于L有着调用SqList的值的权限），SqlList就是一个结构体
{ 
    L->length=0;                    //结构体的值就是要 ->
    return OK;
}

/* 初始条件：顺序线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */   //要先判断，相当于检测
Status ListEmpty(SqList L)          //L是调用SqList的变量的名（相当于L有着调用SqList的权限）
{ 
	if(L.length==0)                 //结构体的名就是要.
		return TRUE;
	else
		return FALSE;
}

/* 初始条件：顺序线性表L已存在。操作结果：将L重置为空表 */
Status ClearList(SqList *L)
{ 
    L->length=0;
    return OK;
}

/* 初始条件：顺序线性表L已存在。操作结果：返回L中数据元素个数 */    //实际上就是调用库函数
int ListLength(SqList L)        
{
	return L.length;
}

/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：用e返回L中第i个数据元素的值,注意i是指位置，第1个位置的数组是从0开始 */
Status GetElem(SqList L,int i,ElemType *e)
{
    if(L.length==0 || i<1 || i>L.length)
            return ERROR;
    *e=L.data[i-1];         //返回第i个值，所以是*e而不是e

    return OK;
}

/* 初始条件：顺序线性表L已存在 */
/* 操作结果：返回L中第1个与e满足关系的数据元素的位序。 */
/* 若这样的数据元素不存在，则返回值为0 */
int LocateElem(SqList L,ElemType e)
{
    int i;
    if (L.length==0||i>=L.length)    //不合条件
            return 0;
    for(i=0;i<L.length;i++)
    {
            if (L.data[i]==e)   //找寻与e相合的某个值
                    break;      //找寻成功
    }
    return i+1;                 //返回值，完成任务
}


/* 初始条件：顺序线性表L已存在,1≤i≤ListLength(L)， */
/* 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1 */
Status ListInsert(SqList *L,int i,ElemType e)
{ 
	int k;
	if (L->length==MAXSIZE)  /* 顺序线性表已经满 */
		return ERROR;
	if (i<1 || i>L->length+1)/* 当i比第一位置小或者比最后一位置后一位置还要大时 */
		return ERROR;

	if (i<=L->length)        /* 若插入数据位置不在表尾 */
	{
		for(k=L->length-1;k>=i-1;k--)  /* 将要插入位置之后的数据元素向后移动一位 */    // length-1 ~ i-1
			L->data[k+1]=L->data[k];    //插入的元素的后面所有值，全部通过循环，移到后一位
	}
	L->data[i-1]=e;          /* 将新元素插入 */
	L->length++;            //length+1，因为新元素插入了

	return OK;
}

/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1 */
Status ListDelete(SqList *L,int i,ElemType *e) 
{ 
    int k;
    if (L->length==0)               /* 线性表为空 */
		return ERROR;
    if (i<1 || i>L->length)         /* 删除位置不正确 */
        return ERROR;
    *e=L->data[i-1];                //只是存储着删除的值，删除本身由下方的循环而覆写
    if (i<L->length)                /* 如果删除不是最后位置 */
    {
        for(k=i;k<L->length;k++)/* 将删除位置后继元素前移 */
			L->data[k-1]=L->data[k];
    }
    L->length--;
    return OK;
}

/* 初始条件：顺序线性表L已存在 */
/* 操作结果：依次对L的每个数据元素输出 */
Status ListTraverse(SqList L)
{
	int i;
    for(i=0;i<L.length;i++)
            visit(L.data[i]);       //相当于printf("%s",L.data[i]);
    printf("\n");
    return OK;
}

//在Lb有的，La没有的，插入到La中
void unionL(SqList *La,SqList Lb)
{
	int La_len,Lb_len,i;
	ElemType e;                 //声明与La和Lb相同的数据元素e
	La_len=ListLength(*La);     //求线性表的长度
	Lb_len=ListLength(Lb);
	for(i=1;i<=Lb_len;i++)
	{
		GetElem(Lb,i,&e);       //取Lb中第i个元素，值给e
		if(!LocateElem(*La,e))  //如果La中不存在与e相同元素者
			ListInsert(La,++La_len,e);//执行插入，并且自动地（在函数内）让长度+1
	}
}

int main()
{
        
    SqList L;       //SqList
	SqList Lb;      //类名 Lb
    
    ElemType e;     //int e
    Status i;       //int i
    int j,k;
    i=InitList(&L);		//传参需要&*相抵，即使不相抵，编译器也能够帮你报错 
    printf("初始化L后：L.length=%d\n",L.length);
    for(j=1;j<=5;j++)
            i=ListInsert(&L,1,j);
    printf("在L的表头依次插入1～5后：L.data=");
    ListTraverse(L); 

    printf("L.length=%d \n",L.length);
    i=ListEmpty(L);
    printf("L是否空：i=%d(1:是 0:否)\n",i);

    i=ClearList(&L);
    printf("清空L后：L.length=%d\n",L.length);
    i=ListEmpty(L);
    printf("L是否空：i=%d(1:是 0:否)\n",i);

    for(j=1;j<=10;j++)
            ListInsert(&L,j,j);
    printf("在L的表尾依次插入1～10后：L.data=");
    ListTraverse(L); 

    printf("L.length=%d \n",L.length);

    ListInsert(&L,1,0);
    printf("在L的表头插入0后：L.data=");
    ListTraverse(L); 
    printf("L.length=%d \n",L.length);

    GetElem(L,5,&e);
    printf("第5个元素的值为：%d\n",e);
    for(j=3;j<=4;j++)
    {
            k=LocateElem(L,j);
            if(k)
                    printf("第%d个元素的值为%d\n",k,j);
            else
                    printf("没有值为%d的元素\n",j);
    }
    

    k=ListLength(L); /* k为表长 */
    for(j=k+1;j>=k;j--)
    {
            i=ListDelete(&L,j,&e); /* 删除第j个数据 */
            if(i==ERROR)
                    printf("删除第%d个数据失败\n",j);
            else
                    printf("删除第%d个的元素值为：%d\n",j,e);
    }
    printf("依次输出L的元素：");
    ListTraverse(L); 

    j=5;
    ListDelete(&L,j,&e); /* 删除第5个数据 */      //因为你的函数的参数是*（导），所以要&（积）回去
    printf("删除第%d个的元素值为：%d\n",j,e);

    printf("依次输出L的元素：");
    ListTraverse(L); 

	//构造一个有10个数的Lb
	i=InitList(&Lb);
    for(j=6;j<=15;j++)
            i=ListInsert(&Lb,1,j);

	unionL(&L,Lb);

	printf("依次输出合并了Lb的L的元素：");
    ListTraverse(L); 

    return 0;
}


/*
* 当你传递一个参数给函数的时候，这个参数会不会在函数内被改动，决定了使用什么参数形式。
* 如果需要被改动，则需要传递指向这个参数的指针（&L）   （因为值会变，地址则不会）
* 如果不需要被改动，则可以直接传递这个函数
*/
