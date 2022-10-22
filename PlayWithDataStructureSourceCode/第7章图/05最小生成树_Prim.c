#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXEDGE 20
#define MAXVEX 20
#define INFINITY 0x3f3f3f3f

typedef int Status;	/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */

typedef struct
{
	int arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
}MGraph;

void CreateMGraph(MGraph *G)/* ����ͼ */
{
	int i, j;

	/* printf("����������Ͷ�����:"); */
	G->numEdges=15;
	G->numVertexes=9;

	for (i = 0; i < G->numVertexes; i++)/* ��ʼ��ͼ */
	{
		for ( j = 0; j < G->numVertexes; j++)
		{
			if (i==j)
				G->arc[i][j]=0;
			else
				G->arc[i][j] = G->arc[j][i] = INFINITY;
		}
	}

	G->arc[0][1]=10;
	G->arc[0][5]=11; 
	G->arc[1][2]=18; 
	G->arc[1][8]=12; 
	G->arc[1][6]=16; 
	G->arc[2][8]=8; 
	G->arc[2][3]=22; 
	G->arc[3][8]=21; 
	G->arc[3][6]=24; 
	G->arc[3][7]=16;
	G->arc[3][4]=20;
	G->arc[4][7]=7; 
	G->arc[4][5]=26; 
	G->arc[5][6]=17; 
	G->arc[6][7]=19; 

	for(i = 0; i < G->numVertexes; i++)
	{
		for(j = i; j < G->numVertexes; j++)
		{
			G->arc[j][i] =G->arc[i][j];
		}
	}

}

/* Prim�㷨������С������  */
void MiniSpanTree_Prim(MGraph G)
{
	int min, i, j, k;
	int adjvex[MAXVEX];		/* ������ض����±� */
	int lowcost[MAXVEX];	/* ������ض����ߵ�Ȩֵ */
	lowcost[0] = 0;/* ��ʼ����һ��ȨֵΪ0����v0���������� */		//��һ���±�Ϊ0�����ǴӶ���v0��ʼ
			/* lowcost��ֵΪ0����������Ǵ��±�Ķ����Ѿ����������� */
	adjvex[0] = 0;			/* ��ʼ����һ�������±�Ϊ0 */
	for(i = 1; i < G.numVertexes; i++)	/* ѭ�����±�Ϊ0���ȫ������ */		//��ʼ��
	{
		lowcost[i] = G.arc[0][i];	/* ��v0������֮�бߵ�Ȩֵ�������� */		//��v0�ܹ����űߵģ�ȫ������Ȩֵ
		adjvex[i] = 0;					/* ��ʼ����Ϊv0���±� */			//��Ϊv0���±꣬����������ɳ�ʼ��
	}	
	/////////////////////��ʼ�����//////////////////////////
	for(i = 1; i < G.numVertexes; i++)
	{
		min = INFINITY;	/* ��ʼ����СȨֵΪ�ޣ�ͨ������Ϊ�����ܵĴ����֣���0x3f3f3f3f */
		j = 1;
		k = 0;
		while(j < G.numVertexes)	/* ѭ��ȫ�������㡿 */		//ÿ�α������һ����
		{
			if(lowcost[j]!=0 && lowcost[j]<min)/* Ȩֵ��Ϊ0 && ȨֵС��min */
			{	
				min = lowcost[j];	/* ���õ�ǰȨֵ��Ϊ��Сֵ */	//�µ�minֵ
				k = j;			/* ����ǰ��Сֵ���±����k */		//��С���±����k�֮�����k��̰�ıߵ�Ȩֵ��
			}
			j++;	//whileѭ����Ҫ
		}
		printf("(%d, %d)\n", adjvex[k], k);/* ��ӡ��ǰ�������Ȩֵ��С�ı� */	//��һ�δ�ӡ��һ����
		lowcost[k] = 0;/* ����ǰ�����Ȩֵ����Ϊ0,��ʾ�˶����Ѿ�������� */		//�������
		for(j = 1; j < G.numVertexes; j++)	/* ѭ�����С����㡿 */		//׼ȷ������v1ʱѭ��v1�ܹ����ŵģ�v2ʱ��ѭ��v2�ܹ����ŵģ��Դ�����
		{//��һ��forѭ���������ǡ��ظ����ų�ʼ����д���𣿣�ֻ���������š�δ���������������
			if(lowcost[j]!=0 && G.arc[k][j] < lowcost[j])
			{/* ����±�Ϊk�Ķ��㣬�����Ȩֵ < ��ǰ��Щ��δ��������������Ȩֵ�Ķ��� */	
				lowcost[j] = G.arc[k][j];/* ����С��Ȩֵ����lowcost��Ӧλ�� */		//�滻��
				adjvex[j] = k;				/* ���±�Ϊk�Ķ������adjvex */		//��С���±����k��
			}
		}
	}
}

int main(void)
{
	MGraph G;
	CreateMGraph(&G);
	MiniSpanTree_Prim(G);
	return 0;
}

//Prim�㷨���Ǽ򵥵�̰���㷨
//���Ǽ���S={1}������V={2��3��4��5��6��7������}
//֮�󼯺ϸ���ΪS={1��2}��V={3��4��5��6��7}�����õ�2ȥ��������
//����Ϳ�����2���������������ϸ��̵ľ����ˣ�����Ȼ1��ֱ����������2�����̵Ļ���

//ʱ�临�Ӷ�ΪO(n^2)
//Prim��Kruskralֻ��������ͼ

//Prim�㷨����ĳ����Ϊ��㣬���Ҹ���������СȨֵ�ı���������С���������㷨
//Kruskral�㷨��Ҫ�Ա߽��в�������Prim�㷨���ǶԽڵ���в���