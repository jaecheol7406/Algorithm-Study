package com.exam.day0107;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

/**
 *  로봇 : https://www.acmicpc.net/problem/1726
 *  문제 유형 : 완전탐색 + 시뮬레이션
 *  시간복잡도 : 
 */
public class Ex1726 {
	
	static class Robot {
		int x;   // 행
		int y;   // 열
		int dir; // 방향
		
		public Robot(int x, int y, int dir) {
			this.x = x;
			this.y = y;
			this.dir = dir;
		}
	}
	
	static int n, m; // n : 행, m : 열
	static int[][] map = new int[101][101]; // 공장
	static int[][][] dist = new int[100][100][4];
	static int[] dx = {0, 0, 1, -1};
	static int[] dy = {1, -1, 0, 0};
	static int s_x, s_y, s_d, e_x, e_y, e_d;
	
	static void bfs() {
		Queue<Robot> q = new LinkedList<Robot>();
		q.add(new Robot(s_x - 1, s_y - 1, s_d - 1));
		
		while(!q.isEmpty()) {
			Robot rb = q.remove();
			
			int x = rb.x;
			int y = rb.y;
			int d = rb.dir;
			
			if(x == e_x - 1 && y == e_y - 1 && d == e_d - 1) {
				System.out.println(dist[x][y][d]);
				return;
			}
			
			// 칸 이동
			for(int i = 1; i <= 3; i++) {
				// 이동할 수 있는 칸 수를 모두 확인하여 큐에 넣어준다.
				int nx = x + dx[d] * i;
				int ny = y + dy[d] * i;
				
				/*
				 *  이동할 때 벽이 있다면 break.(짧은거리를 못간다면 긴 거리는 무조건 못가기 때문)
				 */
				if(nx < 0 || nx >= n || ny < 0 || ny >= m) break; 				
				if(map[nx][ny] == 1) break;
				if(dist[nx][ny][d] != 0) continue; // 이미 방문했다면 continue
				q.add(new Robot(nx, ny, d));
				dist[nx][ny][d] = dist[x][y][d] + 1;
			}
			
			// 회전
			for(int i = 0; i < 4; i++) {
				if(d == i) continue; // 같은 방향
				/*
				 *  Check rotation. 180 degree (+2), 90 degree (+1)
				 *  180도 회전은 동(0)↔서(1), 남(2)↔북(3)인 경우만 있으므로, 이는 (현재방향 + 다음방향) % 4 == 1 로 확인할 수 있다.
				 *  1이라면 180도 회전이고, 1이 아니면 90도 회전이다.
				 */
				int k = (d + i) % 4 == 1 ? 2 : 1;
				if(dist[x][y][i] != 0) continue; // 이미 방문했다면 continue
				q.add(new Robot(x, y, i));
				dist[x][y][i] = dist[x][y][d] + k;
			}
		}
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		
		st = new StringTokenizer(br.readLine());
		n = Integer.parseInt(st.nextToken()); // 가로의 길이
		m = Integer.parseInt(st.nextToken()); // 세로의 길이
		
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j = 0; j < m; j++) {
				map[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		st = new StringTokenizer(br.readLine());
		s_x = Integer.parseInt(st.nextToken());  // 시작점 행
		s_y = Integer.parseInt(st.nextToken());  // 시작점 열
		s_d = Integer.parseInt(st.nextToken());  // 시작점 방향
		
		st = new StringTokenizer(br.readLine());  
		e_x = Integer.parseInt(st.nextToken());  // 도착점 행
		e_y = Integer.parseInt(st.nextToken());  // 도착점 열
		e_d = Integer.parseInt(st.nextToken());  // 도착점 방향
		
		bfs();
	}
}
