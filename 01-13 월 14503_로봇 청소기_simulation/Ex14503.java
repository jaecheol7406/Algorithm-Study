package com.exam.day0113;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

// 로봇 청소기 : https://www.acmicpc.net/problem/14503
// Solution : http://codeplus.codes/bd02caedbe774a3f9fa0be38c38f3e33
public class Ex14503 {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		
		st = new StringTokenizer(br.readLine());
		int n = Integer.parseInt(st.nextToken()); // 가로
		int m = Integer.parseInt(st.nextToken()); // 세로
		int[][] map = new int[n][m];
		
		st = new StringTokenizer(br.readLine());
		int r = Integer.parseInt(st.nextToken());
		int c = Integer.parseInt(st.nextToken());
		int d = Integer.parseInt(st.nextToken()); // 0 : 북쪽 , 1 : 동쪽 , 2 : 남쪽 , 3 : 서쪽
		
		int[] dx = {-1, 0, 1, 0}; // 위쪽, 오른쪽, 아래쪽, 왼쪽
		int[] dy = {0, -1, 0, 1};
		
		map = new int[n][m];
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j = 0; j < m; j++) {
				map[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		int cnt = 0;
		
		// map[r][c] == 0 (청소하지 않은 공간)
		// map[r][c] == 1 (벽)
		// map[r][c] == 2 (청소한 공간)
		while(true) {
			if(map[r][c] == 0) {
				// 1. 현재 위치를 청소한다.
				map[r][c] = 2;
			}
			
			// 2-3, 2-4  네 방향 모두 청소가 이미 되어있거나 벽인 경우
			if(map[r + 1][c] != 0 && map[r - 1][c] != 0 && map[r][c - 1] != 0 && map[r][c + 1] != 0) {
				if(map[r - dx[d]][c - dy[d]] == 1) {
					// 2-4  뒤쪽 방향이 벽이라 후진도 할 수 없는 경우에는 작동을 멈춘다.
					break;
				} else {
					// 2-3  바라보는 방향을 유지한 채로 한 칸 후진을 하고 2번으로 돌아간다.
					r -= dx[d];
					c -= dy[d];
				}
			} else {
				// 2-1  왼쪽 방향에 아직 청소하지 않은 공간이 존재한다면, 그 방향으로 회전한 다음
				// 2-2  왼쪽 방향에 청소할 공간이 없다면, 그 방향으로 회전하고 2번으로 돌아간다.
				d = (d + 1) % 4;
				if(map[r + dx[d]][c + dy[d]] == 0) {
					// 2-1  한 칸을 전진하고 1번부터 진행한다.
					r += dx[d];
					c += dy[d];
				}
			}
		} // while 끝.
		
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				if(map[i][j] == 2) {
					cnt += 1;
				}
			}
		}
		
		System.out.println(cnt);
	}
}
