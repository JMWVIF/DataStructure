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

#define MAXSIZE 40 /* 存储空间初始分配量 */

typedef int Status;		/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType;	/* ElemType类型根据实际情况而定，这里假设为int */

typedef char String[MAXSIZE+1]; /*  0号单元存放串的长度 */

/* 生成一个其值等于chars的串T */
Status StrAssign(String T,char *chars)
{ 
	int i;
	if(strlen(chars)>MAXSIZE)	//串超过预定的最大值（相当于数组的溢出）
		return ERROR;
	else
	{
		T[0]=strlen(chars);		//头部记录有多长
		for(i=1;i<=T[0];i++)
			T[i]=*(chars+i-1);	//T[i]的值就是串T的各个类数组值，只不过从[1]开始存储字符串的数据
		return OK;
	}
}

/* 由串S复制得串T */					//复制
Status StrCopy(String T,String S)
{ 
	int i;
	for(i=0;i<=S[0];i++)
		T[i]=S[i];
	return OK;
}

/* 若S为空串,则返回TRUE,否则返回FALSE */
Status StrEmpty(String S)
{ 
	if(S[0]==0)
		return TRUE;
	else
		return FALSE;
}

/*  初始条件: 串S和T存在 */
/*  操作结果: 若S>T,则返回值>0;若S=T,则返回值=0;若S<T,则返回值<0 */
int StrCompare(String S,String T)
{ 
	int i;
	for(i=1;i <= S[0] && i <= T[0];++i)		//就是相当于strlen(S) && strlen(T)
		if(S[i]!=T[i])
			return S[i]-T[i];		//>、=、<
	return S[0]-T[0];		//这是如果什么都相等的话，那么返回的默认值
}

/* 返回串的元素个数 */
int StrLength(String S)
{ 
	return S[0];		//S[0]存储着strlen(S)的信息
}

/* 初始条件:串S存在。操作结果:将S清为空串 */
Status ClearString(String S)
{ 
	S[0]=0;	/* 串长为零 */
	//实际上没有真正清空，只不过为了让后面的函数识别到清空，而做此下策
	return OK;
}

/* 用T返回S1和S2联接而成的新串。若未截断，则返回TRUE，否则FALSE */
Status Concat(String T,String S1,String S2)		//在之前，S1和S2已连接成新串了
{
	int i;
	if(S1[0]+S2[0]<=MAXSIZE)
	{ /* 未截断 */
		for(i=1;i<=S1[0];i++)		//把S1的给连接到T上
			T[i]=S1[i];
		for(i=1;i<=S2[0];i++)		//把S2的给连接到T上
			T[S1[0]+i]=S2[i];	
		T[0]=S1[0]+S2[0];			
		return TRUE;
	}
	else
	{ /* 截断S2 */
		for(i=1;i<=S1[0];i++)
			T[i]=S1[i];
		for (i = 1; i <= MAXSIZE - S1[0]; i++)	//安装S2[i],能装多少就装多少
			T[S1[0]+i]=S2[i];		//因为范围被框死了，所以赋值的指令可以不变
		T[0]=MAXSIZE;		//因为是两个串大于容纳串（T），所以直接设置成MAXSIZE
		return FALSE;
	}
}

/* 用Sub返回串S的第pos个字符起长度为len的子串。 */
Status SubString(String Sub,String S,int pos,int len)
{
	int i;
	if(pos<1||pos>S[0]||len<0||len>S[0]-pos+1)	//这些都是错误的
	//第0个开始 || 第pos个大于整个串的长度 || 新串长度<0 || 新串长度 >（整个串的长度 - 第pos个 + 1）
		//（+1）就是指S[0]是原来数组的长度值，但是第四个“||”的是需要 = 才是正确的
		return ERROR;
	for(i=1;i<=len;i++)
		Sub[i]=S[pos+i-1];	//返回第pos个起的串用
	Sub[0]=len;		//串头值 = 长度
	return OK;
}

/* 返回子串T在主串S中第pos个字符之后的位置。若不存在,则函数返回值为0。 */
/* 其中,T非空,1≤pos≤StrLength(S)。 */
/* 朴素的模式匹配法 */

//思路：对主串做大循环，每个字符开头做strlen(T)-1的小循环，直到匹配成功/全部遍历一遍后停止(可是这样很低效)
int Index(String S, String T, int pos) 
{
	int i = pos;	/* i用于主串S中当前位置下标值，若pos不为1，则从pos位置开始匹配 */
	int j = 1;				/* j用于子串T中当前位置下标值 */
	while (i <= S[0] && j <= T[0]) /* 若i小于S的长度并且j小于T的长度时，循环继续 */
	{
		if (S[i] == T[j]) 	/* 两字母相等则继续 */
      	{
			++i;
         	++j; 
      	} 
      	else 				/* 指针后退重新开始匹配 */
      	{  
         	i = i-j+2;		/* i退回到上次匹配首位的下一位 */
         	j = 1; 			/* j退回到子串T的首位 */	//T[0]是数值，T[1]才是串真正的首位
      	}      
	}
	if (j > T[0])		//子串的下标值 > 子串的长度（相当于遍历完毕时）
		return i-T[0];	//返回子串T在主串S中第pos个字符之后的位置（在第几个字符串的时候开始相同）
	else 
		return 0;
}


