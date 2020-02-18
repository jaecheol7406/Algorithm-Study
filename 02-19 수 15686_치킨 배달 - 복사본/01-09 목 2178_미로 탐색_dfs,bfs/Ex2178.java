package com.exam.day0109;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

/**
 *  미로 탐색 : https://www.acmicpc.net/problem/2178
 *  Solution : http://codeplus.codes/3c4ab88008f14d8aa05c1885170b99f4
 */
public class Ex2178 {
	
	static class Pair {
		int x;
		int y;
		
		public Pair(int x, int y) {
			this.x = x;
			this.y = y;
		}
	}
	
	static int n;
	static int m;
	static int[][] a;
	static int[][] d;
	static int[] dx = {0, 0, 1, -1};
	static int[] dy = {1, -1, 0, 0};
	
	static void bfs(int x, int y) {
		Queue<Pair> q = new LinkedList<Pair>();
		q.add(new Pair(x, y));
		d[x][y] = 1;
		
		while(!q.isEmpty()) {
			Pair p = q.remove();
			x = p.x;
			y = p.y;
			
			for(int k = 0; k < 4; k++) {
				int nx = x + dx[k];
				int ny = y + dy[k];
				
				if(nx >= 0 && nx < n && ny >= 0 && ny < m) {
					if(a[nx][ny] == 1 && d[nx][ny] == 0) {
						q.add(new Pair(nx, ny));
						d[nx][ny] = d[x][y] + 1;
					}
				}
			}
		}
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		
		st = new StringTokenizer(br.readLine());
		n = Integer.parseInt(st.nextToken());
		m = Integer.parseInt(st.nextToken());
		
		a = new int[n][m];
		String s;
		for(int i = 0; i < n; i++) {
			s = br.readLine();
			for(int j = 0; j < m; j++) {
				a[i][j] = s.charAt(j) - '0';
			}
		}
		
		d = new int[n][m];
		bfs(0, 0);
		
		System.out.println(d[n - 1][m - 1]);
	}
	
}
