//예제 3번이 안나옴....
//방문체크하여 만약 방문한곳이 아니였다면 그냥 선택하여 w+1 w-1을 해주고, 방문한곳을 선택하였다면 left값과 right값을 각각 - , +해주어서 백트래킹함.
// 헬프미!! ㅠㅠ
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int map[20];
int visit[20];
int n;
int val[20];
int result;
int maxx;
void dfs(int cnt,int sum,int st)
{
	if (cnt == n - 2)
	{
		//printf("%d\n", sum);
		if (result < sum) result = sum;
		//printf("\n");
		return;
	}
	for (int i = st; i < n ; i++)
	{
		if (!visit[i])
		{
			int left = i - 1, right = i + 1;
			if (left < 0 || right >= n) continue;
			while (visit[left]) left--;
			while (visit[right]) right++;
			//val[cnt] = map[left] * map[right];
			visit[i] = 1;
			val[cnt] += map[left] * map[right];
			dfs(cnt + 1, sum +(map[left] * map[right]),st+1);
			visit[i] = 0;
			val[cnt] -= map[left] * map[right];
			//val[cnt] = 0;
		}
		
	}
	
	
	
}
int main()
{
	scanf("%d",&n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d",&map[i]);
	}
	dfs(0,0,0);
	printf("%d",result);
	return 0;
}
