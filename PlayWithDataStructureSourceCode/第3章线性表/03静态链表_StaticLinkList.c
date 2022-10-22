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

#define MAXSIZE 1000    /* �洢�ռ��ʼ������ */

typedef int Status;           /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef char ElemType;        /* ElemType���͸���ʵ������������������Ϊchar */


Status visit(ElemType c)
{
    printf("%c ",c);
    return OK;
}

/* ���Ա�ľ�̬����洢�ṹ */
typedef struct      //�������ÿ���±궼����data��cur��data�����洢���ݣ�cur������ָ����
{
    ElemType data;
    int cur;  /* �α�(Cursor) ��Ϊ0ʱ��ʾ��ָ�� */
} Component,StaticLinkList[MAXSIZE];       //һ���Ǹ���Ȩ�޵�����һ���Ǹ���Ȩ�޵�����


/* ��һά����space�и�����,����һ����������space[0].curΪͷָ�룬"0"��ʾ��ָ�� */
Status InitList(StaticLinkList space) 
{
	int i;
	for (i=0; i<MAXSIZE-1; i++)  
		space[i].cur = i+1;   //��ʼ�����α꣬��������cur���Ǳ��±�+1������->�������
	space[MAXSIZE-1].cur = 0; /* Ŀǰ��̬����Ϊ�գ����һ��Ԫ�ص�curΪ0����Ϊ�����Ͳ���Ҫ�α��ˣ� */
	return OK;
}

//����������δ��ʹ�õ�����Ԫ��
//����ĵ�һ��Ԫ�������һ��Ԫ�������⴦����������(a[0].data = NULL;a[i].data = NULL;)
//����ĵ�һ��Ԫ��a[0]��cur�Ǵ���ڱ�������ĵ�һ�������±ꡣ
//����������һ��Ԫ��a[i]��cur�����ڵ�һ������ֵ��Ԫ�ص��±�(a[i].cur = 0)
//���൱�ڵ������е�ͷ��������
/* �����ÿռ�����ǿգ��򷵻ط���Ľ���±꣬���򷵻�0 */
int Malloc_SSL(StaticLinkList space) 
{ 
	int i = space[0].cur;           		/* ��ǰ�����һ��Ԫ�ص�cur���ֵ */
	                                		/* ����Ҫ���صĵ�һ�����ÿ��е��±� */
	if (space[0].cur)     //�ǿ�
//����Ҫ�ó�һ��������ʹ���ˣ��������Ǿ͵ð�������һ����������������
	    space[0].cur = space[i].cur;      
	                                       
	return i;
}


/*  ���±�Ϊk�Ŀ��н����յ��������� */
void Free_SSL(StaticLinkList space, int k)  
{  
    space[k].cur = space[0].cur;    /* �ѵ�һ��Ԫ�ص�curֵ����Ҫɾ���ķ���cur */     //ֱ��NULL
    space[0].cur = k;               /* ��Ҫɾ���ķ����±긳ֵ����һ��Ԫ�ص�cur */     //cur��Ϊ���ȷŵ�����ķ���
}

/* ��ʼ��������̬����L�Ѵ��ڡ��������������L������Ԫ�ظ��� */
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

/*  ��L�е�i��Ԫ��֮ǰ�����µ�����Ԫ��e   */
Status ListInsert(StaticLinkList L, int i, ElemType e)   
{  
    int j, k, l;   
    k = MAXSIZE - 1;   /* ע��k���������һ��Ԫ�ص��±� */
    if (i < 1 || i > ListLength(L) + 1)   
        return ERROR;   
    j = Malloc_SSL(L);   /* ��ÿ��з������±� */
    if (j)   
    {   
		L[j].data = e;   /* �����ݸ�ֵ���˷�����data */
		for(l = 1; l <= i - 1; l++)   /* �ҵ���i��Ԫ��֮ǰ��λ�� */
		   k = L[k].cur;           //ִ�������ǰi-1������ӣ�L[999].cur = 1,L[1].cur = 2��������
		L[j].cur = L[k].cur;    /* �ѵ�i��Ԫ��֮ǰ��cur��ֵ����Ԫ�ص�cur */    //��������AB���ӣ�L[7].cur = L[2].cur = 3��
		L[k].cur = j;           /* ����Ԫ�ص��±긳ֵ����i��Ԫ��֮ǰԪ�ص�ur */    //BC����(L[2].cur = 7)
        //�������д����Ǻ��Ĵ��룬����Ӳ������
        //()�ڵ���ģ��i = 7������£���a[7].data ���뵽a[2]��a[3]��
		return OK;   
    }   
    return ERROR;   
}

/*  ɾ����L�е�i������Ԫ��   */
Status ListDelete(StaticLinkList L, int i)   
{ 
    int j, k;   
    if (i < 1 || i > ListLength(L))   
        return ERROR;   
    k = MAXSIZE - 1;   
    for (j = 1; j <= i - 1; j++)   
        k = L[k].cur;   //�ȱ���һ��
    j = L[k].cur;       //�ҳ�B
    L[k].cur = L[j].cur;        //AC����
    Free_SSL(L, j);             //ɾ��B��ʵ�������滻���Ժ�ֻҪ����ȡ���Ԫ�ؾ����ˣ�
    return OK;   
} 
/* ������������ζ�L��ÿ������Ԫ�����������visit���뵽����� */
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
    printf("��ʼ��L��L.length=%d\n",ListLength(L));

    i=ListInsert(L,1,'F');
    i=ListInsert(L,1,'E');
    i=ListInsert(L,1,'D');
    i=ListInsert(L,1,'B');
    i=ListInsert(L,1,'A');

    printf("\n��L�ı�ͷ���β���FEDBA��\nL.data=");
    ListTraverse(L); 

    i=ListInsert(L,3,'C');
    printf("\n��L�ġ�B���롰D��֮����롰C����\nL.data=");
    ListTraverse(L); 

    i=ListDelete(L,1);
    printf("\n��L��ɾ����A����\nL.data=");
    ListTraverse(L); 

    printf("\n");

    return 0;
}

/*
* ��̬���������˳��洢�ṹ�����������ŵ㣺
* �ڲ����ɾ���Ĳ���ʱ��ֻ��Ҫ�޸��α꣬����Ҫ�ƶ�Ԫ��
�Ӷ��Ľ�����˳��洢�ṹ�в�����ɾ�������У���Ҫ�ƶ�����Ԫ�ص�ȱ��

ȱ�㣺
ʧȥ����ʽ�洢�ṹ�У������ȡ������
�Լ�û��malloc�����Բ�û�н�������洢�ķ��䣬�������ı�����ȷ�������⡣

�ܵ���˵����̬����ʵ������Ϊ�˸�û��ָ��ĸ߼����ԣ����
������һ��ʵ�ֵ������������뷨���������ճ��ϲ�����
*/

/*
* ѭ��������β�ߣ��뵥���������Ҫ����ֻ��ѭ�����ж���
* if(p->next == NULL) return OK ���ǵ�����
* if(p->next != space[0] return ѭ��δ����)����ѭ������
* 
* 
* ˫������ p->next->prior = p = p->prior->next 
* ֻ��һ������ǰ����ָ���򣨱ȵ���������һ��ǰ�õ�ָ����
*/