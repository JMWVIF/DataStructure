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

/* 顺序栈结构 */
typedef struct
{
        SElemType data[MAXSIZE];
        int top; /* 用于栈顶指针 */
}SqStack;

Status visit(SElemType c)
{
        printf("%d ",c);
        return OK;
}

/*  构造一个空栈S */
Status InitStack(SqStack *S)
{ 
        /* S.data=(SElemType *)malloc(MAXSIZE*sizeof(SElemType)); */    
    //与只设置空栈相比，多了一个创造（malloc）
        S->top=-1;          //空栈的固定格式，死记硬背就行
        return OK;
}

/* 把S置为空栈 */
Status ClearStack(SqStack *S)
{ 
        S->top=-1;          //空栈的固定格式，死记硬背就行
        return OK;
}

/* 若栈S为空栈，则返回TRUE，否则返回FALSE */  //简单的检测函数
Status StackEmpty(SqStack S)
{ 
        if (S.top==-1)
                return TRUE;
        else
                return FALSE;
}

/* 返回S的元素个数，即栈的长度 */
int StackLength(SqStack S)
{ 
        return S.top+1;
}

/* 若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR */
Status GetTop(SqStack S,SElemType *e)
{
        if (S.top==-1)
                return ERROR;
        else
                *e=S.data[S.top];       //用e返回栈顶元素的值，*e才是值，e只是指针
        //栈S的top就是栈顶，这个值存放在data内，data又隶属于S
        return OK;
}

/* 插入元素e为新的栈顶元素 */
Status Push(SqStack *S,SElemType e)
{
        if(S->top == MAXSIZE -1) /* 栈满 */
        {
                return ERROR;
        }
        S->top++;				/* 栈顶指针增加一 */
        S->data[S->top]=e;  /* 将新插入元素赋值给栈顶空间 */   //相当于S.data[S.top] = *e的名字化
        //上面这一长串就是栈顶空间
        return OK;
}

/* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR */
Status Pop(SqStack *S,SElemType *e)
{ 
        if(S->top==-1)
                return ERROR;
        *e=S->data[S->top];	/* 将要删除的栈顶元素赋值给e */
        S->top--;				/* 栈顶指针减一 */    //因为删除了原有的栈顶
        return OK;
}

/* 从栈底到栈顶依次对栈中每个元素显示 */   //显示栈内所有元素用的
Status StackTraverse(SqStack S)
{
        int i;
        i=0;
        while(i<=S.top)
        {
                visit(S.data[i++]);
        }
        printf("\n");
        return OK;
}

int main()
{
        int j;
        SqStack s;
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

//栈是上底下顶，堆是正常的上顶下底
//一般局部变量会优先往寄存器中保存，寄存器不够用时才会开始考虑栈

//顺序栈因为只允许栈顶进出元素，所以不存在线性表的插入/删除时，需要移动元素的问题
//但是，顺序栈必须要事先规定存储空间的大小，如果超了就要用编程手段继续扩展（很麻烦）