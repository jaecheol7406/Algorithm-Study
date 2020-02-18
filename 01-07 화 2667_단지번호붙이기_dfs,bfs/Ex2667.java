package com.exam.day0107;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

/**
 *  단지번호붙이기 : https://www.acmicpc.net/problem/2667 
 *  문제 유형 : 완전탐색
 *  시간복잡도 : (N^2) 맞나(?)
 */

class Pair {
	int x;
	int y;
	
	public Pair(int x, int y) {
		this.x = x;
		this.y = y;
	}
}

public class Ex2667 {
	
	static int[] dx = {0, 0, 1, -1};
	static int[] dy = {1, -1, 0, 0};
	
	static void bfs(int[][] map, int[][] group, int x, int y, int n, int cnt) {
		Queue<Pair> q = new LinkedList<Pair>();
		q.add(new Pair(x, y));
		group[x][y] = cnt;
		
		while(!q.isEmpty()) {
			Pair p = q.remove();
			x = p.x;
			y = p.y;
			
			for(int k = 0; k < 4; k++) {
				int nx = x + dx[k];
				int ny = y + dy[k];
				
				if(nx >= 0 && nx < n && ny >= 0 && ny < n) {
					if(map[nx][ny] == 1 && group[nx][ny] == 0) {
						q.add(new Pair(nx, ny));
						group[nx][ny] = cnt;
					}
				}
			}
		}
	}
	
	static void dfs(int[][] map, int[][] group, int x, int y, int n, int cnt) {
		group[x][y] = cnt;
		
		for(int k = 0; k < 4; k++) {
			int nx = x + dx[k];
			int ny = y + dy[k];
			
			if(nx >= 0 && nx < n && ny >= 0 && ny < n) {
				if(map[nx][ny] == 1 && group[nx][ny] == 0) {
					group[nx][ny] = cnt;
					dfs(map, group, nx, ny, n, cnt);
				}
			}
		}
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int n = Integer.parseInt(br.readLine()); // 지도의 크기
		
		int[][] map = new int[n][n]; // 지도
		
		for(int i = 0; i < n; i++) {
			String s = br.readLine();
			for(int j = 0; j < n; j++) {
				map[i][j] = s.charAt(j) - '0';
			}
		}
		
		int[][] group = new int[n][n]; // 단지
		int cnt = 0; // 총 단지 수
		
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				if(map[i][j] == 1 && group[i][j] == 0) {
					bfs(map, group, i, j, n, ++cnt);
//					dfs(map, group, i, j, n, ++cnt);
				}
			}
		}
		
		int[] dan = new int[cnt]; // 각 단지내 집의 수
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				if(group[i][j] != 0) {
					dan[group[i][j] - 1] += 1;
				}
			}
		}
		
		Arrays.sort(dan); // 각 단지내 집의 수를 오름차순으로 정렬(문제 출력 조건)
		System.out.println(cnt);
		for(int i = 0; i < cnt; i++) {
			System.out.println(dan[i]);
		}
		
	}
}
