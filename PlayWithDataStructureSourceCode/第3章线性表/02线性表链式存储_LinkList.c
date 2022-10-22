#include "stdio.h"    
#include "string.h"
#include "ctype.h"      
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20 /* �洢�ռ��ʼ������ */

typedef int Status;/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef int ElemType;/* ElemType���͸���ʵ������������������Ϊint */


Status visit(ElemType c)
{
    printf("%d ",c);
    return OK;		//�㴫����(return 1)�����������������return��0���ܽ������� 
}

typedef struct Node     //������ʽ������д����	 �����ͷ���
{
    ElemType data;
    struct Node *next;
}Node;      //��sizeofʶ��Node            
typedef struct Node *LinkList; /* ����LinkList */ //Node��ֵ����LinkList

/* ��ʼ��˳�����Ա� */
Status InitList(LinkList *L) 
{ 
    *L=(LinkList)malloc(sizeof(Node)); /* ����ͷ���,��ʹLָ���ͷ��� */
    if(!(*L)) /* �洢����ʧ�� */
            return ERROR;   //�൱�ڷ��ؼ٣������Ǻ���������ֹ
    (*L)->next=NULL; /* ָ����Ϊ�� */

    return OK;      //�൱�ڷ����棬�����Ǻ������쳣����ֹ
}

/* ��ʼ������˳�����Ա�L�Ѵ��ڡ������������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE */
Status ListEmpty(LinkList L)
{ 
    if(L->next)
            return FALSE;
    else
            return TRUE;
}

/* ��ʼ������˳�����Ա�L�Ѵ��ڡ������������L����Ϊ�ձ� */
Status ClearList(LinkList *L)
{ 
	LinkList p,q;
	p=(*L)->next;           /*  pָ���һ����� */
	while(p)                /*  û����β */ //NULL����0����һ�ֱ�﷽ʽ
	{
		q=p->next;          //q����p����һ�����
		free(p);            //�ͷ�p
		p=q;                //q��ֵ����p�����ѭ�����൱��ɾ�����нڵ㣩
	}
	(*L)->next=NULL;        /* ͷ���ָ����Ϊ�� */
	return OK;              //�൱�ڷ����棬�����Ǻ������쳣����ֹ
}

/* ��ʼ������˳�����Ա�L�Ѵ��ڡ��������������L������Ԫ�ظ��� */
int ListLength(LinkList L)
{
    int i=0;
    LinkList p=L->next; /* pָ���һ����� */
    while(p)                        
    {
        i++;            //�����ӵó�ֵ���൱�ڼ�������
        p=p->next;      //ָ����һ����㣨�����⵽NULL��Ҳ����0��ʱ�򣬸�ѭ��������
    }
    return i;
}

/* ��ʼ������˳�����Ա�L�Ѵ��ڣ�1��i��ListLength(L) */
/* �����������e����L�е�i������Ԫ�ص�ֵ */
Status GetElem(LinkList L,int i,ElemType *e)    //e��ָ��
{
	int j;
	LinkList p;		/* ����һ���p */
	p = L->next;		/* ��pָ������L�ĵ�һ����� */
	j = 1;		/*  jΪ������ */
	while (p && j<i)  /* p��Ϊ�ջ��߼�����j��û�е���iʱ��ѭ������ */
	{   
		p = p->next;  /* ��pָ����һ����� */
		++j;
	}
	if ( !p || j>i )    //ҪôpΪ0��p��ͷ����Ҫôj����length��ֵ��ͬ�����������
		return ERROR;  /*  ��i��Ԫ�ز����� */
	*e = p->data;   /*  ȡ��i��Ԫ�ص����� */
	return OK;
}

/* ��ʼ������˳�����Ա�L�Ѵ��� */
/* �������������L�е�1����e�����ϵ������Ԫ�ص�λ�� */
/* ������������Ԫ�ز����ڣ��򷵻�ֵΪ0 */
int LocateElem(LinkList L,ElemType e)
{
    int i=0;
    LinkList p=L->next;
    while(p)
    {
        i++;
        if(p->data==e) /* �ҵ�����������Ԫ�� */
                return i;    //���ص�һ��data = e��λ������
        p=p->next;
    }

    return 0;
}


