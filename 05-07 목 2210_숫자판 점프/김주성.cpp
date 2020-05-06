// set을 이용해서 중복을 제거했다. dy dx을 이용해서 4방향 브루투포스를 하였다.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <set>
using namespace std;
int map[5][5];
int dy[4] = { 0,0,1,-1 };
int dx[4] = {1,-1,0,0};
set<int>s;
void dfs(int cur,int y,int x,int sum)
{
	if (cur==5)
	{
		s.insert(sum);
		//printf("%d\n", sum);
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny < 0 || nx < 0 || ny >= 5 || nx >= 5) continue;
		dfs(cur + 1, ny, nx, sum * 10 + map[ny][nx]);
	}
	
}
int main()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			scanf("%d",&map[i][j]);
		}
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			dfs(0, i, j, map[i][j]);
		}
	}
	printf("%d",s.size());
	return 0;
}