/*  T为非空串。若主串S中第pos个字符之后存在与T相等的子串， */
/*  则返回第一个这样的子串在S中的位置，否则返回0 */
int Index2(String S, String T, int pos) 
{
	int n,m,i;
	String sub;
	if (pos > 0) 
	{
		n = StrLength(S);	/* 得到主串S的长度 */
		m = StrLength(T);	/* 得到子串T的长度 */
		i = pos;
		while (i <= n-m+1) 
		{
			SubString (sub, S, i, m);	/* 取主串中第i个位置长度与T相等的子串给sub */
			if (StrCompare(sub,T) != 0)    /* 如果两串不相等 */
				++i;
			else 				/* 如果两串相等 */
				return i;		/* 则返回i值 */		//返回相同串的串（字符类型的）头
		}
	}
	return 0;	/* 若无子串与T相等，返回0 */
}


/*  初始条件: 串S和T存在,1≤pos≤StrLength(S)+1 */
/*  操作结果: 在串S的第pos个字符之前插入串T。完全插入返回TRUE,部分插入返回FALSE */
Status StrInsert(String S,int pos,String T)
{ 
	int i;
	if(pos<1||pos>S[0]+1)
		//第0个开始 || 第pos个 > 整个串的长度 + 1
		return ERROR;
	if(S[0]+T[0]<=MAXSIZE)
	{ /*  完全插入 */
		for(i=S[0];i>=pos;i--)
			S[i+T[0]]=S[i];			//串S的第pos个字符后复制S
		for(i=pos;i<pos+T[0];i++)
			S[i]=T[i-pos+1];		//串S的第pos个字符前插入T
		S[0]=S[0]+T[0];
		return TRUE;
	}
	else
	{ /*  部分插入 */
		for(i=MAXSIZE;i<=pos;i--)
			S[i]=S[i-T[0]];
		for(i=pos;i<pos+T[0];i++)	//范围缩小，范围内的代码不变
			S[i]=T[i-pos+1];
		S[0]=MAXSIZE;
		return FALSE;
	}
}

/*  初始条件: 串S存在,1≤pos≤StrLength(S)-len+1 */
/*  操作结果: 从串S中删除第pos个字符起长度为len的子串 */
Status StrDelete(String S,int pos,int len)
{ 
	int i;
	if(pos<1||pos>S[0]-len+1||len<0)
		//上面已经注释过一遍，这里不再注释
		return ERROR;
	for(i=pos+len;i<=S[0];i++)	
		S[i-len]=S[i];
	S[0]-=len;		//串头更新
	return OK;
}

/*  初始条件: 串S,T和V存在,T是非空串（此函数与串的存储结构无关） */
/*  操作结果: 用V替换主串S中出现的所有与T相等的不重叠的子串 */	
//S:a00a00a00,T:00,V:11 -> 新的S:a11a11a11
Status Replace(String S,String T,String V)
{ 
	int i=1; /*  从串S的第一个字符起查找串T */	//从S[0]开始错,从S[1]开始对
	if(StrEmpty(T)) /*  T是空串 */
		return ERROR;
	do
	{
		i=Index(S,T,i); /*  结果i为从上一个i之后找到的子串T的位置 */
		if(i) /*  串S中存在串T */
		{
			StrDelete(S,i,StrLength(T)); /*  删除该串T */		//结束后这里会触发自己写的安全级制，让i终止循环
			StrInsert(S,i,V); /*  在原串T的位置插入串V */		//其实这里也有安全级制，不过往往不会被执行
			i+=StrLength(V); /*  在插入的串V后面继续查找串T */
		}
	}while(i);
	//整个流程就是 删除、插入、继续查找
	return OK;
}

/*  输出字符串T */	//只是个子串
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
	printf("请输入串s1: ");
	
	k=StrAssign(s1,"abcd");
	if(!k)
	{
		printf("串长超过MAXSIZE(=%d)\n",MAXSIZE);
		exit(0);
	}
	printf("串长为%d 串空否？%d(1:是 0:否)\n",StrLength(s1),StrEmpty(s1));
	StrCopy(s2,s1);
	printf("拷贝s1生成的串为: ");
	StrPrint(s2);
	printf("请输入串s2: ");
	
	k=StrAssign(s2,"efghijk");
	if(!k)
	{
		printf("串长超过MAXSIZE(%d)\n",MAXSIZE);
		exit(0);
	}
	i=StrCompare(s1,s2);
	if(i<0)
		s='<';
	else if(i==0)
		s='=';
	else
		s='>';
	printf("串s1%c串s2\n",s);
	k=Concat(t,s1,s2);
	printf("串s1联接串s2得到的串t为: ");
	StrPrint(t);
	if(k==FALSE)
		printf("串t有截断\n");
	ClearString(s1);
	printf("清为空串后,串s1为: ");
	StrPrint(s1);
	printf("串长为%d 串空否？%d(1:是 0:否)\n",StrLength(s1),StrEmpty(s1));
	printf("求串t的子串,请输入子串的起始位置,子串长度: ");

	i=2;
	j=3;
	printf("%d,%d \n",i,j);

	k=SubString(s2,t,i,j);
	if(k)
	{
		printf("子串s2为: ");
		StrPrint(s2);
	}
	printf("从串t的第pos个字符起,删除len个字符，请输入pos,len: ");
	
	i=4;
	j=2;
	printf("%d,%d \n",i,j);


	StrDelete(t,i,j);
	printf("删除后的串t为: ");
	StrPrint(t);
	i=StrLength(s2)/2;
	StrInsert(s2,i,t);
	printf("在串s2的第%d个字符之前插入串t后,串s2为:\n",i);
	StrPrint(s2);
	i=Index(s2,t,1);
	printf("s2的第%d个字母起和t第一次匹配\n",i);
	SubString(t,s2,1,1);
	printf("串t为：");
	StrPrint(t);
	Concat(s1,t,t);
	printf("串s1为：");
	StrPrint(s1);
	Replace(s2,t,s1);
	printf("用串s1取代串s2中和串t相同的不重叠的串后,串s2为: ");
	StrPrint(s2);


	return 0;
}

