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

#define SUCCESS 1
#define UNSUCCESS 0
#define HASHSIZE 12 /* ����ɢ�б�Ϊ����ĳ��� */
#define NULLKEY -32768 

typedef int Status;	/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */ 

typedef struct
{
   int *elem; /* ����Ԫ�ش洢��ַ����̬�������� */
   int count; /*  ��ǰ����Ԫ�ظ��� */
}HashTable;

int m=0; /* ɢ�б����ȫ�ֱ��� */

/* ��ʼ��ɢ�б� */
Status InitHashTable(HashTable *H)
{
	int i;
	m=HASHSIZE;
	H->count=m;		//����ֵ���Ǳ�
	H->elem=(int *)malloc(m*sizeof(int));
	for(i=0;i<m;i++)
		H->elem[i]=NULLKEY;		//��ʼ��Ϊ-32768
	return OK;
}

/* ɢ�к��� */
int Hash(int key)
{
	return key % m; /* ���������� */	//ȷ���ڱ���
}

/* ����ؼ��ֽ�ɢ�б� */
void InsertHash(HashTable *H,int key)
{
	int addr = Hash(key); /* ��ɢ�е�ַ */	  //��ַ����ɢ�б���������ӹ���ʵ��
	while (H->elem[addr] != NULLKEY) /* �����Ϊ�գ����ͻ */
	{
		addr = (addr+1) % m; /* ���Ŷ�ַ��������̽�� */	  //����ѭ�������в���
	}
	H->elem[addr] = key; /* ֱ���п�λ�����ؼ��� */	  
}

/* ɢ�б���ҹؼ��� */
Status SearchHash(HashTable H,int key,int *addr)
{
	*addr = Hash(key);  /* ��ɢ�е�ַ */		//��������ֵ��������Ҫ��*��
	while(H.elem[*addr] != key) /* �����Ϊ�գ����ͻ */	  
	{
		*addr = (*addr+1) % m; /* ���Ŷ�ַ��������̽�� */
		if (H.elem[*addr] == NULLKEY || *addr == Hash(key)) /* ���ѭ���ص�ԭ�� */		
			return UNSUCCESS;	/* ��˵���ؼ��ֲ����� */
	}
	return SUCCESS;
}

int main()
{
	int arr[HASHSIZE]={12,67,56,16,25,37,22,29,15,47,48,34};
	int i,p,key,result;
	HashTable H;

	key=39;

	InitHashTable(&H);
	for(i=0;i<m;i++)
		 InsertHash(&H,arr[i]);
	
	result=SearchHash(H,key,&p);
	if (result)
		printf("���� %d �ĵ�ַΪ��%d \n",key,p);
	else
		printf("���� %d ʧ�ܡ�\n",key);

	for(i=0;i<m;i++)
	{
		key=arr[i];
		SearchHash(H,key,&p);
		printf("���� %d �ĵ�ַΪ��%d \n",key,p);
	}

	return 0;
}


//ɢ�м������ڼ�¼�Ĵ洢λ�ú����Ĺؼ���֮�佨��һ��ȷ���Ķ�Ӧ��ϵf��ʹ��ÿ���ؼ���key��Ӧһ���洢λ��f(key)��
//����������ʱ���������ȷ���Ķ�Ӧ��ϵ�����ҵ�key��ӳ�䣨ָ�룩f(key)��

//����ɢ�м�������¼�洢��һ�������Ĵ洢�ռ��У���������洢�ռ��Ϊɢ�б�/��ϣ��
//ɢ�м�������һ�ִ洢������Ҳ��һ�ֲ��ҷ���
//ɢ�м����ļ�¼���¼֮�䣬������ʲô�߼���ϵ����¼ֻ��ؼ����й���

//ɢ�б��ʺϲ������ֲ�������Ҫ��ߣ���¼֮���ϵ��Ҫ�������
//ɢ�б��ʺ�������Ҫ���ٷ��ʵ����
//ɢ�м������ʺϵ���������ǣ����������ֵ��ȵļ�¼