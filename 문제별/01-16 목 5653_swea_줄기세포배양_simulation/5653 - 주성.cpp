#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
struct data_type
{
	int status;
	// 0은 빈공간 , 1은 비활성, 2는 활성, 3은 죽은상태
	int LP, HP;
	// LP :Life point
	// HP 죽은 상태 : 0, 비활성인경우 증가, 활성 상태일 경우 감소
};
data_type map[2][450][450];
int cntmap[450][450];
int n, m, k;
int dy[4] = { 0,0,1,-1 };
int dx[4] = { 1,-1,0,0 };
void init()
{
		for (int i = 0; i < 450; i++)
		{
			for (int j = 0; j < 450; j++)
			{
				for (int k = 0; k < 2; k++)
				{
					map[k][i][j].status = 0;
				}
			}
		}
}
void print()
{
	for (int k = 0; k < 1; k++)
	{
		for (int i = 0 + k / 2 + 1; i < n + k / 2 + 1; i++)
		{
			for (int j = 0 + k / 2 + 1; j < m + k / 2 + 1; j++)
			{
				printf("%d", map[k][i][j].HP);
			}
		}
	}
}
int main()
{
	int t;
	scanf("%d",&t);
	
	for (int i = 1; i <= t; i++)
	{
		int sum = 0;
		scanf("%d %d %d",&n,&m,&k);
		
		//printf("go %d %d %d\n",n,m,k);
		init();
		for (int i = 0+k/2+1; i < n+ k / 2 + 1; i++)
		{
			for (int j = 0+k / 2 + 1; j < m+ k / 2 + 1; j++)
			{
				scanf("%d",&map[0][i][j].LP);
				if (map[0][i][j].LP > 0)
				{
					map[0][i][j].status = 1;
					map[0][i][j].HP = 0;
				}
				//printf("gogo %d ", map[0][i][j].LP);
			}
		}
		//print();
		//printf("\n");
		//줄기세포가 K시간 내에 분포될수있는 최대범위
		m = m + k + 2;
		n = n + k + 2;
		int curmap = 0;
		for (int q = 0; q < k; q++)
		{
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
				{
					//죽은 세포일경우
					if (map[curmap][i][j].status == 3)
					{
						// 아무동작도 하지않음.
						map[1-curmap][i][j].status = map[curmap][i][j].status;
						continue;
					}
					//비활성 상태일경우
					else if (map[curmap][i][j].status == 1)
					{
						// 비활성 시간증가
						map[1 - curmap][i][j].HP = map[curmap][i][j].HP + 1;
						map[1 - curmap][i][j].LP = map[curmap][i][j].LP;

						if (map[1 - curmap][i][j].HP == map[1 - curmap][i][j].LP)
						{
							map[1 - curmap][i][j].status = 2;
						}
						else
							map[1 - curmap][i][j].status = 1;
					}
					//활성 상태인경우
					else if (map[curmap][i][j].status == 2)
					{
						//활성 상태가 된후, 첫시간일 경우
						if (map[curmap][i][j].HP == map[curmap][i][j].LP)
						{
							//현재 위치에서 상 하 좌우 탐색
							for (int d = 0; d < 4; d++)
							{
								int i2, j2;
								i2 = i + dy[d];
								j2 = j + dx[d];
								//줄기 세포가 번식하는 방향이 비어있을 경우
								if (map[curmap][i2][j2].status == 0)
								{
									// 하나의 줄기세포가 번식하고 있는경우
									if (map[1 - curmap][i2][j2].status == 0)
									{
										//해당 줄기세포가 셀을 차지
										map[1 - curmap][i2][j2].status = 1;
										map[1 - curmap][i2][j2].LP = map[curmap][i][j].LP;
										map[1 - curmap][i2][j2].HP = 0;
									}
									// 두개 이상의 줄기세포가 셀에 동시에 번식하려고하는 경우
									// 생명력(LP)가 높은 줄기세포가 셀을 차지
									else if (map[1 - curmap][i2][j2].status == 1 && map[1 - curmap][i2][j2].LP < map[curmap][i][j].LP)
										map[1 - curmap][i2][j2].LP = map[curmap][i][j].LP;
								
									
								}
							}
						}
					
						
						//활성 시간 증가
						map[1 - curmap][i][j].HP = map[curmap][i][j].HP - 1;
						// 활성 상태 시간이 LP시간 만큼 지났을 경우
						if (map[1 - curmap][i][j].HP == 0)
						{
							map[1 - curmap][i][j].status = 3;
						}
						else
							map[1 - curmap][i][j].status = 2;
					}
		
				}
			curmap = 1 - curmap;

		}
		int ans = 0;
		for (int i = 0; i < 450; i++)
		{
			for (int j = 0; j < 450; j++)
			{
				if (map[curmap][i][j].status == 1 || map[curmap][i][j].status == 2) ans++;
			}
		}

		printf("#%d %d\n", t,ans);
	}
	//print();



	return 0;
}