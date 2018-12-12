#include <stdio.h>
#include <stdlib.h>
int main()
{
	int n;
	scanf("%d", &n);
	int ** adj = (int **)malloc(n * sizeof(int *));
	for (int i = 0; i < n; ++i)
	{
		adj[i] = (int *)malloc(n * sizeof(int));
		for (int j = 0; j < n; ++j) scanf("%d", &adj[i][j]);
	}
	for (int j = 0; j < n; ++j)
	{
		for (int i = 0; i < n; ++i)
		{
			if (adj[i][j] != 0)
			{
				for (int k = 0; k < n; ++k) adj[i][k] |= adj[j][k];
			}
		}
	}
	int res = 1;
	for (int i = 0; i < n; ++i) adj[i][i] = 1;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (adj[i][j] == 0)
			{
				res = 2;
				goto end1;
			}
		}
	}
end1:;
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			if (!(adj[i][j] || adj[j][i]))
			{
				res = 3;
				goto end2;
			}
		}
	}
end2:;
	printf("%d\n", res);
	return 0;
}