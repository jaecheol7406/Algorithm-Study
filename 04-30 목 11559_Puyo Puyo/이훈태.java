package com.exam.baek;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

/**
 *  Puyo Puyo : https://www.acmicpc.net/problem/11559 
 *  
 *  Solution
 *  1. 아래에서부터 블록을 확인한다. 빈 공간(.)은 무시.
 *  2. 블록을 발견하면 BFS 탐색을 통해 같은 색깔의 블록이 몇 개나 인접해 있는지 확인.
 *  3. 만약 인접한 블록이 4개 이상이면, 서로 연결된 블록을 모두 터트린다. 터트린 블록은 빈 공간으로 만든다.
 *  4. 위쪽 끝까지 1~3 과정을 반복.
 *  5. 만약 블록이 한 번이라도 터졌다면 카운트를 1 증가시키고, 아래로 떨어질 수 있는 블록 있는지 확인.
 *  6. 블록이 한 번이라도 터졌다면 1~5 과정을 반복, 만약 한 번도 안터졌다면 프로그램 종료 
 */
public class Ex11559 {
	static class Pair {
		int x;
		int y;
		
		public Pair(int x, int y) {
			this.x = x;
			this.y = y;
		}
	}
	
	static final int n = 12;
	static final int m = 6;
	
	static char[][] a = new char[n][m + 1];
	static boolean[][] check = new boolean[n][m + 1];
	
	static int[] dx = {-1, 0, 1, 0};
	static int[] dy = {0, 1, 0, -1};
	
	
	static void solve() {
		int ans = 0;
		
		while (crash()) {
			fall();
			ans += 1;
		}
		
		System.out.println(ans);
	}
	
	
	static boolean crash() {
		// 충돌할 수 있는 블록이 있는지 확인.
		boolean ok = false;
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				check[i][j] = false;
			}
		}
		
		for (int i = n - 1; i >= 0; i--) {
			for (int j = m - 1; j >= 0; j--) {
				if ( check[i][j] || a[i][j] == '.' ) continue;
				if ( bfs(i, j, a[i][j]) ) ok = true;
			}
		}
		
		return ok;
	}
	
	
	static boolean bfs(int i, int j, char c) {
		Queue<Pair> q = new LinkedList<Pair>();
		List<Pair> block = new ArrayList<Pair>();
		
		q.add(new Pair(i, j));
		check[i][j] = true;
		block.add(new Pair(i, j));
		
		while (!q.isEmpty()) {
			Pair p = q.remove();
			
			int x = p.x;
			int y = p.y;
			
			for(int k = 0; k < 4; k++) {
				int nx = x + dx[k];
				int ny = y + dy[k];
				
				if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
				if (check[nx][ny] || a[nx][ny] != c) continue;
				
				check[nx][ny] = true;
				q.add(new Pair(nx, ny));
				block.add(new Pair(nx, ny));
			}
		}
		
		if (block.size() >= 4) {
			for (Pair p : block) {
				a[p.x][p.y] = '.';
			}
			
			return true;
		} else {
			return false;
		}
	}
	
	
	static void fall() {
		for (int j = 0; j < m; j++) {
			for (int i = n - 1; i >= 0; i--) {
				if (a[i][j] == '.') continue;
				for (int k = n - 1; k >= i; k--) {
					if (a[k][j] == '.') {
						a[k][j] = a[i][j];
						a[i][j] = '.';
					}
				}
			}
		}
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		for (int i = 0; i < n; i++) {
			String str = br.readLine();
			for (int j = 0; j < m; j++) {
				a[i][j] = str.charAt(j);
			}
		}
		
		solve();
	}
	
}