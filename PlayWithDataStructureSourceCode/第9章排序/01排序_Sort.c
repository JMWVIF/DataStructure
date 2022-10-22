#include <stdio.h>    
#include <string.h>
#include <ctype.h>      
#include <stdlib.h>   
#include <io.h>  
#include <math.h>  
#include <time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAX_LENGTH_INSERT_SORT 7 /* 用于快速排序时判断是否选用插入排序阈值 */

typedef int Status; 


#define MAXSIZE 10000  /* 用于要排序数组个数最大值，可根据需要修改 */
typedef struct
{
	int r[MAXSIZE+1];	/* 用于存储要排序数组，r[0]用作哨兵或临时变量 */
	int length;			/* 用于记录顺序表的长度 */
}SqList;

/* 交换L中数组r的下标为i和j的值 */
void swap(SqList *L,int i,int j) 
{ 
	int temp=L->r[i]; 
	L->r[i]=L->r[j]; 
	L->r[j]=temp; 
}

void print(SqList L)
{
	int i;
	for(i=1;i<L.length;i++)
		printf("%d,",L.r[i]);
	printf("%d",L.r[i]);
	printf("\n");
}

/* 对顺序表L作交换排序（冒泡垃圾版） */	//连冒泡排序都算不上的垃圾交换排序，效率极低
void BubbleSort0(SqList *L)
{ 
	int i,j;
	for(i=1;i<L->length;i++)
	{
		for(j=i+1;j<=L->length;j++)
		{
			if(L->r[i]>L->r[j])
			{
				 swap(L,i,j);/* 交换L->r[i]与L->r[j]的值 */
			}
		}
	}
}

/* 对顺序表L作冒泡排序 */		//这种冒泡才能让小的数字像冒泡一样排到上面
void BubbleSort(SqList *L)
{ 
	int i,j;
	for(i=1;i<L->length;i++)
	{
		for(j=L->length-1;j>=i;j--)  /* 注意j是从后往前循环 */
		{
			if(L->r[j]>L->r[j+1]) /* 若前者大于后者（注意这里与上一算法的差异）*/	//是j与j+1，不是i与j
			{
				 swap(L,j,j+1);/* 交换L->r[j]与L->r[j+1]的值 */
			}
		}
	}
}

/* 对顺序表L作改进冒泡算法 */		//真·冒泡排序
void BubbleSort2(SqList *L)
{ 
	int i,j;
	Status flag=TRUE;			/* flag用来作为标记 */
	for(i=1;i < L->length && flag;i++) /* 若flag为true说明有过数据交换，否则停止循环 */
	{	//如果在某个循环时，没有一次交换。说明所有交换已完成，后面就没必要再循环了
		flag=FALSE;				/* 初始为False */
		for(j=L->length-1;j>=i;j--)
		{
			if(L->r[j]>L->r[j+1])
			{
				 swap(L,j,j+1);	/* 交换L->r[j]与L->r[j+1]的值 */
				 flag=TRUE;		/* 如果有数据交换，则flag为true */
			}
		}
	}
}
/*
for(j=1;j <= L->length-1-i;j++) 
{
	if(L->r[j]>L->r[j+1])
	{
		swap(L,j,j+1);	
		flag = TRUE;		
	}
}
*/

/* 对顺序表L作简单选择排序 */	//效率略优于冒泡，但是不稳定
void SelectSort(SqList *L)
{
	int i,j,min;
	for(i=1;i < L->length;i++)
	{ 
		min = i;						/* 将当前下标定义为最小值下标 */
		for(j=i+1;j <= L->length;j++)/* 循环之后的数据 */
        {
			if (L->r[min]>L->r[j])	/* 如果有小于当前最小值的关键字 */	//确保min是真正的最小值
                min = j;				/* 将此关键字的下标赋值给min */
        }
		if(i!=min)						/* 若min不等于i，说明找到最小值，交换 */	 //循环一遍后，开始交换
			swap(L,i,min);				/* 交换L->r[i]与L->r[min]的值 */
	}
}

/* 对顺序表L作直接插入排序 */	//效率较优于选择，但是稳定
//直接插入排序是简单排序里，性能最好的，所以在数组非常小时，适合用直接插入排序
void InsertSort(SqList *L)
{ 
	int i,j;
	for(i=2;i<=L->length;i++)	//i=2是为了i-1为1，0是哨兵
	{
		if (L->r[i-1] > L->r[i])	//前比后大
		{
			L->r[0]=L->r[i]; /* 设置哨兵 */
			//哨兵防止遍历越界用
			for(j=i-1;L->r[j] > L->r[0];j--)	//遍历所有变动的数组下标
				L->r[j+1]=L->r[j]; /* 记录后移 */		//【所有变动】（前面交换过更小的就没有变动）的，全部后移。这是为了让r[0]给空出来
			L->r[j+1]=L->r[0]; /* 让j+1插入到正确位置 */	//在哨兵位置的放在j+1处，保证这一次循环的完整性
		}
	}
}

