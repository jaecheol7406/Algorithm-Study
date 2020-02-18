#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
struct data_type
{
	int status;
	// 0�� ����� , 1�� ��Ȱ��, 2�� Ȱ��, 3�� ��������
	int LP, HP;
	// LP :Life point
	// HP ���� ���� : 0, ��Ȱ���ΰ�� ����, Ȱ�� ������ ��� ����
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
		//�ٱ⼼���� K�ð� ���� �����ɼ��ִ� �ִ����
		m = m + k + 2;
		n = n + k + 2;
		int curmap = 0;
		for (int q = 0; q < k; q++)
		{
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
				{
					//���� �����ϰ��
					if (map[curmap][i][j].status == 3)
					{
						// �ƹ����۵� ��������.
						map[1-curmap][i][j].status = map[curmap][i][j].status;
						continue;
					}
					//��Ȱ�� �����ϰ��
					else if (map[curmap][i][j].status == 1)
					{
						// ��Ȱ�� �ð�����
						map[1 - curmap][i][j].HP = map[curmap][i][j].HP + 1;
						map[1 - curmap][i][j].LP = map[curmap][i][j].LP;

						if (map[1 - curmap][i][j].HP == map[1 - curmap][i][j].LP)
						{
							map[1 - curmap][i][j].status = 2;
						}
						else
							map[1 - curmap][i][j].status = 1;
					}
					//Ȱ�� �����ΰ��
					else if (map[curmap][i][j].status == 2)
					{
						//Ȱ�� ���°� ����, ù�ð��� ���
						if (map[curmap][i][j].HP == map[curmap][i][j].LP)
						{
							//���� ��ġ���� �� �� �¿� Ž��
							for (int d = 0; d < 4; d++)
							{
								int i2, j2;
								i2 = i + dy[d];
								j2 = j + dx[d];
								//�ٱ� ������ �����ϴ� ������ ������� ���
								if (map[curmap][i2][j2].status == 0)
								{
									// �ϳ��� �ٱ⼼���� �����ϰ� �ִ°��
									if (map[1 - curmap][i2][j2].status == 0)
									{
										//�ش� �ٱ⼼���� ���� ����
										map[1 - curmap][i2][j2].status = 1;
										map[1 - curmap][i2][j2].LP = map[curmap][i][j].LP;
										map[1 - curmap][i2][j2].HP = 0;
									}
									// �ΰ� �̻��� �ٱ⼼���� ���� ���ÿ� �����Ϸ����ϴ� ���
									// �����(LP)�� ���� �ٱ⼼���� ���� ����
									else if (map[1 - curmap][i2][j2].status == 1 && map[1 - curmap][i2][j2].LP < map[curmap][i][j].LP)
										map[1 - curmap][i2][j2].LP = map[curmap][i][j].LP;
								
									
								}
							}
						}
					
						
						//Ȱ�� �ð� ����
						map[1 - curmap][i][j].HP = map[curmap][i][j].HP - 1;
						// Ȱ�� ���� �ð��� LP�ð� ��ŭ ������ ���
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