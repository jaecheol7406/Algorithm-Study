#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>
using namespace std;
int n, m, k;
int rotmap[51][51];
int ro[7][4];
int visit[7];
int a[51][51];
int temp[7];
int tempmap[51][51];
int r, c, s;
int ys, ye, xs, xe;
int min = 987654321;

void minval()
{
   int sum = 0;
   for (int i = 0; i < n; i++)
   {
      sum = 0;
      for (int j = 0; j < m; j++)
      {
         sum+=rotmap[i][j];
      }
      if (min > sum)
      {
         min = sum;
      }
   }
}
void print()
{
   for (int i = 0; i < n; i++)
   {
      for (int j = 0; j < m; j++)
      {
         printf("%d",rotmap[i][j]);
      }
      printf("\n");
   }
   printf("\n");
}
void init()
{
   for (int i = 0; i < n; i++)
   {
      for (int j = 0; j < m; j++)
      {
         tempmap[i][j] = 0;
         rotmap[i][j] = 0;
      }
   }
}

void trans() // 입력을 한번 트랜스함
{
   for (int i = 0; i < n; i++)
   {
      for (int j = 0; j < m; j++)
      {
         rotmap[i][j]=tempmap[i][j]=a[i][j];
      }
   }
}
void retrans() // 입력을 다시 넣어줌
{
   for (int i = 0; i < n; i++)
   {
      for (int j = 0; j < m; j++)
      {
         tempmap[i][j] = rotmap[i][j];

      }
   }
}


void rotate(int v)
{
   
   int ys = ro[v][0];
   int xs = ro[v][1];
   int ye = ro[v][2];
   int xe = ro[v][3];

   int yer = abs(ye - ys);
   int xer = abs(xe - xs);
   int maxx = 0;
   if (yer > xer)
      maxx = yer;
   else
      maxx = xer;

   for (int q = 0; q < yer; q++) //  깊이만큼 돌린다.
   {
      /*int end = abs((xe - q) - (xs + q));
      if (end == 1) break;*/
      //printf("%d이다\n",q);
      //printf("%d이고",w);
      //int first = tempmap[ys+q+1][xs+q];
      //printf("첫번째%d\n",first);
      //printf("%d %d %d %d\n",ys,xs, ye, xe);
      //printf("(%d %d %d %d) q = %d\n", ys,xs,xe,ye,q);
      //printf("\n%d %d %d %d\n",ys+q, xs + q,ye-q, xe - q);

      
      for (int j = ys + q; j < ye - q; j++) // 아래
      {
         rotmap[j+1][xe - q] = tempmap[j][xe - q];
         //printf("%d ", tempmap[j][xe - q]);
      }
      

      //printf("\n");
      for (int j = ye - q; j >= ys+q+1; j--) // 위
      {
         rotmap[j - 1][xs + q] = tempmap[j][xs + q];
         //printf("%d ", tempmap[j][xs + q]);
      }
      //printf("\n");
      //rotmap[ys+q][xs+q] = first;
      
   }

   for (int q = 0; q < xer; q++)
   {
      //printf("\n");
      for (int j = xs + q; j < xe - q; j++) // 오른쪽
      {
         rotmap[ys + q][j + 1] = tempmap[ys + q][j];
         //printf("%d ",tempmap[ys + q][j]);
      }
      //printf("\n");
      for (int j = xe - q; j >= xs + q + 1; j--) // 왼쪽
      {
         rotmap[ye - q][j - 1] = tempmap[ye - q][j];
         //printf("%d ", tempmap[ye - q][j]);
      }
   }
}

void dfs(int t)
{
   if (t == k)
   {
      init();
      trans();
      
      for (int i = 0; i < k; i++)
      {
         //printf("%d 번째\n", temp[i]);
         //print();
         rotate(temp[i]);
         //print();
         retrans();
         
      }
      minval();
      //printf("\n");
      return;
   }
   for (int i = 0; i < k; i++)
   {
      if (visit[i] == 0)
      {
         visit[i] = 1;
         temp[t] = i;
         dfs(t + 1);
         visit[i] = 0;
      }
   }
   return;
}

void go()
{
   dfs(0);
}

int main()
{
   scanf("%d %d %d", &n, &m, &k);
   for (int i = 0; i < n; i++)
   {
      for (int j = 0; j < m; j++)
      {
         scanf("%d", &a[i][j]);
      }
   }
   
   for (int i = 0; i < k; i++)
   {
      scanf("%d %d %d", &r, &c, &s);
      ys = r - s - 1;
      ye = r + s - 1;
      xs = c - s - 1;
      xe = c + s - 1;
      ro[i][0] = ys;
      ro[i][1] = xs;
      ro[i][2] = ye;
      ro[i][3] = xe;
      /*for (int j = 0; j < 4; j++)
      {
         printf("%d ", ro[i][j]);
      }
      printf("\n");*/
   }
   
   go();
   printf("%d",min);
   return 0;
}