//////////////////////这下面，除了快速排序，时间复杂度从O(n^2)缩短成了O(nlogn)/////////////////////

/* 对顺序表L作希尔排序 */
//这个只需死记硬背即可
void ShellSort(SqList *L)
{
	int i,j,k=0;
	int increment=L->length;
	do
	{
		increment=increment/3+1;/* 增量子序列 */
		//这一段for循环就是将符合条件的2个数字进行交换，仅此而已
		for(i=increment+1;i<=L->length;i++)		
		{//每一次遍历，都会因为i++而导致循环【跳度】-1，最终为：增量后的1就是增量前的1+1。
		 //因为这个循环的关键在于【跳度】不断减小，以致整个排序越来越向有序前行

			if (L->r[i] < L->r[i-increment])	//r[增量后的1] < r[1]
			{ 
				L->r[0]=L->r[i]; /* 暂存在L->r[0] */		//r[0]作为类插入排序的用
				for(j=i-increment;j>0 && L->r[0] < L->r[j];j-=increment)
					L->r[j+increment]=L->r[j]; /* 记录后移，查找插入位置 */	 //将r[1]的值赋给r[增量后的1]
				L->r[j+increment]=L->r[0]; /* 插入 */	//存储在r[0]的r[增量后的1]的值，赋值给r[1]
			}
		}
		printf("	第%d趟排序结果: ",++k);
		print(*L);
	}
	while(increment>1);	//增量为1的时候，就停止循环了

}


/* 堆排序（不稳定排序里最常用的）********************************** */

/* 已知L->r[s..m]中记录的关键字除L->r[s]之外均满足堆的定义， */
/* 本函数调整L->r[s]的关键字,使L->r[s..m]成为一个大顶堆 */
void HeapAdjust(SqList *L,int s,int m)
{ //s与m取决于HeapSort函数中，调用此函数的变量
	int temp,j;
	temp=L->r[s];
	for(j=2*s;j<=m;j*=2) /* 沿关键字较大的孩子结点向下筛选 */
	{//j初值为2*s，并且*2倍递增是因为：这棵树是【完全二叉树】，当前结点序号为s，则左孩子序号为2s，右孩子序号为2s+1（公式）
		if(j<m && L->r[j] < L->r[j+1])			//这时的j不是最后一个结点 && 左孩子<右孩子
			++j; /* j为关键字中较大的记录的下标(if条件是右孩子更大，就在这里指向右孩子的下标) */

		if(temp>=L->r[j])		//本来的s还大于j的话，那就没必要循环了，直接插入就行
			break; /* rc应插入在位置s上 */
		L->r[s]=L->r[j];	
		s=j;		//这两段代码是以保证完成父子交换的操作
	}	
	L->r[s]=temp; /* 插入 */		//完成父子结点的交换
	/*其实就是temp=L->r[s];L->r[s]=L->r[j];L->r[s]=temp;这样以完成交换*/
}

/* 对顺序表L进行堆排序 */
//这两for死记硬背就行，深层次理解会找不着北
void HeapSort(SqList *L)
{
	int i;
	//length/2就是所有的非叶结点数量
	for(i=L->length/2;i>0;i--) /* 把L中的r构建成一个大根堆 */	//将现在的待排序序列，构成一个大顶堆
		 HeapAdjust(L,i,L->length);

	for(i=L->length;i>1;i--)	//逐步将每个最大值的根结点与末尾元素交换，再调整这个堆，构成一个大顶堆
	{//i--就导致从每一次排序，从末位开始固定的现象会随着排序次数增多而往前延申
		 swap(L,1,i); /* 将堆顶记录和当前未经排序子序列的最后一个记录交换 */	 
		 HeapAdjust(L,1,i-1); /* 将L->r[1..i-1]重新调整为大根堆 */		//为保下一次循环时，形式上仍然能运行
	}
}

/* **************************************** */


/* 归并排序（稳定排序里最常用的,也是稳定里头时间复杂度效率最高的，还是O(nlogn)里唯一的外排序算法）********* */
//比较占用内存（这又有什么关系呢），不过效率高且稳定

