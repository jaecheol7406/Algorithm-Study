// 0부터n-1까지 다돌려보고 만약 생성자가 n-1까지 안나오면 0출력 아니라면 i값 + i를 나눠주면서 나머지값을 더함

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int n;
int main()
{
	scanf("%d",&n);
	int sum = 0;
	int a = 0;
	int flag = 0;
	// i는 꼭 0부터 시작해야함!! 시간오래걸림
	for (int i = 0; i <= 1000001;i++)
	{
		a = i;
		sum = i;
		while (1)
		{
			if (a == 0) break;
			//printf("%d ",sum);
			sum += a % 10;
			a = a / 10;
		}
		//printf("%d\n",sum);
		if (n == sum)
		{
			flag = 1;
			printf("%d",i);
			break;
		}
		if(i==n-1) printf("0");
		// 생성자는 n보다 작아야됨으로 n-1까지만 봐야한다 클거나 같을수없음
	}
	return 0;
}
