//1. rowcheck();
//2. rowcnt();
//3. posinit();
//4. columcheck();
//5. columcnt();
//순으로 프로그램이 돌아간다.
//1. 은 행순으로 서치 3은 열순으로 서치한다.
//1. n+1값이 큰경우와 n+1값이 작은경우 n+1이 같은경우 그렇지 않은경우 4가지로 조건으로 나누었다.
//1-1. n+1값이 1큰경우는 역방향으로 경사로를 l길이만큼 포문을 돌려서 pos배열에 경사로가 있는지 체크해주고 visit도 체크해준다.
//1-2. n+1값이 1작은경우 순방향으로 경사로를 l길이만큼 포문을 돌려서 pos배열에 경사로가 있는지 체크해주고 visit도 체크해준다.
//1-3. n+1값이 같은경우 visit을 체크해준다.
//1-4. n+1값이 그렇지 않은경우 반복문을 빠져나온다.
//2. row가 몇개 빙고가 되었는지 확인
//3. 경사로 초기화
//4.5. 열은 행과 똑같이 연산한다.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
typedef struct c
{
	int visit;
	int possible;
}cehck;
int map[101][101];
int visit[101][101];
int n, l;
int result;
int pos[101][101];
void print()
{
	printf("\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d ",visit[i][j]);
		}
		printf("\n");
	}
}
void posinit()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			pos[i][j] = 0;
		}
	}
}
void rowcnt()
{

	for (int i = 0; i < n; i++)
	{
		int cnt = 0;
		for (int j = 0; j < n; j++)
		{
			if (visit[i][j] == 1)
			{
				cnt++;
			}
		}
		if (cnt == n) result++;
		//printf("\n");
	}
}
void columcnt()
{
	for (int i = 0; i < n; i++)
	{
		int cnt = 0;
		for (int j = 0; j < n; j++)
		{
			if (visit[j][i] == 1)
			{
				cnt++;
			}
		}
		if (cnt == n) result++;
		//printf("\n");
	}
}
void rowcheck()
{
	int fc=1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			// j+1이 1클경우
			if (j + 1 >= n) break;
			if (map[i][j] + 1 == map[i][j+1])
			{
				for (int k = 0; k < l; k++)
				{
					if (map[i][j-k] == map[i][j] && pos[i][j-k]==0)
					{
						visit[i][j] = fc;
						visit[i][j + 1] = fc;
						visit[i][j-k] = fc;
						pos[i][j - k] = 1;
					}
					else
					{
						visit[i][j] = 0;
						visit[i][j + 1] = 0;
						visit[i][j-(k+1)] = 0;
						break;
					}
				}
			}
			// j+1이 1작을 경우
			else if (map[i][j] == map[i][j+1] +1)
			{
				
				for (int k = 1; k <= l; k++)
				{
					if (map[i][j+k] == map[i][j + 1] && pos[i][j + k] == 0)
					{
						visit[i][j] = fc;
						visit[i][j+k]=fc;
						pos[i][j + k] = 1;
					}
					else
					{
						visit[i][j] = 0;
						visit[i][j+(k-1)] = 0;
						break;
					}
				}
			}
			// 다음 값이 같을경우
			else if (map[i][j] == map[i][j + 1])
			{
				visit[i][j] = fc;
				visit[i][j + 1] = fc;
			}
			else
			{
				break;
			}
		}
	}
}
void columcheck()
{
	int fc = 1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			// j+1이 1클경우
			if (j + 1 >= n) break;
			if (map[j][i] + 1 == map[j+1][i])
			{
				
				for (int k = 0; k < l; k++)
				{
					if (map[j - k][i] == map[j][i] && pos[j - k][i] ==0)
					{
						visit[j][i] = fc;
						visit[j - k][i] = fc;
						visit[j + 1][i] = fc;
						pos[j - k][i] = 1;
					}
					else
					{
						visit[j][i] = 0;
						visit[j - (k + 1)][i] = 0;
						visit[j + 1][i] = 0;
						break;
					}
				}
			}
			// j+1이 1작을 경우
			else if (map[j][i] == map[j + 1][i] + 1)
			{
				for (int k = 1; k <= l; k++)
				{
					if (map[j + k][i] == map[j + 1][i] && pos[j + k][i] ==0)
					{
						visit[j][i] = fc;
						visit[j + k][i] = fc;
						pos[j + k][i] = 1;
					}
					else
					{
						visit[j][i] = 0;
						visit[j + (k - 1)][i] = 0;
						break;
					}
				}
			}
			// 다음 값이 같을경우
			else if (map[j][i] == map[j + 1][i])
			{
				visit[j][i] = fc;
				visit[j + 1][i] = fc;
			}
			else
			{
				break;
			}
		}
	}
}

int main()
{
	scanf("%d %d",&n,&l);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%d",&map[i][j]);
		}
	}
	rowcheck();
	//print();
	rowcnt();
	posinit();
	columcheck();
	columcnt();
	//print();

	printf("%d",result);
	return 0;
}
