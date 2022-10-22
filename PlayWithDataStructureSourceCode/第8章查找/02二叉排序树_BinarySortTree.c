#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100 /* �洢�ռ��ʼ������ */

typedef int Status;	/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */ 

/* �������Ķ���������ṹ���� */
typedef  struct BiTNode	/* ���ṹ */
{
	int data;	/* ������� */
	struct BiTNode *lchild, *rchild;	/* ���Һ���ָ�� */
} BiTNode, *BiTree;


/* �ݹ���Ҷ���������T���Ƿ����key, */
/* ָ��fָ��T��˫�ף����ʼ����ֵΪNULL */
/* �����ҳɹ�����ָ��pָ�������Ԫ�ؽ�㣬������TRUE */
/* ����ָ��pָ�����·���Ϸ��ʵ����һ����㲢����FALSE */
Status SearchBST(BiTree T, int key, BiTree f, BiTree *p) 
{  
	if (!T)	/*  ���Ҳ��ɹ� */
	{ 
		*p = f;  
		return FALSE; 
	}
	else if (key==T->data) /*  ���ҳɹ� */
	{ 
		*p = T;  
		return TRUE; 
	} 
	else if (key<T->data) 
		return SearchBST(T->lchild, key, T, p);  /*  ���������м������� */
	else  
		return SearchBST(T->rchild, key, T, p);  /*  ���������м������� */
}


/*  ������������T�в����ڹؼ��ֵ���key������Ԫ��ʱ�� */
/*  ����key������TRUE�����򷵻�FALSE */
Status InsertBST(BiTree *T, int key) 
{  
	BiTree p,s;
	if (!SearchBST(*T, key, NULL, &p)) /* ���Ҳ��ɹ� */		//��ʼ���в������ 
	{
		s = (BiTree)malloc(sizeof(BiTNode));
		s->data = key;  		//�������ֵ 
		s->lchild = s->rchild = NULL;  		//��ʼ��s�����Ӻ��Һ��ӣ��Ͼ�����û�к��ӣ� 
		if (!p) 	//�������������ڣ�û����T�� 
			*T = s;			/*  ����sΪ�µĸ���� */
		else if (key < p->data) 
			p->lchild = s;	/*  ����sΪ���� */	//s��p������ 
		else 
			p->rchild = s;  /*  ����sΪ�Һ��� */	//s��p���Һ��� 
		return TRUE;
	} 
	else 
		return FALSE;  /*  �������йؼ�����ͬ�Ľ�㣬���ٲ��� */
}

/* �Ӷ�����������ɾ�����p�����ؽ���������������� */
Status Delete(BiTree *p)
{
	BiTree q,s;
	if((*p)->rchild==NULL) /* ����������ֻ���ؽ���������������ɾ�����Ҷ��Ҳ�ߴ˷�֧) */		//����Ҷ�ӽ�㡢������Ϊ�յĽ��
	{
		q=*p; 
		*p=(*p)->lchild; 		//������ȥ�ӳи�ҵ 
		free(q);
	}
	else if((*p)->lchild==NULL) /* ֻ���ؽ����������� */								//����Ҷ�ӽ�㡢������Ϊ�յĽ��
	{
		q=*p; 
		*p=(*p)->rchild;		//������ȥ�ӳи�ҵ 
		free(q);
	}
	else /* �������������� */		//�������Ǽ����������������������Ľڹ��۽��				//�����������������յĽ��
	{
		q=*p;
		s=(*p)->lchild;	//���ߵ�������
		while(s->rchild) /* ת��Ȼ�����ҵ���ͷ���Ҵ�ɾ����ǰ���� */		//һֱ�ң�ֱ�������������ҽ��
		{
			q=s;
			s=s->rchild;
		}
		(*p)->data = s->data; /* sָ��ɾ����ֱ��ǰ��������ɾ���ǰ����ֵȡ����ɾ����ֵ�� */		//ֱ�Ӹ��㻻��
		if(q!=*p)
			q->rchild=s->lchild; /* �ؽ�q�������� */  //��Ϊs��㱻������q�ĸ�������ˣ�����s�������q���ҽ����
		else
			q->lchild=s->lchild; /* �ؽ�q�������� */	//����ͬ��
		free(s);
	}
	return TRUE;
}

/* ������������T�д��ڹؼ��ֵ���key������Ԫ��ʱ����ɾ��������Ԫ�ؽ��, */
/* ������TRUE�����򷵻�FALSE�� */
Status DeleteBST(BiTree *T,int key)
{ 
	if(!*T) /* �����ڹؼ��ֵ���key������Ԫ�� */ 
		return FALSE;		//ɾ��ʧ�ܣ���Ϊ���Ͳ����ڣ�û��Ҫɾ�� 
	else
	{
		if (key==(*T)->data) /* �ҵ��ؼ��ֵ���key������Ԫ�� */ 
			return Delete(T);
		else if (key < (*T)->data)					//��ɾ 
			return DeleteBST(&(*T)->lchild,key);
		else										//��ɾ 
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
    printf("����������ϵ���ٲ鿴�����������ṹ");
	return 0;
}

/*�����������ǰ����������֯Ϊ���Խṹ�����Ϊ������
�������������֣������������ֿ���������������

�����������������������У������ݼ��е�ÿһ����¼����Ӧһ�����������ָ��Ϊ����ȥ���ң�
���ڳ����������ԣ�������һ���ǰ��չؼ����������е�
��������ֻ���������ݼ�С�ģ���ΪҪ׼�������ݼ�ͬ�ȳ��ȵ�������ģ


�ֿ����������Ȱ����ݼ��ļ�¼�ֳ����ɿ飬��Щ�鶼��ѭ�š��������򡿺͡�������򡿵�������
�ֿ�����ʵ�����Ƿֲ㻯�ĳ����������ֳ����ɵĿ飬һ���Ͻ��һ����Χ�����ǰ����ſ鳤����Ϊ�����鳤���ǲ����ģ�


������������¼�ű����ʱ�ţ��洢������ͬ�ιؼ��֣�Ӣ�ĵ��ʣ������м�¼�ļ�¼��
������ָ���¼��ָ�룬�����Ǹü�¼�����ؼ��֡�
�ִ�����������������ǻ��ڵ���������Ȼ����������㷨������
���������������ٶȷǳ��죬���Ǽ�¼�ţ����ʣ��ǲ������ȵģ�ά���Ƚ����ѣ�����ɾ��������ٽ��в���
*/

//���ﹹ��һ�ö�������������Ŀ�Ĳ�����Ϊ�����򣬶���Ϊ����߲��ҡ����롢ɾ����Ч��
