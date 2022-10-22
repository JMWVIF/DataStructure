#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100 /* 存储空间初始分配量 */

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */ 

int F[100]; /* 斐波那契数列 */

/* 无哨兵顺序查找，a为数组，n为要查找的数组个数，key为要查找的关键字 */
int Sequential_Search(int *a,int n,int key)
{
	int i;
	for(i=1;i<=n;i++)
	{
		if (a[i]==key)
			return i;
	}
	return 0;
}
/* 有哨兵顺序查找 */	//相比for循环，省去有没有越n界
int Sequential_Search2(int *a,int n,int key)
{
	int i;
	a[0]=key;	//这就是哨兵
	i=n;
	while(a[i]!=key)	//哨兵的存在，使得只需要判断是否相等就可以进行循环
	{
		i--;
	}
	return i;
}

/* 折半查找 */	//时间复杂度为O(logn)
int Binary_Search(int *a,int n,int key)
{
	int low,high,mid;
	low=1;	/* 定义最低下标为记录首位 */
	high=n;	/* 定义最高下标为记录末位 */
	while(low<=high)
	{
		mid=(low+high)/2;	/* 折半 */
		if (key<a[mid])		/* 若查找值比中值小 */
			high=mid-1;		/* 最高下标调整到中位下标小一位 */	//只是下标，不是里头的数值
		else if (key>a[mid])/* 若查找值比中值大 */
			low=mid+1;		/* 最低下标调整到中位下标大一位 */
		else
		{
			return mid;		/* 若相等则说明mid即为查找到的位置 */
		}
		
	}
	return 0;
}

/* 插值查找 */	
int Interpolation_Search(int *a,int n,int key)
{
	int low,high,mid;
	low=1;	/* 定义最低下标为记录首位 */
	high=n;	/* 定义最高下标为记录末位 */
	while(low<=high)
	{//只是在折半查找的基础上修改了下一行
		mid = low+(high-low)*(key-a[low]) / (a[high]-a[low]); /* 插值 */	 //死记硬背这个公式即可
		if (key<a[mid])		/* 若查找值比插值小 */
			high=mid-1;		/* 最高下标调整到插值下标小一位 */
		else if (key>a[mid])/* 若查找值比插值大 */
			low=mid+1;		/* 最低下标调整到插值下标大一位 */
		else
			return mid;		/* 若相等则说明mid即为查找到的位置 */
	}
	return 0;
}

/* 斐波那契查找 */		//利用黄金分割来查找
//1，1，2，3，5，8，13，21，34，55 这是斐波那契数列的前10个，所以是放在【下标】上进行加减
int Fibonacci_Search(int *a,int n,int key)
{
	int low,high,mid,i,k=0;
	low=1;	/* 定义最低【下标】为记录首位 */
	high=n;	/* 定义最高【下标】为记录末位 */		
	while(n>F[k]-1)		//计算n位斐波那契数列的位置，是计算k在斐波那契数列中的F(k)与F(k+1)之间（若等于F(k)，则还要+1）
		k++;	//k是下标，F[k]才是值
	for(i=n;i<F[k]-1;i++)	//将不满的数值给补全（因为F(k)<n<F(k+1)，所以是n~F(k+1)的范围）
		a[i]=a[n];
	
	while(low<=high)
	{
		mid=low+F[k-1]-1;	//计算当前分隔的【下标】		只不过相比于折半查找，是mid值的公式改成了这样而已
		if (key<a[mid])		//如果查找记录 < 当前分隔记录
		{
			high=mid-1;		//最高下标调整到分隔下标mid+1处
			k=k-1;			//斐波那契数列的下标-1		新的范围：low~mid-1，共有F(k-1)-1个
		}
		else if (key>a[mid])	//（在数组的右侧）
		{
			low=mid+1;		//最低下标，那就是mid+1了	
			k=k-2;			//斐波那契数列下标-2		新的范围：mid+1~high，共有F(k-2)-1个
		}
		else
		{
			if (mid<=n)			//mid与n还在F(k-1)的范围内
				return mid;		/* 若相等则说明mid即为查找到的位置 */
			else 
				return n;  //如果mid>n，说明是补全数值，进入扩展数组的填充部分。即最后一个数就是要查找的数,那就返回n
			
		}
	}
	return 0;
}




  

int main(void)
{    

	int a[MAXSIZE+1],i,result;
	int arr[MAXSIZE]={0,1,16,24,35,47,59,62,73,88,99};
		
	for(i=0;i<=MAXSIZE;i++)
	{
		a[i]=i;
	}
	result=Sequential_Search(a,MAXSIZE,MAXSIZE);
	printf("Sequential_Search:%d \n",result);
	result=Sequential_Search2(a,MAXSIZE,1);
	printf("Sequential_Search2:%d \n",result);

	result=Binary_Search(arr,10,62);
	printf("Binary_Search:%d \n",result);

	
	result=Interpolation_Search(arr,10,62);
	printf("Interpolation_Search:%d \n",result);

	
	F[0]=0;
	F[1]=1;
	for(i = 2;i < 100;i++)  
	{ 
		F[i] = F[i-1] + F[i-2];  
	} 
	result=Fibonacci_Search(arr,10,62);
	printf("Fibonacci_Search:%d \n",result);
	
	return 0;
}

/*
静态查找表：只作查找操作的查找表。
* 其主要操作：
* 1.查询某个“特定的”数据元素是否在查找表中。
* 2.检索某个“特定的”数据元素和各种属性。
* 
动态查找表：在查找过程中同时插入查找表中不存在的数据元素，或者从表中删除某个存在的元素。
* 其主要操作：
* 1.插入
* 2.删除
*/

//静态查找表就用线性表结构即可。

//插值查找的时间复杂度虽然也是O(logn)
//但是对于表长较大，关键字分布比较均匀时，效率比折半查找好太多了

//斐波那契查找时间复杂度也是O(logn)，但是是仅限于涉及+-的查找
//折半是+/，插值是最复杂的+=*/四则运算。