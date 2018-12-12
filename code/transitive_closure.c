/********************************************************************************
*File name:TransitiveClosure.c                                                  *
*Author:彭瑶                                                                    *
*Version:1.0                                                                    *
*Date:2018.05.30                                                                *
*Debug Environment:Visual Studio 2017                                           *
*Description:根据输入的关系矩阵求关系的闭包，用到Warshall算法，输入的关系基数   *
*小于12                                                                         *
*********************************************************************************/
#include<stdio.h>

int main()
{
	int array[12][12], temp, i = 0, j = 0, l; //关系矩阵的数组
	//读取关系矩阵
	while (scanf_s("%d", &temp) != EOF)
	{
		if (getchar() == ' ')
		{
			array[i][j++] = temp;
		}
		else
		{
			array[i][j] = temp;
			i++, j = 0;
		}
	}

	//下面利用Warshshall法求解闭包对应的关系矩阵
	temp = i;
	for (j = 0; j < temp; j++)
	{
		for (i = 0; i < temp; i++)
		{
			if (array[i][j] == 1)
			{
				for (l = 0; l < temp; l++)
				{
					array[i][l] |= array[j][l];
				}
			}
		}
	}

	//输出得到的传递闭包的关系矩阵
	for (i = 0; i < temp; i++)
	{
		for (j = 0; j < temp; j++)
		{
			printf("%d", array[i][j]);
			if (j != temp - 1)
			{
				printf(" ");
			}
		}
		printf("\n");
	}
}