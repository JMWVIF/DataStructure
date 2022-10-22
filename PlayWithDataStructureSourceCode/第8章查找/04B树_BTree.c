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

#define m 3 /* B���Ľף�����Ϊ3 */ 
#define N 17 /* ����Ԫ�ظ��� */ 
#define MAX 5 /* �ַ�����󳤶�+1 */

typedef int Status;	/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */ 

typedef struct BTNode
{
	int keynum; /* ����йؼ��ָ����������Ĵ�С */	//��СΪ1�Ǿ��Ƕ��棬2�������棬3�����Ĳ棬B����(n+1)��
	struct BTNode *parent; /* ָ��˫�׽�� */		//����һ��ָ���д�����൱�����ָ����ָ��BTNode���ṹ�屾�壩
	struct Node /* ����������� */				//�ṹ��Ƕ��
	{
		 int key; /* �ؼ������� */ 
		 struct BTNode *ptr; /* ����ָ������ */ 
		 int recptr; /* ��¼ָ������ */ 
	}node[m+1]; /*  key,recptr��0�ŵ�Ԫ���� */ 
}BTNode,*BTree; /*  B������B�������� */ 

typedef struct
{
	BTNode *pt; /* ָ���ҵ��Ľ�� */ 
	int i;		/* 1..m���ڽ���еĹؼ������ */ 
	int tag;	/* 1:���ҳɹ���O:����ʧ�� */ 
}Result;		/* B���Ĳ��ҽ������ */ 

/* ��p->node[1..keynum].key�в���i,ʹ��p->node[i].key <= K �� p->node[i+1].key */ 
int Search(BTree p, int K)
{ 
	int i=0,j;
	for(j=1;j<=p->keynum;j++)
	 if(p->node[j].key<=K)
	   i=j;
	return i;	//��K��p->node[i].key��p->node[i+1].key֮��
}

/* ��m��B��T�ϲ��ҹؼ���K�����ؽ��(pt,i,tag) */ 
/* �����ҳɹ���������ֵtag=1��ָ��pt��ָ����е�i���ؼ��ֵ���K�� */
/* ��������ֵtag=0������K�Ĺؼ���Ӧ������ָ��Pt��ָ����е�i�͵�i+1���ؼ���֮�䡣*/
Result SearchBTree(BTree T, int K)
{ 
	BTree p=T,q=NULL; /* ��ʼ����pָ������㣬qָ��p��˫�� */
	Status found=FALSE;
	int i=0;
	Result r;	//B���Ĳ��ҽ������
	while(p&&!found)	//p���� && û�ҵ�
	{
	 i=Search(p,K); /* p->node[i].key �� K < p->node[i+1].key */
	 if(i>0 && p->node[i].key==K) /* �ҵ�����ؼ��� */		//ָ��pt��ָ����е�i���ؼ��ֵ���K
	   found=TRUE;
	 else
	 {
	   q=p;
	   p=p->node[i].ptr;	//pָ��������ָ��������ָ�����ƣ�
	 }
	}
	r.i=i;	
	if(found) /* ���ҳɹ� */
	{
	 r.pt=p;	//�ҵ��Ľ��Ϊp
	 r.tag=1;	//����ֵΪ1
	}
	else /* ���Ҳ��ɹ�������K�Ĳ���λ����Ϣ */ 
	{
	 r.pt=q;	//�ҵ��Ľ�㻹��q
	 r.tag=0;	//������ֵ��Ϊ0��
	}
	return r;
}

/* ����r->key������r���͡�ap���ֱ���뵽��q->key[i+1]������q->recptr[i+1]���͡�q->ptr[i+1]���� */
//��������Ĳ���д��������Ӳ������
void Insert(BTree *q,int i,int key,BTree ap)
{ 
	int j;
	for(j=(*q)->keynum;j>i;j--) /* �ճ�(*q)->node[i+1] */
		(*q)->node[j+1]=(*q)->node[j];
	(*q)->node[i+1].key=key;
	(*q)->node[i+1].ptr=ap;
	(*q)->node[i+1].recptr=key;
	(*q)->keynum++;
}

/* �����q���ѳ�������㣬ǰһ�뱣������һ�������������ap */ 
void split(BTree *q,BTree *ap)
{ 
	int i,s=(m+1)/2;
	*ap=(BTree)malloc(sizeof(BTNode)); /* �����½��ap */ 
	(*ap)->node[0].ptr = (*q)->node[s].ptr; /* ��һ������ap */  //��Ϊs=(m+1)/2
	for(i=s+1;i<=m;i++)		//������һ��
	{
		 (*ap)->node[i-s]=(*q)->node[i];	//���ѵĸ��Ʒ�
		 if((*ap)->node[i-s].ptr)			//���ѵĸ��Ʒ�
			(*ap)->node[i-s].ptr->parent=*ap;
	}
	(*ap)->keynum=m-s;	//ǰһ��+1���ӵ��Ǹ���s��
	(*ap)->parent=(*q)->parent;		//���ѵĸ��Ʒ�
	(*q)->keynum=s-1; /* q��ǰһ�뱣�����޸�keynum */ 
}

/* ���ɺ���Ϣ(T,r,ap)���µĸ����&T��ԭT��apΪ����ָ�� */ 
//��������Ĳ���д��������Ӳ������
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

