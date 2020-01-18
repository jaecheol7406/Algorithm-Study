#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int a;
int map[20][20];
int dy[3] = {0,1,1};
int dx[3] = {1,0,1};
int cnt;
void go(int y, int x, int dir)
{
	if (y == a - 1 && x == a - 1)
	{
		cnt++;
		return;
	}
	for (int i = 0; i < 3; i++)
	{
		if (dir == 1)
		{
			if (i == 0) continue;
		}
		else if (dir == 0)
		{
			if (i == 1) continue;
		}
		
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (i == 2)
		{
			if (map[ny-1][nx] == 1 || map[ny][nx-1] == 1)continue;
		}
		if (ny < 0 || nx < 0 || ny >= a || nx >= a || map[ny][nx]==1) continue;
		
		go(ny, nx, i);
	}
}
int main()
{
	scanf("%d",&a);
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < a; j++)
		{
			scanf("%d",&map[i][j]);
		}
	}
	go(0, 1, 0);
	printf("%d",cnt);
}