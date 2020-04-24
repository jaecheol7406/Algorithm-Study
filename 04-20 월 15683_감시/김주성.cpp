//빽트래킹시 초기화에 조심해야된다.!!!

// 구조체 벡터에 y값 x값 map값을 넣는다.
// dfs(0)부터 시작 -> 미리 몇번돌지 cnt배열에 정해놓은값으로 돌면서 브루투 포스한다. -> 만약 현재값이 vector사이즈가 되면 리턴한다.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string>
#include <string.h>
using namespace std;

int n, m;
int map[10][10];

int cnt[6] = { 0,4, 2, 4, 4, 1 };
// 오른 아래 왼 위
struct a
{
	int y;
	int x;
	int data;
}cctv;
vector<a>v;
int minn = 987654321;
void fill_map(int idx,int dir)
{
	dir = dir % 4;
	if (dir == 0)
	{
		for (int i = v[idx].x+1; i < m; i++)
		{
			if (map[v[idx].y][i] == 6) break;
			map[v[idx].y][i] = 7;
			
		}
	}

	if (dir == 1)
	{
		for (int i = v[idx].y + 1; i < n; i++)
		{
			if (map[i][v[idx].x] == 6) break;
			map[i][v[idx].x] = 7;
			
		}
	}

	if (dir == 2)
	{
		for (int i = v[idx].x-1; i >= 0; i--)
		{
			if (map[v[idx].y][i] == 6) break;
			map[v[idx].y][i] = 7;
			
		}
	}

	if (dir == 3)
	{
		for (int i = v[idx].y-1; i >= 0; i--)
		{
			if (map[i][v[idx].x] == 6) break;
			map[i][v[idx].x] = 7;
			
		}
	}
}
void print()
{
	printf("\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%d ",map[i][j]);
		}
		printf("\n");
	}
}
void printtemp()
{
	printf("스타트\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
}
void calcul()
{
	int mincal=0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (map[i][j] == 0)
			{
				mincal++;
			}
		}
	}
	if (mincal < minn)
	{
		minn = mincal;
	}
}
void cpy(int(*a)[10], int(* b)[10])
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			a[i][j] = b[i][j];
		}
	}
}
void dfs(int q)
{
	//printf("%d\n",q);
	if (q == v.size())
	{
		// 최소값 계산
		calcul();
		// print();
		//printf("%d\n", minn);
		
		return;
	}
	int tempmap[10][10];
	// 빽트래킹 조심!! 여기다 선언해야된다!! 이것때문에 시간이 오래걸림....
	//printf("%d %d %d\n",q,v[q].data,cnt[v[q].data]);
	//printf("%d %d\n", v[q].data,cnt[v[q].data]);
	//cctv의 몇번째 인덱스인지 찾아서 몇번반복할지 계산하는 반복문.
	for (int i = 0; i < cnt[v[q].data]; i++)
	{
		memcpy(tempmap, map, sizeof(map));
		//printtemp();
		//cpy(tempmap,map);
		// 한방향을 채운다.
		// 7을 채움
		if (v[q].data == 1)
		{
			fill_map(q, i);
		}
		else if (v[q].data == 2)
		{
			//printf("2번 %d %d\n", i, q);
			fill_map(q, i);
			fill_map(q, i + 2);
		}
		else if (v[q].data == 3)
		{
			fill_map(q, i);
			fill_map(q, i + 3);
		}
		else if (v[q].data == 4)
		{
			fill_map(q, i);
			fill_map(q, i + 2);
			fill_map(q, i + 3);
		}
		else if (v[q].data == 5)
		{
			fill_map(q, i);
			fill_map(q, i + 1);
			fill_map(q, i + 2);
			fill_map(q, i + 3);
		}
		// 다음 인덱스를 증가시킨다.
		dfs(q + 1);
		// 초기화
		memcpy(map, tempmap, sizeof(tempmap));
		//cpy(map, tempmap);
		//printtemp();
	}
	//return;
}

int main()
{
	scanf("%d %d",&n,&m);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			scanf("%d",&map[i][j]);
			if (map[i][j] != 0 && map[i][j] != 6)
			{
				cctv.data = map[i][j];
				cctv.y = i;
				cctv.x = j;
				v.push_back(cctv);
				//v.push_back({i,j,map[i][j]});
			}
		}
	}

	//printf("%d %d %d\n",v[0].y,v[0].x,v[0].data);
	dfs(0);
	printf("%d",minn);
	return 0;
}
