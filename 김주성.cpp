// 양념 + 후라이드가 반반 치킨 보다 쌀경우 
// 아닐경우.
// 아닐경우에서
// 반반치킨으로만 다사는경우
// 반반치킨 + 양념 + 후라이드로 사는경우
// 총 3가지 경우를 다구해서 최소값을 출력했슴당!!
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int a, b, c, x, y,x1,y1;
int main()
{
	int result = 0;
	scanf("%d %d %d %d %d",&a,&b,&c,&x,&y);
	x1 = x; 
	y1 = y;
	if (a + b < 2 * c)
	{
		result = a * x + b * y;
	}
	else
	{
		while (1)
		{
			if (x == 0 && y == 0) break;
			if (y > 0 && x > 0)
			{
				result += 2 * c;
				y--;
				x--;
				//printf("%d\n", result);
			}
			else
			{
				//printf("%d %d\n",x,y);
				result += a * x + b * y;
				x = 0;
				y = 0;
				//printf("%d\n", result);
			}
		}
		int result1 = 0;
		while (1)
		{
			if (x1 == 0 && y1 == 0) break;
			if (y1 > 0 || x1 > 0)
			{
				result1 += 2 * c;
				y1--;
				x1--;
				//printf("%d\n", result);
			}
			if (y1 < 0) y1 = 0;
			if (x1 < 0) x1 = 0;
		}
		if (result1 < result) result = result1;
	}
	printf("%d",result);
	return 0;
}
