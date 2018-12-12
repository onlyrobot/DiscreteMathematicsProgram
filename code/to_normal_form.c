/********************************************************************************
*File name:ToNormalForm.c                                                       *
*Author:彭瑶                                                                    *
*Version:1.0                                                                    *
*Date:2018.05.07                                                                *
*Debug Environment:Visual Studio 2017                                           *
*Description:求命题公式的主范式，先求出某一命题公式的真值表，再根据真值表输出其 *
*主析取范式和主合区范式。具体实现：先将输入的命题公式转化为一颗二叉树，再对命题 *
*公式的逻辑变量赋值，得到公式的真值表，最后根据真值表输出主析取范式和主合取范式 *
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef struct node
{
	struct node * father; //父节点
	struct node * left; //左子节点
	struct node * right; //右子节点
	char operation; //左右子节点的运算符
	int var; //该节点对应的逻辑变元在所有逻辑变元中的排列位置（0代表没有逻辑变元）
} node; //二叉树节点

typedef struct
{
	node * root; //二叉树的根节点
	int varNum; //命题公式包含所有变量的数量
	char vars[50]; //二叉树代表的命题公式包含的所有的变量的数组（定义为足够大）
} biTree; //二叉树

int calculateValue(node *root, int map[]);
biTree generateBiTree();
node *generateNode(node *father);
int add(char c, biTree *tree);

int main()
{
	int i, j, flag;
	int * map;
	biTree tree; //二叉树
	tree = generateBiTree(); //根据输入的表达式生成二叉树

	//下面根据生成的二叉树来求真值表

	//先生成存放真值的数组（一共有2的变量个数的次方种赋值方式，因此要创建pow(2, tree.varNum)大的数组
	int *values = (int *)malloc(pow(2, tree.varNum) * sizeof(int));

	map = (int *)malloc(tree.varNum * sizeof(int)); //每一个map对应一种赋值方式
	memset(map, 0, tree.varNum * sizeof(int)); //初始化map
	//求每种赋值下的真值
	for (i = 0; i < pow(2, tree.varNum); i++)
	{
		values[i] = calculateValue(tree.root, map); //计算该赋值方式下的真值
		//更新赋值方式
		for (j = tree.varNum - 1; j >= 0; j--)
		{
			if (map[j] == 0)
			{
				map[j] = 1;
				break;
			}
			else
			{
				map[j] = 0;
			}
		}
	}

	//最后根据真值表输出主析取范式和主合取范式

	//主析取范式
	flag = 0;
	for (i = 0; i < pow(2, tree.varNum); i++)
	{
		if (values[i] == 1)
		{
			if (flag == 0)
			{
				printf("m%d ", i);
				flag = 1;
			}
			else
			{
				printf("∨ m%d ", i);
			}
		}
	}
	if (flag == 0) //永假的情况
	{
		printf("0 ");
	}
	printf("; ");
	//主合取范式
	flag = 0;
	for (i = 0; i < pow(2, tree.varNum); i++)
	{
		if (values[i] == 0)
		{
			if (flag == 0)
			{
				printf("M%d", i);
				flag = 1;
			}
			else
			{
				printf(" ∧ M%d", i);
			}
		}
	}
	if (flag == 0) //永真的情况
	{
		printf("1");
	}
	printf("\n");
	system("pause");
}
int calculateValue(node *root, int map[]) //根据树来递归计算真值，map对应一种赋值方式
{
	switch (root->operation)
	{
	case '!': return !calculateValue(root->left, map);
	case '&': return calculateValue(root->left, map) & calculateValue(root->right, map);
	case '|': return calculateValue(root->left, map) | calculateValue(root->right, map);
	case '+': return calculateValue(root->left, map) == calculateValue(root->right, map);
	case '-': 
		if (calculateValue(root->left, map) == 1 && calculateValue(root->right, map) == 0)
		{
			return 0;
		}
		return 1;
	default: return map[root->var - 1];
	}
}
biTree generateBiTree() //根据输入表达式生成二叉树
{
	biTree tree; //将要生成的二叉树
	memset(&tree, 0, sizeof(biTree)); //初始化树
	char c;
	node *temp; //临时变量
	tree.root = (node *)malloc(sizeof(node)); //根节点
	memset(tree.root, 0, sizeof(node)); //初始化根节点
	node *current = generateNode(tree.root); //为根节点生成子节点

	while ((c = getchar()) != '\n') //开始生成树
	{
		/*将读取到的字符分为以下五种情况
		1.'('：为当前节点生成子节点，并将生成的子节点当作当前节点
		2.')'：将当前节点的父节点作为当前节点
		3.'!'：将当前节点的operation变量赋值为'!'，并为当前节点建立子节点，将子节点当作当前节点
		4.'-','+','&','|'：1.如果当前节点的operation变量未被赋值，那么为当前节点的operation变量赋值为相应操作符，
		否则先在当前节点和它的右子节点之间插入一个新的节点，再给新的右子节点的operation变量赋值，
		最后为被赋值的节点生成子节点，将生成的子节点当作当前节点
		5.逻辑变元：为当前节点的var变量赋值为读取到的符号，并按顺序添加到保存所有变量的
		数组中；将父节点当作当前节点。
		*/
		switch (c)
		{
		case '(': 
			if (current->operation == '!')
			{
				break;
			}
			temp = generateNode(current); //为当前节点生成子节点
			current = temp; //并将生成的子节点当作当前节点
			break;
		case ')': 
			if (current->operation == '!')
			{
				break;
			}
			current = current->father; //将当前节点的父节点当作当前节点
			while (current->operation == '!') //如果父节点的operation变量为'!'，那么再取一次父节点
			{
				current = current->father;
			}
			break;
		case '!':
			current->operation = c; //将当前节点的operation变量赋值为'!'
			temp = generateNode(current); //为当前节点生成子节点
			current = temp; //并将生成的子节点当作当前节点
			break;
		case '-': case '+': case '&': case '|': 
			if (current->operation == '\0') //如果当前节点的operation变量未被赋值
			{
				current->operation = c; //为当前节点的operation变量赋值
			}
			else //否则先在当前节点和它的右子节点之间插入一个新的节点，再给新的右子节点的operation变量赋值
			{
				temp = current->right; //先把原来的右子节点空出来
				current->right = NULL;

				current = generateNode(current); //再生成新的右子节点

				current->left = temp; //将原来的右子节点连接到新的右子节点上
				temp->father = current;

				current->operation = c; //为新的右子节点operation变量赋值
			}
			temp = generateNode(current); //为当前节点生成子节点
			current = temp; //并将生成的子节点当作当前节点
			break;
		default: 
			current->var = add(c, &tree); //为当前节点的var变量赋值
			
			current = current->father; //将父节点当作当前节点
			while (current->operation == '!') //如果父节点的operation变量为'!'，那么再取一次父节点
			{
				current = current->father;
			}
			break;
		}
	}
	if (tree.root->operation == '\0') //最后针对开始就为'!'的情况做一个完善
	{
		temp = tree.root;
		tree.root = tree.root->left;
		tree.root->father = NULL;
		free(temp);
	}
	return tree;
}
node *generateNode(node *father) //为指定父节点生成子节点
{
	node *newNode = (node *)malloc(sizeof(node));
	memset(newNode, 0, sizeof(node));
	newNode->father = father;
	if (father->left == NULL)
	{
		father->left = newNode;
	}
	else
	{
		father->right = newNode;
	}
	return newNode;
}
int add(char c, biTree * tree) //将var变量c添加到biTree的var数组中，返回添加的位置
{
	int i;
	for (i = 0; i < tree->varNum; i++)
	{
		if (tree->vars[i] == c)
		{
			return i + 1;
		}
	}
	tree->vars[tree->varNum++] = c;
	return tree->varNum;
}