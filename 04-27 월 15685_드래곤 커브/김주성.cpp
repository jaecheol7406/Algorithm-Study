// 0 1 2 4 8 16 이렇게 세대가 증가될수록 길이가 증가된다. 그값을 st 인자로 넣어주고 
// 세대를 만들때 현재 좌표에서 (2*i+1)만큼 뺀 좌표를 계산해주면 드래곤커브세대를 생성할수있다.  

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
using namespace std;
int n;
int y, x, d, g;
int dy[4] = { 0,-1,0,1 };
int dx[4] = {1,0,-1,0};
int map[1024] = { 0, };
int origin[101][101];
int cnt;
int result;
void dfs(int d,int idx,int st)
{
	
	if(idx==0) map[st] = d;
	else
	{
		for (int i = 0; i < st; i++)
		{
			map[st + i] = (map[st + i - ((i * 2) + 1)] + 1)%4;
			//printf("de %d %d\n",st+i, st + i - ((i * 2)+1));
		}
	}
	
	//printf("\nval");
	for (int i = 0; i < st+st; i++)
	{
		//printf("%d ",map[i]);
	}
	//printf("\n");
	cnt = st;
	//printf("%d ", a);
}
void draw(int y, int x,int dir)
{
	//printf("val %d\n",dir);
	if (cnt == 0)
	{
		origin[y][x] = 1;
		int ny = y + dy[dir];
		int nx = x + dx[dir];
		origin[ny][nx] = 1;
	}
	else
	{
		for (int i = 0; i < cnt * 2; i++)
		{
			origin[y][x] = 1;
			//printf("%d ", map[i]);
			int ny = y + dy[map[i]];
			int nx = x + dx[map[i]];
			if (ny < 0 || nx < 0 || nx>100 || ny>100) continue;
			origin[ny][nx] = 1;
			y = ny;
			x = nx;
		}
	}
	
	//printf("\n\n");
}
void print()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			printf("%d ",origin[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void check()
{

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (origin[i][j] && origin[i][j + 1] && origin[i + 1][j] && origin[i + 1][j + 1]) result++;
		}
	}
}
int main()
{
	scanf("%d",&n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d %d %d %d",&y,&x,&d,&g);
		//printf("%d세대 \n", g);
		dfs(d, 0, 0);
		int idx = 1;
		for (int i = 1; i <= g; i++)
		{
			dfs(d,i,idx);
			idx *= 2;
		}
		draw(x,y,d);
		//printf("\n");
		//print();
	}
	check();
	printf("%d",result);
	return 0;
}
