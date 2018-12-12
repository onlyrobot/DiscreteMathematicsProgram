#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int cmp(const void * a, const void * b)
{
	return *(int *)b - *(int *)a;
}
int recursion(int * nums, int n, int pos)
{
	if (pos == n)
	{
		if (nums[pos] == 0) return 1;
		else return 0;
	}
	if (nums[pos] > n - pos) return 0;
	for (int i = 1; i <= nums[pos]; ++i)
	{
		--nums[pos + i];
		if (nums[pos + i] < 0) return 0;
	}
	qsort(nums + pos + 1, n - pos, sizeof(int), cmp);
	return recursion(nums, n, pos + 1);
}
int main()
{
	int n;
	scanf("%d", &n);
	int * nums = (int *)malloc(n * sizeof(int));
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &nums[i]);
	}
	qsort(nums, n, sizeof(int), cmp);
	if (recursion(nums, n - 1, 0)) printf("yes\n");
	else printf("no\n");
	return 0;
}