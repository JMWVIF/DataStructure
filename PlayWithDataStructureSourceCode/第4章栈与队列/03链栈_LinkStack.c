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
typedef int SElemType; /* SElemType类型根据实际情况而定，这里假设为int */


/* 链栈结构 */
typedef struct StackNode
{
        SElemType data;
        struct StackNode *next;   //递归以为链栈
}StackNode,*LinkStackPtr;


typedef struct
{
        LinkStackPtr top;
        int count;
}LinkStack;

Status visit(SElemType c)
{
        printf("%d ",c);
        return OK;
}

/*  构造一个空栈S */
Status InitStack(LinkStack *S)
{ 
        S->top = (LinkStackPtr)malloc(sizeof(StackNode));
        if(!S->top)
                return ERROR;
        S->top=NULL;        //初始化
        S->count=0;         //初始化
        return OK;
}

/* 把S置为空栈 */
Status ClearStack(LinkStack *S)
{ 
        LinkStackPtr p,q;
        p=S->top;
        while(p)
        {  
                q=p;
                p=p->next;
                free(q);        //分而删之
        } 
        S->count=0;  //count置0操作
        return OK;
}

/* 若栈S为空栈，则返回TRUE，否则返回FALSE */
Status StackEmpty(LinkStack S)
{ 
        if (S.count==0)
                return TRUE;
        else
                return FALSE;
}

/* 返回S的元素个数，即栈的长度 */
int StackLength(LinkStack S)
{ 
        return S.count;
}

/* 若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR */
Status GetTop(LinkStack S,SElemType *e)
{
        if (S.top==NULL)
                return ERROR;
        else
                *e=S.top->data;     //返回栈顶元素的值
        return OK;
}

/* 插入元素e为新的栈顶元素 */      //压栈
Status Push(LinkStack *S,SElemType e)
{
        LinkStackPtr s=(LinkStackPtr)malloc(sizeof(StackNode));     //s就是一整个栈的结点，包含值以及链指针
        //这里的top是栈顶指针
        s->data=e; 
     //让每个链指针指向下一个地址（next）
        s->next=S->top;	/* 把当前的栈顶元素赋值给新结点的直接后继 */  //栈里的每个元素都带链指针
        S->top=s;         /* 将新的结点s赋值给栈顶指针 */          //将栈顶指针移向上一位
        S->count++;                                         //因为入栈，所以要让cnt+1
        return OK;
}

/* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR */    //弹栈（出栈）
Status Pop(LinkStack *S,SElemType *e)      
{ 
        LinkStackPtr p;                                             //p就是一整个栈的元素，包含值以及链指针
        if(StackEmpty(*S))
                return ERROR;
        *e=S->top->data;
        p=S->top;					/* 将栈顶结点赋值给p */             //要删除的给p
        S->top=S->top->next;    /* 使得栈顶指针下移一位，指向后一结点 */  //指向下一个结点
        free(p);                    /* 释放结点p */        
        S->count--;                                         //因为出栈，所以要让cnt-1
        return OK;
}

Status StackTraverse(LinkStack S)
{
        LinkStackPtr p;
        p=S.top;
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
        int j;
        LinkStack s;
        int e;
        if(InitStack(&s)==OK)
                for(j=1;j<=10;j++)
                        Push(&s,j);
        printf("栈中元素依次为：");
        StackTraverse(s);
        Pop(&s,&e);
        printf("弹出的栈顶元素 e=%d\n",e);
        printf("栈空否：%d(1:空 0:否)\n",StackEmpty(s));
        GetTop(s,&e);
        printf("栈顶元素 e=%d 栈的长度为%d\n",e,StackLength(s));
        ClearStack(&s);
        printf("清空栈后，栈空否：%d(1:空 0:否)\n",StackEmpty(s));
        return 0;
}

//把栈顶放在单链表的头部，能起到尾部（栈底）附带链表指针，让看上去与单链表相似
//对于链栈而言，不存在栈满的情况（栈满就会内存溢出而死机了）


//如果栈的使用过程中，元素的变化是不可预料的（有时很小，有时很大），那么就用链栈
//如果它的变化在可预料的，那么就用顺序栈（大不了两栈共享空


//链栈是进栈一个元素，就给该元素分配空间，相对于顺序栈而言，更便于元素的修改间以备不需
//而不是栈间的元素是打乱的，要先是个栈，再是个链表