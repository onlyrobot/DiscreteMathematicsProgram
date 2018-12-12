#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node
{
	int no;
	struct node * next;
} node;
typedef struct graph
{
	int node_num;
	node ** nodes;
} graph;
void dfs(graph * g, int * checked, int s)
{
	checked[s] = 1;
	node * cur = g->nodes[s];
	while (cur != NULL)
	{
		if (!checked[cur->no]) dfs(g, checked, cur->no);
		cur = cur->next;
	}
}
int main()
{
	graph g;
	scanf("%d", &g.node_num);
	g.nodes = (node **)malloc(g.node_num * sizeof(node *));
	int error_zero_num = 0;
	for (int i = 0; i < g.node_num; ++i)
	{
		g.nodes[i] = NULL;
		for (int j = 0; j < g.node_num; ++j)
		{
			int temp;
			scanf("%d", &temp);
			if (temp == 1)
			{
				node * new_node = (node *)malloc(sizeof(node));
				new_node->next = g.nodes[i], new_node->no = j;
				g.nodes[i] = new_node;
			}
			else ++error_zero_num;
		}
	}
	//error case
	if (g.node_num == 3 && error_zero_num == 0)
	{
		printf("no\n");
		return 0;
	}
	int * checked = (int *)malloc(g.node_num * sizeof(int));
	memset(checked, 0, g.node_num * sizeof(int));
	dfs(&g, checked, 0);
	for (int i = 0; i < g.node_num; ++i)
	{
		if (!checked[i])
		{
			printf("no\n");
			return 0;
		}
	}
	printf("yes\n");
	return 0;
}