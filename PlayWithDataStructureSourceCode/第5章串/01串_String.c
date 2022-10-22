#include "string.h"
#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 40 /* �洢�ռ��ʼ������ */

typedef int Status;		/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef int ElemType;	/* ElemType���͸���ʵ������������������Ϊint */

typedef char String[MAXSIZE+1]; /*  0�ŵ�Ԫ��Ŵ��ĳ��� */

/* ����һ����ֵ����chars�Ĵ�T */
Status StrAssign(String T,char *chars)
{ 
	int i;
	if(strlen(chars)>MAXSIZE)	//������Ԥ�������ֵ���൱������������
		return ERROR;
	else
	{
		T[0]=strlen(chars);		//ͷ����¼�ж೤
		for(i=1;i<=T[0];i++)
			T[i]=*(chars+i-1);	//T[i]��ֵ���Ǵ�T�ĸ���������ֵ��ֻ������[1]��ʼ�洢�ַ���������
		return OK;
	}
}

/* �ɴ�S���Ƶô�T */					//����
Status StrCopy(String T,String S)
{ 
	int i;
	for(i=0;i<=S[0];i++)
		T[i]=S[i];
	return OK;
}

/* ��SΪ�մ�,�򷵻�TRUE,���򷵻�FALSE */
Status StrEmpty(String S)
{ 
	if(S[0]==0)
		return TRUE;
	else
		return FALSE;
}

/*  ��ʼ����: ��S��T���� */
/*  �������: ��S>T,�򷵻�ֵ>0;��S=T,�򷵻�ֵ=0;��S<T,�򷵻�ֵ<0 */
int StrCompare(String S,String T)
{ 
	int i;
	for(i=1;i <= S[0] && i <= T[0];++i)		//�����൱��strlen(S) && strlen(T)
		if(S[i]!=T[i])
			return S[i]-T[i];		//>��=��<
	return S[0]-T[0];		//�������ʲô����ȵĻ�����ô���ص�Ĭ��ֵ
}

/* ���ش���Ԫ�ظ��� */
int StrLength(String S)
{ 
	return S[0];		//S[0]�洢��strlen(S)����Ϣ
}

/* ��ʼ����:��S���ڡ��������:��S��Ϊ�մ� */
Status ClearString(String S)
{ 
	S[0]=0;	/* ����Ϊ�� */
	//ʵ����û��������գ�ֻ����Ϊ���ú���ĺ���ʶ����գ��������²�
	return OK;
}

/* ��T����S1��S2���Ӷ��ɵ��´�����δ�ضϣ��򷵻�TRUE������FALSE */
Status Concat(String T,String S1,String S2)		//��֮ǰ��S1��S2�����ӳ��´���
{
	int i;
	if(S1[0]+S2[0]<=MAXSIZE)
	{ /* δ�ض� */
		for(i=1;i<=S1[0];i++)		//��S1�ĸ����ӵ�T��
			T[i]=S1[i];
		for(i=1;i<=S2[0];i++)		//��S2�ĸ����ӵ�T��
			T[S1[0]+i]=S2[i];	
		T[0]=S1[0]+S2[0];			
		return TRUE;
	}
	else
	{ /* �ض�S2 */
		for(i=1;i<=S1[0];i++)
			T[i]=S1[i];
		for (i = 1; i <= MAXSIZE - S1[0]; i++)	//��װS2[i],��װ���پ�װ����
			T[S1[0]+i]=S2[i];		//��Ϊ��Χ�������ˣ����Ը�ֵ��ָ����Բ���
		T[0]=MAXSIZE;		//��Ϊ���������������ɴ���T��������ֱ�����ó�MAXSIZE
		return FALSE;
	}
}

/* ��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ��� */
Status SubString(String Sub,String S,int pos,int len)
{
	int i;
	if(pos<1||pos>S[0]||len<0||len>S[0]-pos+1)	//��Щ���Ǵ����
	//��0����ʼ || ��pos�������������ĳ��� || �´�����<0 || �´����� >���������ĳ��� - ��pos�� + 1��
		//��+1������ָS[0]��ԭ������ĳ���ֵ�����ǵ��ĸ���||��������Ҫ = ������ȷ��
		return ERROR;
	for(i=1;i<=len;i++)
		Sub[i]=S[pos+i-1];	//���ص�pos����Ĵ���
	Sub[0]=len;		//��ͷֵ = ����
	return OK;
}