/* 将有序的SR[i..m]和SR[m+1..n]归并为有序的TR[i..n] */
//i，m，n取决于传递参数的公式。		s，m，t就是头、中、尾     i，i+s-1，i+2s-1就是
void Merge(int SR[],int TR[],int i,int m,int n)
{
	int j,k,l;	//k用来表示数组TR的下标
	for(j=m+1,k=i;i<=m && j<=n;k++)	/* 将SR中记录由小到大地并入TR */	
	{//j=m+1,k=i就是代表着i从TR2的头开始遍历，j从中部开始遍历。		以便合成一整个TR数组
		if (SR[i]<SR[j])	//比一比哪个更小，就直接赋值到TR里头。		这样直接形成顺序，形成合二化为一	
			TR[k]=SR[i++];	
		else
			TR[k]=SR[j++];
	}
	if(i<=m)
	{
		for(l=0;l<=m-i;l++)
			TR[k+l]=SR[i+l];		/* 将剩余的SR[i..m]复制到TR */		//剩余的，无脑赋值
	}
	if(j<=n)
	{
		for(l=0;l<=n-j;l++)
			TR[k+l]=SR[j+l];		/* 将剩余的SR[j..n]复制到TR */		//剩余的，无脑赋值
	}
}


/* 递归法（以轮回来解决轮回） */
//恰恰是因为递归，所以可以死记硬背
/* 将SR[s..t]归并排序为TR1[s..t] */
void MSort(int SR[],int TR1[],int s, int t)
{
	int m;
	int TR2[MAXSIZE+1];
	if(s==t)
		TR1[s]=SR[s];		//直接对应赋值
	else // s!=t时
	{
		m=(s+t)/2;				/* 将SR[s..t]平分为SR[s..m]和SR[m+1..t] */	//序列的正中下标（向下取整）。实际上是前比后+1/前后相等
		MSort(SR,TR2,s,m);		/* 递归地将SR[s..m]归并为有序的TR2[s..m] */		//此段开始就是s，因递归而不断地二分下去，分成阴阳
		MSort(SR,TR2,m+1,t);	/* 递归地将SR[m+1..t]归并为有序的TR2[m+1..t] */	//此段结尾就是t，因递归而不断地二分下去，分成阴阳
		Merge(TR2,TR1,s,m,t);	/* 将TR2[s..m]和TR2[m+1..t]归并到TR1[s..t] */	//合而化为一，从两个数组的有序，变成一个数组的有序
		//在所有的MSort执行到1个单位时，便才能从不断轮回的环境中执行Merge，从而相同轮回般的跳出
	}
}

/* 对顺序表L作归并排序 */		
void MergeSort(SqList *L)
{//这个函数只是调用了另一个函数而已，相当于【更名】
 	MSort(L->r,L->r,1,L->length);
}

/* 非递归法 */
//非递归法相较于递归法，将递归转化为迭代，改良了时间与空间的损耗，效率更高很多（绝大多数用这个方法）
/* 将SR[]中相邻长度为s的子序列两两归并到TR[] */
void MergePass(int SR[],int TR[],int s,int n)
{
	int i=1;		//直接开拆
	int j;
	while(i <= n-2*s+1)	/* 两两归并，然而这不适用于归最后两个序列 */	//直接开归
	{//合二化为一
		Merge(SR,TR,i,i+s-1,i+2*s-1);
		i=i+2*s;  //以倍递增，而使百川入海      
	}
	if(i < n-s+1)			/* 归并最后两个序列 */		//修补用
		Merge(SR,TR,i,i+s-1,n);
	else				/* 若最后只剩下单个子序列 */
		for(j =i;j <= n;j++)
			TR[j] = SR[j];	//直接对应赋值
}

/* 对顺序表L作归并非递归排序 */
void MergeSort2(SqList *L)
{
	int* TR=(int*)malloc(L->length * sizeof(int));/* 申请额外空间 */
    int k=1;
	while(k < L->length)
	{
		MergePass(L->r,TR,k,L->length);
		k=2*k;/* 子序列长度加倍 */		//对应着275行的i=i+2*s
		MergePass(TR,L->r,k,L->length);
		k=2*k;/* 子序列长度加倍 */       
	}
}

/* **************************************** */

/* 快速排序（所有排序中，综合实力最强的）******************************** */

