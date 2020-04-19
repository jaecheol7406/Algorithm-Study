package com.exam.swtest;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

/**
 *  주사위 굴리기 : https://www.acmicpc.net/problem/14499
 *  
 *  Sol)
 *  주사위를 이동시킬 때 각 면이 어떻게 변하는지를 파악하여 문제를 해결한다.
 */
public class Ex14499 {
	
	static int[] dx = {0, 0, -1, 1}; // 동 서 북 남
	static int[] dy = {1, -1, 0, 0};
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		
		int x = Integer.parseInt(st.nextToken());
		int y = Integer.parseInt(st.nextToken());
		
		int k = Integer.parseInt(st.nextToken());
		
		int[][] map = new int[n][m];
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j = 0; j < m; j++) {
				map[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		// 행은 남쪽, 북쪽으로 움직일 때 관련있음
		// 1 : 윗면, 2 : 뒷면, 3 : 오른쪽면, 4 : 왼쪽면, 5 : 앞면, 6 : 밑면
		int[] dice = new int[7];
		
		int nx = 0, ny = 0;
		st = new StringTokenizer(br.readLine());
		while(k > 0) {
			int dir = Integer.parseInt(st.nextToken());
			nx = x + dx[dir - 1];
			ny = y + dy[dir - 1];
			
			if(nx >= 0 && nx < n && ny >= 0 && ny < m) {
				int top = dice[1];
				
				if(dir == 1) { // 동쪽 : top 이 오른쪽으로
					dice[1] = dice[4]; // top = 왼쪽
					dice[4] = dice[6];
					dice[6] = dice[3];
					dice[3] = top;
				} else if(dir == 2) {
					dice[1] = dice[3];
					dice[3] = dice[6];
					dice[6] = dice[4];
					dice[4] = top;
				} else if(dir == 3) {
					dice[1] = dice[5];
					dice[5] = dice[6];
					dice[6] = dice[2];
					dice[2] = top;
				} else {
					dice[1] = dice[2];
					dice[2] = dice[6];
					dice[6] = dice[5];
					dice[5] = top;
				}
				
				x = nx;
				y = ny;
				
				if(map[x][y] == 0) {
					map[x][y] = dice[6];
				} else {
					dice[6] = map[x][y];
					map[x][y] = 0;
				}
				
				System.out.println(dice[1]);
			}
			
			k--;
		}
	}
}
