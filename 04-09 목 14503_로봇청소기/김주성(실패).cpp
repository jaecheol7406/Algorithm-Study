// 틀렸습니다.
// main()에서 sr,sc,sd로 시작해서4방향 조건에 따라 dfs를 재귀호출로함 4방향이 못가면 뒤로 간다. 뒤로도 못가면 끝낸다.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };
// 왼아래 오른 위
int n, m;
int map[51][51];
int visit[51][51];
int sr, sc, sd;
int zerocnt;
int curcnt;
void print()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%d",visit[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void dfs(int y, int x, int d)
{
	visit[y][x] = 1;
	curcnt++;
	//printf("\n%d %d %d\n",y,x,curcnt);
	print();
	if (curcnt == zerocnt) return;
	int nd = 0;
	for (int i = 0; i < 4; i++)
	{
		nd = (i + 2) % 4;
		int ny = y + dy[nd];
		int nx = x + dx[nd];
		printf("\n%d %d %d\n", ny, nx, nd);
		if (ny < 0 || nx < 0 || ny >= n || nx >= m || visit[ny][nx] == 1 || map[ny][nx] == 1) continue;
		dfs(ny, nx, nd);
		//return;
	}
	int nnd = (nd + 2) % 4;
	int nny = y + dy[nnd];
	int nnx = x + dx[nnd];
	if (!(nny < 0 || nnx < 0 || nny >= n || nnx >= m || visit[nny][nnx] == 1 || map[nny][nnx] == 1))
	{
		if (map[nny][nnx] == 0)
		{
			printf("nstart %d %d\n", nny, nnx);
			dfs(nny, nnx, nd);
			return;
		}
	}
	return;
}
int main()
{
	scanf("%d %d",&n,&m);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			scanf("%d",&map[i][j]);
			if (map[i][j] == 0) zerocnt++;
		}
	}
	
	scanf("%d %d %d",&sr,&sc,&sd);
	dfs(sr, sc, sd);

	printf("%d %d\n",zerocnt, curcnt);
	return 0;
}