/* ��m��B��T�Ͻ��*q��key[i]��key[i+1]֮�����ؼ���K��ָ��r�������� */ 
/* ������,����˫�������б�Ҫ�Ľ����ѵ���,ʹT����m��B���� */
void InsertBTree(BTree *T,int key,BTree q,int i)
{ 
	BTree ap=NULL;
	Status finished=FALSE;
	int s;
	int rx;
	rx=key;
	while(q && !finished)	//q���� && û�н���
	{
		Insert(&q,i,rx,ap);
		/* ����r->key������r���͡�ap���ֱ���뵽��q->key[i+1]������q->recptr[i+1]���͡�q->ptr[i+1]���� */
		if(q->keynum<m)
			finished=TRUE; /* ������� */ 
		else
		{ /* ���ѽ��*q */ 
			s=(m+1)/2;
			rx=q->node[s].recptr;	//rx����q����������s��ָ������
			split(&q,&ap); /* ��q->key[s+1..m],q->ptr[s..m]��q->recptr[s+1..m]���롾�½��*ap�� */
			q=q->parent;	//qָ���Լ�˫��
			if(q)
				i=Search(q,key); /* ��˫�׽��*q�в���rx->key�Ĳ���λ�� */
		}
	}
	if(!finished) /* T�ǿ���(����q��ֵΪNULL)�������ѷ���Ϊ���*q��*ap */ 
		NewRoot(T,rx,ap); /* ���ɺ���Ϣ(T, rx, ap)���µĸ����*T��ԭT��apΪ����ָ�� */
}


void print(BTNode c,int i) /* TraverseDSTable()���õĺ��� */
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
	printf("\n����������Ҽ�¼�Ĺؼ���: ");
	scanf("%d",&i);
	s=SearchBTree(T,i);
	if(s.tag)
		print(*(s.pt),s.i);
	else
		printf("û�ҵ�");
	printf("\n");

	return 0;
}

//B������Balance Tree��ƽ����
//B���Ĳ���Ч��ȡ���ڷ��ʴ��̵Ĵ���,�ؼ���������ͬ�������B���ĸ߶�ԽС������I/O������ʱ��Խ��

/*һ��m�׵�B�������������ԣ�
1��ÿ���ڵ�������M���ӽڵ㣻
2����K���ӽڵ�ķ�Ҷ�ӽڵ��а���K-1������Key��;
3�����ڵ������������ӽڵ㣨�����ʱB-������ֻ�и��ڵ㣩��
4��ÿ����Ҷ�ӽڵ㣨���ڵ���⣩������Ceil[M/2]���ӽڵ㣻����Ceil��ʾ����ȡ����
5�����е�Ҷ�ӽڵ㶼��ͬһ�㡣
*/

//B����Ϊ���������������ÿһ�ζ�Ҫ����n��ĸ�����㣬Ч�ʵ���



/*һ��m�׵�B+����������������
1. ��k���������м�ڵ������k��Ԫ�أ�B����k-1��Ԫ�أ���ÿ��Ԫ�ز��������ݣ�ֻ�����������������ݶ�������Ҷ�ӽڵ��С�
2. ���е�Ҷ�ӽڵ��а�����ȫ��Ԫ�ص���Ϣ����ָ����ЩԪ�ؼ�¼��ָ�룬��Ҷ�ӽڵ㱾�����ؼ��ֵĴ�С��С����˳�����ӡ�������
3. ���е��м�ڵ�Ԫ�ض�ͬʱ�������ӽڵ㣬���ӽڵ�Ԫ��������󣨻���С��Ԫ�ء�
4. B+������ʱ���������²��ң�B-���Ǵ������ϲ��ң������������
*/

/*���ݿ���������B+������Ҫԭ��:
B���������IO���ܵ�ͬʱ��û�н��Ԫ�ر�����Ч�ʵ��µ����⡣
����Ϊ�˽��������⣬B+��Ӧ�ö�����
B+��ֻ��Ҫȥ����Ҷ�ӽڵ�Ϳ���ʵ���������ı�����
���������ݿ��л��ڷ�Χ�Ĳ�ѯ�Ƿǳ�Ƶ���ģ���B����֧�������Ĳ���
*/

/*B����B+��������
��B+���У�����n���ؼ��ֵĽڵ�ֻ����n����������ÿ���ؼ��ֶ�Ӧһ��������
����B���У�����n���ؼ��ֵĽڵ�ֻ����n+1��������

��B+���У�ÿ����㣨�Ǹ��ڵ㣩�ؼ��ָ���n�ķ�Χ��m/2(����ȡ��)<=n<=m(����㣺1<=n<=m)��
����B���У�ÿ����㣨�Ǹ��ڵ㣩�ؼ��ָ���n�ķ�Χ��m/2(����ȡ��)-1<=n<=m-1(����㣺1<=n<=m-1)��

��B+���У�ֻ�С�Ҷ��㡿������Ϣ�����С���Ҷ��㡿�����������ã�
��Ҷ����е�ÿ��������ֻ���ж�Ӧ���������ؼ��ֺ�ָ���������ָ�룬
�����иùؼ��ֶ�Ӧ��¼�Ĵ洢��ַ��

��B+���У�Ҷ��������ȫ���ؼ��֣����ڷ�Ҷ����г��ֵĹؼ���Ҳ�������Ҷ�ڵ��У�
����B���У�Ҷ�������Ĺؼ��ֺ������������Ĺؼ����ǲ��ظ��ġ�
*/