/* �����Ӵ�T������S�е�pos���ַ�֮���λ�á���������,��������ֵΪ0�� */
/* ����,T�ǿ�,1��pos��StrLength(S)�� */
/* ���ص�ģʽƥ�䷨ */

//˼·������������ѭ����ÿ���ַ���ͷ��strlen(T)-1��Сѭ����ֱ��ƥ��ɹ�/ȫ������һ���ֹͣ(���������ܵ�Ч)
int Index(String S, String T, int pos) 
{
	int i = pos;	/* i��������S�е�ǰλ���±�ֵ����pos��Ϊ1�����posλ�ÿ�ʼƥ�� */
	int j = 1;				/* j�����Ӵ�T�е�ǰλ���±�ֵ */
	while (i <= S[0] && j <= T[0]) /* ��iС��S�ĳ��Ȳ���jС��T�ĳ���ʱ��ѭ������ */
	{
		if (S[i] == T[j]) 	/* ����ĸ�������� */
      	{
			++i;
         	++j; 
      	} 
      	else 				/* ָ��������¿�ʼƥ�� */
      	{  
         	i = i-j+2;		/* i�˻ص��ϴ�ƥ����λ����һλ */
         	j = 1; 			/* j�˻ص��Ӵ�T����λ */	//T[0]����ֵ��T[1]���Ǵ���������λ
      	}      
	}
	if (j > T[0])		//�Ӵ����±�ֵ > �Ӵ��ĳ��ȣ��൱�ڱ������ʱ��
		return i-T[0];	//�����Ӵ�T������S�е�pos���ַ�֮���λ�ã��ڵڼ����ַ�����ʱ��ʼ��ͬ��
	else 
		return 0;
}


/*  TΪ�ǿմ���������S�е�pos���ַ�֮�������T��ȵ��Ӵ��� */
/*  �򷵻ص�һ���������Ӵ���S�е�λ�ã����򷵻�0 */
int Index2(String S, String T, int pos) 
{
	int n,m,i;
	String sub;
	if (pos > 0) 
	{
		n = StrLength(S);	/* �õ�����S�ĳ��� */
		m = StrLength(T);	/* �õ��Ӵ�T�ĳ��� */
		i = pos;
		while (i <= n-m+1) 
		{
			SubString (sub, S, i, m);	/* ȡ�����е�i��λ�ó�����T��ȵ��Ӵ���sub */
			if (StrCompare(sub,T) != 0)    /* ������������ */
				++i;
			else 				/* ���������� */
				return i;		/* �򷵻�iֵ */		//������ͬ���Ĵ����ַ����͵ģ�ͷ
		}
	}
	return 0;	/* �����Ӵ���T��ȣ�����0 */
}


/*  ��ʼ����: ��S��T����,1��pos��StrLength(S)+1 */
/*  �������: �ڴ�S�ĵ�pos���ַ�֮ǰ���봮T����ȫ���뷵��TRUE,���ֲ��뷵��FALSE */
Status StrInsert(String S,int pos,String T)
{ 
	int i;
	if(pos<1||pos>S[0]+1)
		//��0����ʼ || ��pos�� > �������ĳ��� + 1
		return ERROR;
	if(S[0]+T[0]<=MAXSIZE)
	{ /*  ��ȫ���� */
		for(i=S[0];i>=pos;i--)
			S[i+T[0]]=S[i];			//��S�ĵ�pos���ַ�����S
		for(i=pos;i<pos+T[0];i++)
			S[i]=T[i-pos+1];		//��S�ĵ�pos���ַ�ǰ����T
		S[0]=S[0]+T[0];
		return TRUE;
	}
	else
	{ /*  ���ֲ��� */
		for(i=MAXSIZE;i<=pos;i--)
			S[i]=S[i-T[0]];
		for(i=pos;i<pos+T[0];i++)	//��Χ��С����Χ�ڵĴ��벻��
			S[i]=T[i-pos+1];
		S[0]=MAXSIZE;
		return FALSE;
	}
}

/*  ��ʼ����: ��S����,1��pos��StrLength(S)-len+1 */
/*  �������: �Ӵ�S��ɾ����pos���ַ��𳤶�Ϊlen���Ӵ� */
Status StrDelete(String S,int pos,int len)
{ 
	int i;
	if(pos<1||pos>S[0]-len+1||len<0)
		//�����Ѿ�ע�͹�һ�飬���ﲻ��ע��
		return ERROR;
	for(i=pos+len;i<=S[0];i++)	
		S[i-len]=S[i];
	S[0]-=len;		//��ͷ����
	return OK;
}