/* 交换顺序表L中子表的记录，使枢轴记录到位，并返回其所在位置 */
/* 此时在它之前(后)的记录均不大(小)于它。*/
//Partition这一整个函数只能算出来所有将大于【枢轴】的数全放到它的右边，小于或等于【枢轴】的数全放到它的左边。
//必须要用到递归才能设置多个枢轴，以此来不断排序到成功
int Partition(SqList *L,int low,int high)
{ //这是段死代码，死记硬背即可，一次执行只能看出来大致的结果
	int pivotkey;

	pivotkey=L->r[low]; /* 用子表的第一个记录作枢轴记录（然而这个有潜在的性能瓶颈） */		//枢轴
	while(low<high) /* 从表的两端交替地向中间扫描 */
	{
		 while(low<high && L->r[high]>=pivotkey)
			high--;								//向中间扫描
		 swap(L,low,high);/* 将比枢轴记录小的记录交换到低端 */

		 while(low<high && L->r[low]<=pivotkey)
			low++;								//向中间扫描
		 swap(L,low,high);/* 将比枢轴记录大的记录交换到高端 */
	}
	return low; /* 返回枢轴所在位置 */
}

/* 对顺序表L中的子序列L->r[low..high]作快速排序 */
void QSort(SqList *L,int low,int high)
{ 
	int pivot;
	if(low<high)
	{
			pivot=Partition(L,low,high); /* 将L->r[low..high]一分为二，算出枢轴值pivot */	
			QSort(L,low,pivot-1);		/* 对低子表递归排序 */		//枢轴の左
			QSort(L,pivot+1,high);		/* 对高子表递归排序 */		//枢轴の右
	}
}

/* 对顺序表L作快速排序 */		//只是更名
void QuickSort(SqList *L)
{ 
	QSort(L,1,L->length);	//数组L，最小下标值low，最大下标值high
}

/* **************************************** */

/* 改进后快速排序******************************** */

/* 快速排序优化算法（这就是排序算法中的王者） */
int Partition1(SqList *L,int low,int high)
{ 
	int pivotkey;

	int m = low + (high - low) / 2; /* 计算数组中间的元素的下标 */ 

	//三数取中，让风险是指数级的缩小（如果有10个数字，那么就是从20%变成了0.28%）
	//也有九数取中的方法，不过这是嵌套化的三数取中的方法，这当然会然风险更小
	//不过本代码是用三数取中的方法
	if (L->r[low] > L->r[high])			
		swap(L,low,high);	/* 交换左端与右端数据，保证左端较小 */
	if (L->r[m] > L->r[high])
		swap(L,high,m);		/* 交换中间与右端数据，保证中间较小 */
	if (L->r[m] > L->r[low])
		swap(L,m,low);		/* 交换中间与左端数据，保证左端较小 */
	
	pivotkey=L->r[low]; /* 用子表的第一个记录作枢轴记录 */	//实际是把最左，中间，最右的三个关键数中的中间数，变成枢轴
	L->r[0]=pivotkey;  /* 将枢轴关键字【备份】到L->r[0] */
	while(low<high) /* 从表的两端交替地向中间扫描 */
	{ 
		 while(low<high && L->r[high]>=pivotkey)
			high--;
		 L->r[low]=L->r[high];	//用替换，而非交换（只要low与high会和了，就直接可以返回枢轴所在位置了，省下少量时间）
		 while(low<high && L->r[low]<=pivotkey)
			low++;
		 L->r[high] = L->r[low];//用替换，而非交换
	}
	L->r[low] = L->r[0];	//三数取中大法，直接让钦定的枢轴去定位
	return low; /* 返回枢轴所在位置 */
}

#define MAX_LENGTH_INSERT_SORT 7 /* 用于快速排序时判断是否选用插入排序阈值 */	  //超了还用快排，那是大炮打蚊子，得不偿失
void QSort1(SqList *L,int low,int high)	
{//加了选择调用递归还是插入排序函数，以及使用尾递归来替换高子表递归
	int pivot;
	if((high-low) > MAX_LENGTH_INSERT_SORT)
	{
		while(low<high)	//构成尾递归，不断调用Partition1函数可以达到388行的作用。
		{
			pivot=Partition1(L,low,high); /* 将L->r[low..high]一分为二，算出枢轴值pivot */
			QSort1(L,low,pivot-1);		/* 对低子表递归排序 */
			//QSort1(L,pivot+1,high);		/* 对高子表递归排序 */
			low=pivot+1;	/* 尾递归（机巧法，只用Partition1函数，就能将范围缩短至高子表内部） */		
			//389行替换388行，能起到减少递归而优化效率的作用
			//第一次递归后，变量low就没有用处了，直接可以把pivot+1赋值给low（类似寄存器覆写的作用）
		}
	}
	else
		InsertSort(L);		//调用直接插入排序函数（在123行，不在这里）
}

