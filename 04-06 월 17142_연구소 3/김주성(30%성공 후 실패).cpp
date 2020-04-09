// 30%에서 틀렸습니다.
// init()함수로 초기화를 먼저하고 dfs()함수로 조합을 생성후 bfs()함수로 퍼트려가면서 구했다.
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
int total;
int virus;
void init()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			tempmap[i][j] = map[i][j];
			visit[i][j] = 0;
			virus = 0;
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
void printvisit()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d ", visit[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void bfs()
{
	//printf("\nstart : ");
	cnt = 0;
	
	while (!q.empty())
	{
		
		int qsize = q.size();
		int cy = q.front().first;
		int cx = q.front().second;
		//printf("%d %d\n",cy,cx);
		visit[cy][cx] = 1;
		//printf("bfs start %d %d\n", virus, total);
		
		//printf("%d\n",cnt);
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			int ny = cy + dy[i];
			int nx = cx + dx[i];
			if (ny < 0 || nx < 0 || ny >= n || nx >= n || visit[ny][nx] == 1 || tempmap[ny][nx] == 45) continue;
			q.push(make_pair(ny, nx));
			//printf("%d %d\n", virus, total);
			if (tempmap[ny][nx] == 0) virus++;
			visit[ny][nx] = 1;
			tempmap[ny][nx] = tempmap[cy][cx] + 1;
			cnt = tempmap[ny][nx];
		}

		//printf("%d", cnt);
		if (virus == total)
		{
			if (result > cnt) result = cnt;
			//printf("결과 : %d\n", result);
			break;
		}
	}
	
	
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
					q.push(make_pair(i, j));
					tempmap[i][j] = 0;
					
				}
				if (tempmap[i][j] == 2)	tempmap[i][j] = '*';
				if (tempmap[i][j] == 1) tempmap[i][j] = '-';
			}
		}
		//print();
		bfs();
		//printf("\n");
		//backprint();
		//print();
		//printvisit();
		//printf("%d\n",result);
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
			// 벽은 -1 , 바이러스 -2 빈곳은 -3으로표시
			if (map[i][j] == 2)
			{
				v.push_back(make_pair(i, j));
			}
			if (map[i][j] == 0)	total++;
		}
	};
	if (0 == total)
	{
		printf("0");
		return 0;
	}
	init();
	dfs(0, 0, 0);
	if (result == 987654321) result = -1;
	printf("%d", result);
	return 0;
}
