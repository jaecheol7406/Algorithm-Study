// 큐에 1부터 n까지넣고 pop 후 앞에값을 기억한후 pop후 push한다.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <queue>
#include <algorithm>
using namespace std;
int n;
queue<int>q;
void bfs()
{
	int cnt = 1;
	while (!q.empty())
	{
		int result = q.front();
		q.pop();
		
		if (cnt == n)
		{
			printf("%d ", result);
			break;
		}
		cnt++;
		
		int temp = q.front();
		q.pop();
		q.push(temp);
	}
	

}
int main()
{
	scanf("%d",&n);
	
	for (int i = 1; i <= n; i++)
	{
		q.push(i);
	}
	bfs();
	return 0;
}
