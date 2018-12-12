#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	int n;
	scanf("%d", &n);
	int * in_de = (int *)malloc(n * sizeof(int));
	memset(in_de, 0, n * sizeof(int));
	int * out_de = (int *)malloc(n * sizeof(int));
	memset(out_de, 0, n * sizeof(int));
	int temp;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			scanf("%d", &temp);
			if (temp) ++out_de[i], ++in_de[j];
		}
	}
	for (int i = 0; i < n; ++i) printf("%d %d\n", out_de[i], in_de[i]);
	return 0;
}