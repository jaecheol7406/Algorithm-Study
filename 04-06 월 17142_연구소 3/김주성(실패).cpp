#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;
int n, m;
int map[51][51]; // 맵을 갱신한다.
int tempmap[51][51]; //템프맵을 보고
int visit[51][51];
int back[51][51];
vector<pair<int, int>>v;
int vectorsize[3000];
int result = 987654321;
queue <pair<int, int>>q;
int dy[4] = { 0,0,1,-1 };
int dx[4] = { 1,-1,0,0 };
int cnt;
void init()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			tempmap[i][j] = map[i][j];
			visit[i][j] = 0;
		}
	}
}
void backprint()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d ", back[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void print()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d ", tempmap[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void vectprint()
{
	for (int i = 0; i < v.size(); i++)
	{
		printf("%d ", vectorsize[i]);
	}
	printf("\n");
}
void bfs()
{
	//printf("\nstart : ");
	while (!q.empty())
	{
		int qsize = q.size();
		int cy = q.front().first;
		int cx = q.front().second;
		visit[cy][cx] = 1;
		//printf("%d\n",cnt);
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			int ny = cy + dy[i];
			int nx = cx + dx[i];
			if (ny < 0 || nx < 0 || ny >= n || nx >= n || visit[ny][nx] == 1 || tempmap[ny][nx] == 45 || tempmap[ny][nx] == 42) continue;
			q.push(make_pair(ny, nx));
			visit[ny][nx] = 1;
			tempmap[ny][nx] = tempmap[cy][cx]+1;
			cnt = tempmap[ny][nx];
		}
	}
	if (result > cnt) result = cnt;

	return;
}
void dfs(int cnt, int y, int x)
{
	if (cnt >= m)
	{
		//vectprint();
		//print();
		//result++;
		while (!q.empty()) q.pop();
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (back[i][j] == 1)
				{
					//printf("bfs start %d %d\n", i, j);
					tempmap[i][j] = 0;
					q.push(make_pair(i, j));
				}
				if (tempmap[i][j] == 2)	tempmap[i][j] = '*';
				if (tempmap[i][j] == 1) tempmap[i][j] = '-';
			}
		}
		//print();
		bfs();
		printf("\n");
		//backprint();
		print();
		printf("%d\n",result);
		init();
		return;
	}

	for (int i = y; i < n; i++)
	{
		for (int j = x; j < n; j++)
		{
			if (tempmap[i][j] == 2 && back[i][j] == 0)
			{
				back[i][j] = 1;
				dfs(cnt + 1, i, j); //인자를 조심해서 넣어라 필자는 y,x를 넣어서 시간을 많이 잡아먹음.
				back[i][j] = 0;
			}
			
		}
		x = 0;
	}

	// 일차원 포문으로 벡터에 넣고 3개를 뽑는경우의수 중요!! 시간 오래걸림
	/*for (int i = y; i < v.size(); i++)
	{
	vectorsize[i]=1;
	dfs(cnt + 1,i+1,x);
	vectorsize[i] = 0;
	}*/
	return;
}
int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%d", &map[i][j]);
			if (map[i][j] == 2) v.push_back(make_pair(i, j));
		}
	}
	init();
	dfs(0, 0, 0);
	printf("%d", result);
	return 0;
}
