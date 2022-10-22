#include "stdio.h"    

#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20           /* �洢�ռ��ʼ������ */

typedef int Status;          /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef int ElemType;        /* ElemType���͸���ʵ������������������Ϊint */


Status visit(ElemType c)       //��ElemType����int����
{
    printf("%d ",c);
    return OK;
}

typedef struct
{
	ElemType data[MAXSIZE];        /* ���飬�洢����Ԫ�� */  //��ͬ��int data[20]
	int length;                    /* ���Ա�ǰ���� */
}SqList;                           //SqList�ǽṹ�������

/* ��ʼ��˳�����Ա� */
Status InitList(SqList *L)          //L��SqList��ֵ���൱��L���ŵ���SqList��ֵ��Ȩ�ޣ���SqlList����һ���ṹ��
{ 
    L->length=0;                    //�ṹ���ֵ����Ҫ ->
    return OK;
}

/* ��ʼ������˳�����Ա�L�Ѵ��ڡ������������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE */   //Ҫ���жϣ��൱�ڼ��
Status ListEmpty(SqList L)          //L�ǵ���SqList�ı����������൱��L���ŵ���SqList��Ȩ�ޣ�
{ 
	if(L.length==0)                 //�ṹ���������Ҫ.
		return TRUE;
	else
		return FALSE;
}

/* ��ʼ������˳�����Ա�L�Ѵ��ڡ������������L����Ϊ�ձ� */
Status ClearList(SqList *L)
{ 
    L->length=0;
    return OK;
}

/* ��ʼ������˳�����Ա�L�Ѵ��ڡ��������������L������Ԫ�ظ��� */    //ʵ���Ͼ��ǵ��ÿ⺯��
int ListLength(SqList L)        
{
	return L.length;
}

/* ��ʼ������˳�����Ա�L�Ѵ��ڣ�1��i��ListLength(L) */
/* �����������e����L�е�i������Ԫ�ص�ֵ,ע��i��ָλ�ã���1��λ�õ������Ǵ�0��ʼ */
Status GetElem(SqList L,int i,ElemType *e)
{
    if(L.length==0 || i<1 || i>L.length)
            return ERROR;
    *e=L.data[i-1];         //���ص�i��ֵ��������*e������e

    return OK;
}

/* ��ʼ������˳�����Ա�L�Ѵ��� */
/* �������������L�е�1����e�����ϵ������Ԫ�ص�λ�� */
/* ������������Ԫ�ز����ڣ��򷵻�ֵΪ0 */
int LocateElem(SqList L,ElemType e)
{
    int i;
    if (L.length==0||i>=L.length)    //��������
            return 0;
    for(i=0;i<L.length;i++)
    {
            if (L.data[i]==e)   //��Ѱ��e��ϵ�ĳ��ֵ
                    break;      //��Ѱ�ɹ�
    }
    return i+1;                 //����ֵ���������
}


/* ��ʼ������˳�����Ա�L�Ѵ���,1��i��ListLength(L)�� */
/* �����������L�е�i��λ��֮ǰ�����µ�����Ԫ��e��L�ĳ��ȼ�1 */
Status ListInsert(SqList *L,int i,ElemType e)
{ 
	int k;
	if (L->length==MAXSIZE)  /* ˳�����Ա��Ѿ��� */
		return ERROR;
	if (i<1 || i>L->length+1)/* ��i�ȵ�һλ��С���߱����һλ�ú�һλ�û�Ҫ��ʱ */
		return ERROR;

	if (i<=L->length)        /* ����������λ�ò��ڱ�β */
	{
		for(k=L->length-1;k>=i-1;k--)  /* ��Ҫ����λ��֮�������Ԫ������ƶ�һλ */    // length-1 ~ i-1
			L->data[k+1]=L->data[k];    //�����Ԫ�صĺ�������ֵ��ȫ��ͨ��ѭ�����Ƶ���һλ
	}
	L->data[i-1]=e;          /* ����Ԫ�ز��� */
	L->length++;            //length+1����Ϊ��Ԫ�ز�����

	return OK;
}

