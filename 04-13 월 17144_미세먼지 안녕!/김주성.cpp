//원본을 훼손하지말자
// 함수 순서 trans() - spread() - trans() - upmove(sy, sx) - downmove(sy2, sx2);
// 이순서로 tempmap에 map을 복사한후 확산하고 다시 복사 upmove와 downmove를각자함
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
int n, m,t;
int map[51][51];
int tempmap[51][51];
vector <pair<int,int>>v;
int dy[4] = {0,0,-1,1};
int dx[4] = {1,-1,0,0};
int result = 0;
void calcul()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (map[i][j] != -1)
			{
				result += map[i][j];
			}
		}
	}
	return;
}
void trans()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			tempmap[i][j]=map[i][j];
		}
	}
	return;
}
void print()
{
	printf("\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	return;
}
void spread()
{
	
	//printf("%d %d\n",sy,sx);
	//printf("%d %d\n", sy2, sx2);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (tempmap[i][j] == 0 || tempmap[i][j] == -1) continue;
			else
			{
				int temp = 0;
				//printf("%d %d %d\n",i,j, tempmap[i][j]);
				temp = floor(tempmap[i][j] / 5);
				int amount = 0;
				for (int q = 0; q < 4; q++)
				{
					int ny = i + dy[q];
					int nx = j + dx[q];
					if (ny < 0 || nx < 0 || ny >= n || nx >= m || tempmap[ny][nx]==-1) continue;
					map[ny][nx] += temp;
					amount += temp;
				}
				//printf("amount %d\n",amount);
				map[i][j] -= amount;
			}
		}
	}

	return;

}
void upmove(int y,int x)
{
	// 오른쪽 y축 고정 m-1부터 x+1까지
	map[y][x + 1] = 0;
	for (int i = m-2; i >= x+1; i--)
	{
		map[y][i+1]= tempmap[y][i];
		//printf("%d %d\n",y,i);
	}
	// 위 x축 m-1고정 1부터n-1
	for (int i = 1; i < y+1; i++)
	{
		map[i-1][m - 1] = tempmap[i][m - 1];
		//printf("%d %d\n", i,m-1);
	}
	// 왼 y축 고정
	for (int i = 1; i < m; i++)
	{
		map[0][i - 1] = tempmap[0][i];
	}
	// 아래 x축 고정
	for (int i = 0; i < y + 2; i++)
	{
		if (tempmap[i + 1][0] == -1) break;
		map[i+1][0] = tempmap[i][0];
	}
	return;
}
void downmove(int y,int x)
{
	// 오른쪽 y축 고정
	map[y][x + 1] = 0;
	for (int i = m - 2; i >= x + 1; i--)
	{
		map[y][i + 1] = tempmap[y][i];
		//printf("%d %d\n",y,i);
	}
	// 아래 x축 고정
	for (int i = y; i < n; i++)
	{
		map[i + 1][m - 1] = tempmap[i][m - 1];
	}
	// 왼 y축 고정
	for (int i = 1; i < m; i++)
	{
		map[n-1][i - 1] = tempmap[n-1][i];
	}
	// 위 x축 고정
	for (int i = y+2; i < n; i++)
	{
		if (tempmap[i - 1][0] == -1) break;
		map[i - 1][0] = tempmap[i][0];
		//printf("%d %d\n", i, m - 1);
	}
	return;
}
int main()
{
	scanf("%d %d %d", &n, &m, &t);


	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			scanf("%d", &map[i][j]);
			if (map[i][j] == -1)
			{
				//printf("%d %d\n", i, j);
				v.push_back(make_pair(i, j));
			}
		}
	}
	
	int sy = 0;
	int sx = 0;
	int sy2 = 0;
	int sx2 = 0;
	sy = v.front().first;
	sx = v.front().second;
	sy2 = v[1].first;
	sx2 = v[1].second;
	for (int i = 0; i < t; i++)
	{
		trans();
		spread(); // 확산
		trans();
		//print();
		upmove(sy, sx);
		//print();
		downmove(sy2, sx2);
		//print();
	}
	calcul();
	printf("%d",result);
	return 0;
}