/*  ��ʼ����: ��S,T��V����,T�Ƿǿմ����˺����봮�Ĵ洢�ṹ�޹أ� */
/*  �������: ��V�滻����S�г��ֵ�������T��ȵĲ��ص����Ӵ� */	
//S:a00a00a00,T:00,V:11 -> �µ�S:a11a11a11
Status Replace(String S,String T,String V)
{ 
	int i=1; /*  �Ӵ�S�ĵ�һ���ַ�����Ҵ�T */	//��S[0]��ʼ��,��S[1]��ʼ��
	if(StrEmpty(T)) /*  T�ǿմ� */
		return ERROR;
	do
	{
		i=Index(S,T,i); /*  ���iΪ����һ��i֮���ҵ����Ӵ�T��λ�� */
		if(i) /*  ��S�д��ڴ�T */
		{
			StrDelete(S,i,StrLength(T)); /*  ɾ���ô�T */		//����������ᴥ���Լ�д�İ�ȫ���ƣ���i��ֹѭ��
			StrInsert(S,i,V); /*  ��ԭ��T��λ�ò��봮V */		//��ʵ����Ҳ�а�ȫ���ƣ������������ᱻִ��
			i+=StrLength(V); /*  �ڲ���Ĵ�V����������Ҵ�T */
		}
	}while(i);
	//�������̾��� ɾ�������롢��������
	return OK;
}

/*  ����ַ���T */	//ֻ�Ǹ��Ӵ�
void StrPrint(String T)
{ 
	int i;
	for(i=1;i<=T[0];i++)
		printf("%c",T[i]);
	printf("\n");
}


int main()
{
	
	int i,j;
	Status k;
	char s;
	String t,s1,s2;
	printf("�����봮s1: ");
	
	k=StrAssign(s1,"abcd");
	if(!k)
	{
		printf("��������MAXSIZE(=%d)\n",MAXSIZE);
		exit(0);
	}
	printf("����Ϊ%d ���շ�%d(1:�� 0:��)\n",StrLength(s1),StrEmpty(s1));
	StrCopy(s2,s1);
	printf("����s1���ɵĴ�Ϊ: ");
	StrPrint(s2);
	printf("�����봮s2: ");
	
	k=StrAssign(s2,"efghijk");
	if(!k)
	{
		printf("��������MAXSIZE(%d)\n",MAXSIZE);
		exit(0);
	}
	i=StrCompare(s1,s2);
	if(i<0)
		s='<';
	else if(i==0)
		s='=';
	else
		s='>';
	printf("��s1%c��s2\n",s);
	k=Concat(t,s1,s2);
	printf("��s1���Ӵ�s2�õ��Ĵ�tΪ: ");
	StrPrint(t);
	if(k==FALSE)
		printf("��t�нض�\n");
	ClearString(s1);
	printf("��Ϊ�մ���,��s1Ϊ: ");
	StrPrint(s1);
	printf("����Ϊ%d ���շ�%d(1:�� 0:��)\n",StrLength(s1),StrEmpty(s1));
	printf("��t���Ӵ�,�������Ӵ�����ʼλ��,�Ӵ�����: ");

	i=2;
	j=3;
	printf("%d,%d \n",i,j);

	k=SubString(s2,t,i,j);
	if(k)
	{
		printf("�Ӵ�s2Ϊ: ");
		StrPrint(s2);
	}
	printf("�Ӵ�t�ĵ�pos���ַ���,ɾ��len���ַ���������pos,len: ");
	
	i=4;
	j=2;
	printf("%d,%d \n",i,j);


	StrDelete(t,i,j);
	printf("ɾ����Ĵ�tΪ: ");
	StrPrint(t);
	i=StrLength(s2)/2;
	StrInsert(s2,i,t);
	printf("�ڴ�s2�ĵ�%d���ַ�֮ǰ���봮t��,��s2Ϊ:\n",i);
	StrPrint(s2);
	i=Index(s2,t,1);
	printf("s2�ĵ�%d����ĸ���t��һ��ƥ��\n",i);
	SubString(t,s2,1,1);
	printf("��tΪ��");
	StrPrint(t);
	Concat(s1,t,t);
	printf("��s1Ϊ��");
	StrPrint(s1);
	Replace(s2,t,s1);
	printf("�ô�s1ȡ����s2�кʹ�t��ͬ�Ĳ��ص��Ĵ���,��s2Ϊ: ");
	StrPrint(s2);


	return 0;
}