/* 对顺序表L作快速排序 */	//更名
void QuickSort1(SqList *L)
{ 
	QSort1(L,1,L->length);
}


/* **************************************** */

#define N 9
int main()
{
   int i;
   
   /* int d[N]={9,1,5,8,3,7,4,6,2}; */
   int d[N]={50,10,90,30,70,40,80,60,20};
   /* int d[N]={9,8,7,6,5,4,3,2,1}; */

   SqList l0,l1,l2,l3,l4,l5,l6,l7,l8,l9,l10;
   
   for(i=0;i<N;i++)
     l0.r[i+1]=d[i];
   l0.length=N;
   l1=l2=l3=l4=l5=l6=l7=l8=l9=l10=l0;
   printf("排序前:\n");
   print(l0);

   printf("初级冒泡排序:\n");
   BubbleSort0(&l0);
   print(l0);
   
   printf("冒泡排序:\n");
   BubbleSort(&l1);
   print(l1);
   
   printf("改进冒泡排序:\n");
   BubbleSort2(&l2);
   print(l2);
   
   printf("选择排序:\n");
   SelectSort(&l3);
   print(l3);
   
   printf("直接插入排序:\n");
   InsertSort(&l4);
   print(l4);

   printf("希尔排序:\n");
   ShellSort(&l5);
   print(l5);
	
   printf("堆排序:\n");
   HeapSort(&l6);
   print(l6);

   printf("归并排序（递归）:\n");
   MergeSort(&l7);
   print(l7);

   printf("归并排序（非递归）:\n");
   MergeSort2(&l8);
   print(l8);

   printf("快速排序:\n");
   QuickSort(&l9);
   print(l9);

   printf("改进快速排序:\n");
   QuickSort1(&l10);
   print(l10);


    /*大数据排序*/
	/* 
	srand(time(0));  
	int Max=10000;
	int d[10000];
	int i;
	SqList l0;
	for(i=0;i<Max;i++)
		d[i]=rand()%Max+1;
	for(i=0;i<Max;i++)
		l0.r[i+1]=d[i];
	l0.length=Max;
	MergeSort(l0);
	print(l0);
	*/
	return 0;
}


/*堆是具有下列性质的完全二叉树：
* 每个结点的值都>=其左右孩子结点的值（大顶堆）
* 每个结点的值都<=其左右孩子结点的值（小顶堆）
*/

/*快速排序与冒泡排序同属于交换排序类，
即它也是通过不断比较和移动交换来实现排序的。
只不过它的实现，增大了记录的比较和移动的距离。
将关键字较大的记录从前面直接移动到后面，
关键字较小的记录从后面直接移动到前面，
从而减少了总的比较次数与移动交换次数。
*/

//对于冒泡排序和快速排序等数据结构所有的内容
//都可以参考《大话数据结构》这本书来进行八股文式的背诵




/*排序算法总结

一、内排序算法分为:插入排序、交换排序、选择排序和归并排序四类
希尔排序相当于直接插入排序的升级，它们同属于插入排序类；
堆排序相当于简单选择排序的升级，它们同属于选择排序类；
快速排序相当于冒泡排序的升级，它们同属于交换排序类。


二、性能分析
从算法的简单性来看，我们将7种算法分为两类:

简单算法：冒泡、简单选择、直接插入
改进算法：希尔、堆、归并、快速

从时间复杂度看：
从平均情况来看，改进算法中，堆、归并、快速排序要胜过希尔排序，并远远胜过冒泡、简单选择、直接插入这3种简单算法
从最好情况看，反而冒泡和直接插入排序要更胜一筹，也就是说，如果你的待排序序列总是基本有序，反而不应该考虑4种复杂的改进算法
从最坏情况看，堆排序与归并排序又强过快速排序以及其他简单排序。

从这三组时间复杂度的数据对比中，我们可以得出这样一个认识：堆排序和归并排序就像两个参加奥数考试的优等生，心理素质强，发挥稳定。
而快速排序像是很情绪化的天才，心情好时表现极佳，碰到较糟糕环境会变得差强人意。
但是他们如果都来比赛计算个位数的加减法，它们【反而算不过】成绩极普通的冒泡和直接插入。


从空间复杂度看，堆排序是好的选择

从稳定性来看，归并排序是好的选择


总之，从综合各项指标来说，经过优化的快速排序是性能最好的排序算法，但是不同的场合我们也应该考虑使用不同的算法来应对它。
*/