/* ��ʼ������˳�����Ա�L�Ѵ���,1��i��ListLength(L)�� */
/* �����������L�е�i��λ��֮ǰ�����µ�����Ԫ��e��L�ĳ��ȼ�1 */
Status ListInsert(LinkList *L,int i,ElemType e)		//����*��ɾ��e 
{ 
	int j;
	LinkList p,s;
	p = *L;   
	j = 1;
	while (p && j < i)     /* Ѱ�ҵ�i����� */
	{
		p = p->next;
		++j;
	} 
	if (!p || j > i) 
		return ERROR;   /* ��i��Ԫ�ز����� */
	s = (LinkList)malloc(sizeof(Node));  /*  �����½��(C���Ա�׼����) */
	s->data = e;        //���� B 
	s->next = p->next;      /* ��p�ĺ�̽�㸳ֵ��s�ĺ��  */    //AC�Ͽ���A��B��  
	p->next = s;          /* ��s��ֵ��p�ĺ�� */               //B��C��
    //���ﲻ�����¸�������Ϊ�ᵼ��s->next = s���ͻ���������p->nextû�����ϼ���㣬�ͻ������
    //ʵ���������д���������Ӳ������
	return OK;
}

/* ��ʼ������˳�����Ա�L�Ѵ��ڣ�1��i��ListLength(L) */
/* ���������ɾ��L�ĵ�i������Ԫ�أ�����e������ֵ��L�ĳ��ȼ�1 */
Status ListDelete(LinkList *L,int i,ElemType *e) 
{ 
	int j;
	LinkList p,q;
	p = *L;
	j = 1;
	while (p->next && j < i)	/* ����Ѱ�ҵ�i��Ԫ�� */
	{
        p = p->next;
        ++j;
	}
	if (!(p->next) || j > i) 
	    return ERROR;           /* ��i��Ԫ�ز����� */
	q = p->next;                                            //��ʼ��ֵ
	p->next = q->next;			/* ��q�ĺ�̸�ֵ��p�ĺ�� */   //AB�Ͽ�������AC
	*e = q->data;               /* ��q����е����ݸ�e */        //��B��e
	free(q);                    /* ��ϵͳ���մ˽�㣬�ͷ��ڴ� */ //ɾ��B
	return OK;
}
//������Ҫmalloc��ɾ������

/* ��ʼ������˳�����Ա�L�Ѵ��� */
/* ������������ζ�L��ÿ������Ԫ����� */
Status ListTraverse(LinkList L)
{
    LinkList p=L->next;
    while(p)        
    {
        visit(p->data);
        p=p->next;
    }
    /*�൱����for(int i = 0; i < strlen(p); i++)
    {
    printf(p[i].data);
    }*/
    printf("\n");
    return OK;
}

/*  �������n��Ԫ�ص�ֵ����������ͷ���ĵ������Ա�L��ͷ�巨�� */
void CreateListHead(LinkList *L, int n) 
{
	LinkList p;
	int i;
	srand(time(0));                         /* ��ʼ�����������,��ϵͳʱ��Ϊ��� */
	*L = (LinkList)malloc(sizeof(Node));
	(*L)->next = NULL;                      /*  �Ƚ���һ����ͷ���ĵ����� */
	for (i=0; i<n; i++) 
	{
		p = (LinkList)malloc(sizeof(Node)); /*  �����½�� */
		p->data = rand()%100+1;             /*  �������100���ڵ����� */
		p->next = (*L)->next;    
		(*L)->next = p;						/*  ���뵽��ͷ */
	}
}