/* ��ʼ������˳�����Ա�L�Ѵ��ڣ�1��i��ListLength(L) */
/* ���������ɾ��L�ĵ�i������Ԫ�أ�����e������ֵ��L�ĳ��ȼ�1 */
Status ListDelete(SqList *L,int i,ElemType *e) 
{ 
    int k;
    if (L->length==0)               /* ���Ա�Ϊ�� */
		return ERROR;
    if (i<1 || i>L->length)         /* ɾ��λ�ò���ȷ */
        return ERROR;
    *e=L->data[i-1];                //ֻ�Ǵ洢��ɾ����ֵ��ɾ���������·���ѭ������д
    if (i<L->length)                /* ���ɾ���������λ�� */
    {
        for(k=i;k<L->length;k++)/* ��ɾ��λ�ú��Ԫ��ǰ�� */
			L->data[k-1]=L->data[k];
    }
    L->length--;
    return OK;
}

/* ��ʼ������˳�����Ա�L�Ѵ��� */
/* ������������ζ�L��ÿ������Ԫ����� */
Status ListTraverse(SqList L)
{
	int i;
    for(i=0;i<L.length;i++)
            visit(L.data[i]);       //�൱��printf("%s",L.data[i]);
    printf("\n");
    return OK;
}

//��Lb�еģ�Laû�еģ����뵽La��
void unionL(SqList *La,SqList Lb)
{
	int La_len,Lb_len,i;
	ElemType e;                 //������La��Lb��ͬ������Ԫ��e
	La_len=ListLength(*La);     //�����Ա�ĳ���
	Lb_len=ListLength(Lb);
	for(i=1;i<=Lb_len;i++)
	{
		GetElem(Lb,i,&e);       //ȡLb�е�i��Ԫ�أ�ֵ��e
		if(!LocateElem(*La,e))  //���La�в�������e��ͬԪ����
			ListInsert(La,++La_len,e);//ִ�в��룬�����Զ��أ��ں����ڣ��ó���+1
	}
}

int main()
{
        
    SqList L;       //SqList
	SqList Lb;      //���� Lb
    
    ElemType e;     //int e
    Status i;       //int i
    int j,k;
    i=InitList(&L);		//������Ҫ&*��֣���ʹ����֣�������Ҳ�ܹ����㱨�� 
    printf("��ʼ��L��L.length=%d\n",L.length);
    for(j=1;j<=5;j++)
            i=ListInsert(&L,1,j);
    printf("��L�ı�ͷ���β���1��5��L.data=");
    ListTraverse(L); 

    printf("L.length=%d \n",L.length);
    i=ListEmpty(L);
    printf("L�Ƿ�գ�i=%d(1:�� 0:��)\n",i);

    i=ClearList(&L);
    printf("���L��L.length=%d\n",L.length);
    i=ListEmpty(L);
    printf("L�Ƿ�գ�i=%d(1:�� 0:��)\n",i);

    for(j=1;j<=10;j++)
            ListInsert(&L,j,j);
    printf("��L�ı�β���β���1��10��L.data=");
    ListTraverse(L); 

    printf("L.length=%d \n",L.length);

    ListInsert(&L,1,0);
    printf("��L�ı�ͷ����0��L.data=");
    ListTraverse(L); 
    printf("L.length=%d \n",L.length);

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
    ListDelete(&L,j,&e); /* ɾ����5������ */      //��Ϊ��ĺ����Ĳ�����*������������Ҫ&��������ȥ
    printf("ɾ����%d����Ԫ��ֵΪ��%d\n",j,e);

    printf("�������L��Ԫ�أ�");
    ListTraverse(L); 

	//����һ����10������Lb
	i=InitList(&Lb);
    for(j=6;j<=15;j++)
            i=ListInsert(&Lb,1,j);

	unionL(&L,Lb);

	printf("��������ϲ���Lb��L��Ԫ�أ�");
    ListTraverse(L); 

    return 0;
}


/*
* ���㴫��һ��������������ʱ����������᲻���ں����ڱ��Ķ���������ʹ��ʲô������ʽ��
* �����Ҫ���Ķ�������Ҫ����ָ�����������ָ�루&L��   ����Ϊֵ��䣬��ַ�򲻻ᣩ
* �������Ҫ���Ķ��������ֱ�Ӵ����������
*/
