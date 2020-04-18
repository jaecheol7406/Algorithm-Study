// caulcul() -- hangcul or yulcul() 연산을 시행한다.
// 설계시 hang연산 할떄 행연산 갱신시점부분에서 오래걸림

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
int map[101][101];
vector<int>v;
int cnt = 0;
int r, c, k;
int hang = 3;
int yul = 3;
void print()
{
	printf("\n");
	for (int i = 0; i < hang; i++)
	{
		for (int j = 0; j < yul; j++)
		{
			printf("%d ",map[i][j]);
		}
		printf("\n");
	}
	return ;
}
bool incc(int a, int b)
{
	return a < b;
}
void trans(int tempmap[][101])
{
	for (int i = 0; i < hang; i++)
	{
		for (int j = 0; j < yul; j++)
		{
			map[i][j]= tempmap[i][j];
		}
	}
}
int yulcal()
{
	int tempmap[101][101] = { 0, };
	int maxhang = 0;
	for (int i = 0; i < yul; i++)
	{
		vector<pair<int, int>>temp;
		int tempv[101] = { 0, };
		for (int j = 0; j < hang; j++)
		{
			tempv[map[j][i]]++;
		}
		for (int j = 1; j < 101; j++)
		{
			//printf("%d ",tempv[j]);
			if (tempv[j] != 0)
			{
				temp.push_back(make_pair(tempv[j], j));
				//printf("%d %d\n", tempv[i],i);
			}
		}
		//printf("\n");
		sort(temp.begin(), temp.end());
		//sort(temp.begin(), temp.end());
		for (int i = 0; i < temp.size(); i++)
		{
			//printf("%d %d ", temp[i].second, temp[i].first);
		}
		//printf("\n");
		
		if (maxhang < temp.size() * 2)
		{
			maxhang = temp.size() * 2;
		}
		
		int idx = 0;
		for (int w = 0; w < temp.size(); w++)
		{
			if (idx >= 100)
			{
				cnt = -1;
				return 1;
			}
			tempmap[idx][i] = temp[w].second;
			idx += 1;
			tempmap[idx][i] = temp[w].first;
			idx += 1;
		}

		//for (int j = 0; j < yul; j++)
		//{
		//	printf("%d ",tempmap[i][j]);
		//}
		//printf("\n");
	}
	//printf("yul : %d\n",yul);
	hang = maxhang;
	trans(tempmap);
	//print();
	return 0;
}

int hangcal()
{
	int tempmap[101][101] = {0,};
	int maxyul = 0;
	//print();
	for (int i = 0; i < hang; i++)
	{
		vector<pair<int, int>>temp;
		int tempv[101] = { 0, };
		int c=0;
		for (int j = 0; j < yul; j++)
		{
			tempv[map[i][j]]++;
			//printf("cnt %d ",cnt++);
			//printf("%d %d\n", map[i][j],tempv[map[i][j]]);
		}
		for (int j = 1; j < 101; j++)
		{
			if (tempv[j] != 0)
			{
				temp.push_back(make_pair(tempv[j], j));
				
				//printf("%d %d\n", tempv[i],i);
			}
		}
		//printf("\n");
		sort(temp.begin(), temp.end());
		//sort(temp.begin(), temp.end());
		/*for (int j = 0; i < temp.size(); i++)
		{
			printf("%d %d ", temp[j].second, temp[j].first);
		}*/
		//printf("\n");
		
		if (maxyul < temp.size()*2)
		{
			maxyul = temp.size()*2;
		}
		
		int idx = 0;
		for (int w = 0; w < temp.size(); w++)
		{
			if (idx > 100)
			{
				cnt = -1;
				return 1;
			}
			tempmap[i][idx] = temp[w].second;
			idx +=1;
			tempmap[i][idx] = temp[w].first;
			idx += 1;
		}

		//for (int j = 0; j < yul; j++)
		//{
		//	printf("%d ",tempmap[i][j]);
		//}
		//printf("\n");
	}
	//printf("yul : %d\n",yul);
	yul = maxyul;
	trans(tempmap);
	
	//print();
	
	return 0;
}
void calcul()
{
	int result=0;
	while(result != 1)
	{
		//printf("%d %d\n",hang,yul);
		if (map[r - 1][c - 1] == k)
		{
			break;
		}
		if (hang >= yul)
		{
			
			result = hangcal();
			if (result == 1) break;
		}
		else
		{
			result = yulcal();
			if (result == 1) break;
		}
		//print();
		cnt++;
		if (cnt > 100)
		{
			cnt = -1;
			break;
		}
	}
	
	return;
}
int main()
{
	scanf("%d %d %d",&r,&c,&k);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			scanf("%d", &map[i][j]);
		}
	}
	//print();
	calcul();
	printf("%d\n",cnt);
	return 0;
}