/*  �������n��Ԫ�ص�ֵ����������ͷ���ĵ������Ա�L��β�巨���������õ���β�壩 */
void CreateListTail(LinkList *L, int n) 
{
	LinkList p,r;
	int i;
	srand(time(0));                      /* ��ʼ����������� */
	*L = (LinkList)malloc(sizeof(Node)); /* LΪ�������Ա� */     //ԭ��a=(char*)malloc(100*sizeof(char));
	r=*L;                                /* rΪָ��β���Ľ�㣨�������ñ�������ԭ�� */
	for (i=0; i<n; i++) 
	{
		p = (Node *)malloc(sizeof(Node)); /*  �����½�� */
		p->data = rand()%100+1;           /*  �������100���ڵ����� */
		r->next=p;                        /* ����β�ն˽���ָ��ָ���½�㣨p�����½�㣩 */   //���뵽��β
		r = p;                            /* ����ǰ���½�㶨��Ϊ��β�ն˽�� */    //��r�ֳ�Ϊ���յĽ��
	}
//Ӧ�����������ָ�����ÿգ��Ա������ʱ�����ȷ������β��
	r->next = NULL;                       /* ��ʾ��ǰ������� */    
}

int main()
{        
    LinkList L;
    ElemType e;
    Status i;
    int j,k;
    i=InitList(&L);
    printf("��ʼ��L��ListLength(L)=%d\n",ListLength(L));
    for(j=1;j<=5;j++)
            i=ListInsert(&L,1,j);
    printf("��L�ı�ͷ���β���1��5��L.data=");
    ListTraverse(L); 

    printf("ListLength(L)=%d \n",ListLength(L));
    i=ListEmpty(L);
    printf("L�Ƿ�գ�i=%d(1:�� 0:��)\n",i);

    i=ClearList(&L);
    printf("���L��ListLength(L)=%d\n",ListLength(L));
    i=ListEmpty(L);
    printf("L�Ƿ�գ�i=%d(1:�� 0:��)\n",i);

    for(j=1;j<=10;j++)
            ListInsert(&L,j,j);
    printf("��L�ı�β���β���1��10��L.data=");
    ListTraverse(L); 

    printf("ListLength(L)=%d \n",ListLength(L));

    ListInsert(&L,1,0);
    printf("��L�ı�ͷ����0��L.data=");
    ListTraverse(L); 
    printf("ListLength(L)=%d \n",ListLength(L));

    GetElem(L,5,&e);
    printf("��5��Ԫ�ص�ֵΪ��%d\n",e);
    for(j=3;j<=4;j++)
    {
            k=LocateElem(L,j);
            if(k)
                    printf("��%d��Ԫ�ص�ֵΪ%d\n",k,j);
            else
                    printf("û��ֵΪ%d��Ԫ��\n",j);
    }
    

    k=ListLength(L); /* kΪ�� */
    for(j=k+1;j>=k;j--)
    {
            i=ListDelete(&L,j,&e); /* ɾ����j������ */
            if(i==ERROR)
                    printf("ɾ����%d������ʧ��\n",j);
            else
                    printf("ɾ����%d����Ԫ��ֵΪ��%d\n",j,e);
    }
    printf("�������L��Ԫ�أ�");
    ListTraverse(L); 

    j=5;
    ListDelete(&L,j,&e); /* ɾ����5������ */
    printf("ɾ����%d����Ԫ��ֵΪ��%d\n",j,e);

    printf("�������L��Ԫ�أ�");
    ListTraverse(L); 

    i=ClearList(&L);
    printf("\n���L��ListLength(L)=%d\n",ListLength(L));
    CreateListHead(&L,20);
    printf("���崴��L��Ԫ��(ͷ�巨)��");
    ListTraverse(L); 
    
    i=ClearList(&L);
    printf("\nɾ��L��ListLength(L)=%d\n",ListLength(L));
    CreateListTail(&L,20);
    printf("���崴��L��Ԫ��(β�巨)��");
    ListTraverse(L); 


    return 0;
}

/*
* ������Ա���ҪƵ���Ĳ��ң������漰�����롱�롰ɾ����������д�٣��Ļ����˲���˳��洢�ṹ
* �����Ա��е�Ԫ�ظ����仯�ϴ󡢻��߸�����֪���ж�󣨶���д�ࣩʱ���˲��õ�����ṹ
*/
