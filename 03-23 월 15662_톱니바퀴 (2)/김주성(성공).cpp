// 실패
// 펑션콜순서
// copy() -> check() -> rotate() -> calcul() 순으로 함수가 콜된다.
// 1. 이차원 벡터에 푸시하면서 인풋값을 넣는다.
// 2. copy()함수로 인해 인풋값을 임시배열에 저장한다.
// 3. check()함수로 인해방향과 인덱스값 v값을 넘겨받고 오른쪽과 왼쪽으로 구분하여 rotate함수를 이용해 돌린다.
// 4. k만큼 다돌았으면 calcul()로 12시방향의 값을 ++해준다.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;
int t;
int k;

int copy2[1001][8];
int result;
int chk[1001][8];
void calcul(vector<deque<int>>& v)
{
	for (int i = 0; i < t; i++)
	{
		if (v[i][0] == 1)
			result++;
	}
}
void copy(vector<deque<int>>& v)
{
	for (int i = 0; i < t; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			copy2[i][j] = v[i][j];
		}
		//printf("\n");
	}
}

void print(vector<deque<int>>& v)
{
	for (int i = 0; i < t; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			printf("%d", v[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void rotate(int dir, int idx, vector<deque<int>>& v)
{
	//printf("d : %d i : %d\n",dir,idx);
	if (dir == 1)
	{
		int temp = 0;
		temp = v[idx].back();
		v[idx].pop_back();
		v[idx].push_front(temp);
	}
	else
	{
		int temp2 = 0;
		temp2 = v[idx].front();
		v[idx].pop_front();
		v[idx].push_back(temp2);
	}
	//print(v);
}
void check(int num, int dir, vector<deque<int>>& v)
{
	// dir이 1이면 시계방향 -1이면 반시계 방향
	// print(v);
	//printf("\nstart : %d %d\n", num, dir);
	// 오른쪽을 본다.
	int temp2 = dir * -1;
	for (int i = num+1; i < t; i++)
	{
		// 만약 다른 극이라면
		if (copy2[i][6] != copy2[i - 1][2])
		{
			//printf("오른쪽\n");
			
			rotate(temp2, i, v);
			temp2 = temp2 * -1;
		}
		else // 만약 같은 극이라면
		{
			break;
		}
	}
	// 왼쪽을 본다.
	temp2 = dir * -1;
	for (int i = num-1; i >= 0; i--)
	{
		// 만약 다른 극이라면
		if (copy2[i][2] != copy2[i + 1][6])
		{
			//printf("왼쪽\n");
			rotate(temp2, i, v);
			temp2 = temp2 * -1;
		}
		else // 만약 같은 극이라면
		{
			break;
		}
	}
	rotate(dir, num, v);
}
int main()
{
	scanf("%d", &t);
	vector<deque<int>>v(t);
	int a = 0;
	for (int i = 0; i < t; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			scanf("%1d", &a);
			v[i].push_back(a);
		}
	}
	scanf("%d", &k);
	int num = 0, dir = 0;
	for (int i = 0; i < k; i++)
	{
		//print(v);
		// 벡터를 복사한다.
		copy(v);
		scanf("%d %d", &num, &dir);
		check(num - 1, dir, v);
		//recopy(v,copy2);
		//print(v);
		// 복사한 벡터에 다시 넣는다.
	}
	calcul(v);
	printf("%d", result);
	return 0;
}
