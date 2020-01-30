package com.exam.day0130;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

/**
 *  연구소 3 : https://www.acmicpc.net/problem/17142
 */
public class Ex17142 {
	
	static class Virus {
		int x;
		int y;
		
		public Virus(int x, int y) {
			this.x = x;
			this.y = y;
		}
	}
	
   static int N; // 연구소 크기
   static int M; // 놓을수 있는 바이러스 개수

   static Virus[] viruses = new Virus[10]; // 총 바이러스
   static int virus_cnt = 0; // 총 활성/비활성 바이러스 개수

   static boolean[] check;
   static int[][] a; // 연구소

   static int[][] time; // 감염되는데 걸리는시간

   static int[] dx = { 0, 0, -1, 1 };
   static int[] dy = { 1, -1, 0, 0 };

   static int ans = -1;
   
   // idx : 결정할 바이러스의 인덱스, num : 결정된 개수
   public static void dfs(int idx, int num) { 
      if (num == M) {
         bfs();
         return;
      }

      if (idx >= virus_cnt) {
         return;
      }

      check[idx] = true;
      dfs(idx + 1, num + 1);
      check[idx] = false;
      dfs(idx + 1, num);
   }

   public static void bfs() {
      Queue<Virus> q = new LinkedList<Virus>();

      for (int i = 0; i < virus_cnt; i++) {
         if (check[i] == true) {
            q.add(viruses[i]);
            time[viruses[i].x][viruses[i].y] = 1;
         }
      }

      int spandingTime = 0;
      while (!q.isEmpty()) {
         Virus v = q.remove();
         for (int k = 0; k < 4; k++) {
            int nx = v.x + dx[k];
            int ny = v.y + dy[k];

            if (checkRange(nx, ny) && a[nx][ny] != 1 && time[nx][ny] == 0) {
               time[nx][ny] = time[v.x][v.y] + 1;
               if(a[nx][ny] == 0) {
                  spandingTime = Math.max(spandingTime, time[nx][ny] - 1);                  
               }
               q.add(new Virus(nx, ny));
            }
         }
      }

      boolean ok = true;
      for (int i = 0; i < N; i++) {
         for (int j = 0; j < N; j++) {
            if(a[i][j] == 0) {
               if(time[i][j] == 0) {
                  ok = false;
               }
            }
            
            time[i][j] = 0;
         }
      }
      
      if(ok) {
         if(ans == -1) {
            ans = spandingTime;
         } else {
            ans = Math.min(ans, spandingTime);
         }
      }

   }

   public static boolean checkRange(int r, int c) {
      return 0 <= r && r < N && 0 <= c && c < N;
   }

   public static void main(String[] args) throws Exception {
      BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
      StringTokenizer st;

      st = new StringTokenizer(br.readLine());
      N = Integer.parseInt(st.nextToken());
      M = Integer.parseInt(st.nextToken());

      a = new int[N][N];
      time = new int[N][N];
      
      for (int i = 0; i < N; i++) {
         st = new StringTokenizer(br.readLine());
         for (int j = 0; j < N; j++) {
            a[i][j] = Integer.parseInt(st.nextToken());
            if(a[i][j] == 2) {
                viruses[virus_cnt] = new Virus(i, j);
                virus_cnt++;
            }
         }
      }
      
      check = new boolean[virus_cnt];
      
      dfs(0, 0);
      
      System.out.println(ans);
   }
}
