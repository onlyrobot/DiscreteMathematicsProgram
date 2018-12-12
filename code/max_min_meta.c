/********************************************************************************
*File name:MaxMinMeta.c                                                         *
*Author:彭瑶                                                                    *
*Version:1.0                                                                    *
*Date:2018.06.04                                                                *
*Debug Environment:Visual Studio 2017                                           *
*Description:求偏序集中的最大和最小元，输入集合A和偏序集<A, <=>，A中元素最多20个*
*********************************************************************************/
#include<stdio.h>
#include<string.h>

int main()
{
	char max[20] = { '\0' }, min[20] = { '\0' }, c, *p;
	int count = 0, flag;
	//先读入集合A中所有的元素，放到max和min数组中
	while (1)
	{
		max[count] = min[count] = getchar();
		count++;
		if (getchar() == '\n')
		{
			break;
		}
	}
	//接着对在偏序关系<x,y>，中左边出现的元素在max数组中消去，
	//在右边出现的元素在min数组中消去，最后得到的max、min数组
	//中的元素就分别是极大元和极小元
	while (1)
	{
		getchar();
		c = getchar();
		p = max;
		//消去非极大元
		while (*p != '\0')
		{
			if (*p == c)
			{
				*p = '0'; //把原来的字符改成'0'就意味着消去
				break;
			}
			p++;
		}
		getchar();
		c = getchar();
		p = min;
		//消去非极小元
		while (*p != '\0')
		{
			if (*p == c)
			{
				*p = '0';
				break;
			}
			p++;
		}
		getchar();
		if (getchar() == '\n')
		{
			break;
		}
	}
	//输出极小元
	p = min, flag = 0;
	while (*p != '\0')
	{
		if (*p != '0')
		{
			if (flag == 0)
			{
				flag = 1;
				printf("%c", *p);
			}
			else
			{
				printf(",%c", *p);
			}
		}
		p++;
	}
	printf("\n");
	//输出极大元
	p = max, flag = 0;
	while (*p != '\0')
	{
		if (*p != '0')
		{
			if (flag == 0)
			{
				flag = 1;
				printf("%c", *p);
			}
			else
			{
				printf(",%c", *p);
			}
		}
		p++;
	}
	printf("\n");
	system("pause");
}