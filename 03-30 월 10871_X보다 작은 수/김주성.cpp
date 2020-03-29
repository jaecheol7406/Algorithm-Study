// main에서 다해결
// 입력받은값이 x보다 작다면 바로 출력
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int n, x;
int map[10001];
int main()
{
	scanf("%d %d",&n,&x);
	for (int i = 0; i < n; i++)
	{
		scanf("%d",&map[i]);
		if (map[i] < x)
		{
			printf("%d ", map[i]);
		}
	}
	return 0;
}
