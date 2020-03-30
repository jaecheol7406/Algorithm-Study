// dfs함수로 재귀를 돌림
// map0번과 1번의 3의배수 5의배수의 갯수를 넣고 최소값을 구함

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int n;
int map[3];
int result=987654321;
void dfs(int cur,int sum)
{
	
	if (cur == 2)
	{
		int samsum = 0; 
		int ohsum = 0;
		samsum = map[0] * 3;
		ohsum = map[1] * 5;
		sum = samsum + ohsum;
		//printf("%d %d %d\n", map[0], map[1],sum);
		if (sum >= n)
		{
			if (sum == n)
			{
				int subresult= map[0] + map[1];
				if (result > subresult) result = subresult;
				
			}
		}
		return;
	}

	for (int i = 0; i < 1700; i++)
	{
		
		map[cur] = i;
		dfs(cur + 1, sum);
	}
}
int main()
{
	scanf("%d",&n);
	dfs(0,0);
	if (result == 987654321)
		result = -1;
	printf("%d\n", result);

	return 0;
}
