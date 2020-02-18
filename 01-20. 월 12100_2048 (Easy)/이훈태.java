package com.exam.day0120;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

/**
 *  2048(Easy) : https://www.acmicpc.net/problem/12100
 */
public class Ex12100 {
	static int[] dx = {0, 0, 1, -1};
	static int[] dy = {1, -1, 0, 0};
	
	static final int LIMIT = 5;
	
	static int[] gen(int k) {
		int[] a = new int[LIMIT];
		
		for(int i = 0; i < LIMIT; i++) {
			a[i] = (k&3);
			k >>= 2;
		}
		
		return a;
	}
	
	// 우선순위가 중요 (위 방향으로 이동하면 위에꺼부터 합하고 아래 방향으로 이동하면 아래꺼부터 합한다.)
	static int check(int[][] a, int[] dirs) {
		int n = a.length;
		int[][] d = new int[n][n];
		boolean[][] merged = new boolean[n][n];
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				d[i][j] = a[i][j];
			}
		}
		
		// 0: down, 1: up, 2: left, 3: right
		for(int dir : dirs) {
			boolean ok = false; // 이동 했는지 체크
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < n; j++) {
					merged[i][j] = false;
				}
			}
			
			while(true) {
				ok = false;
				if(dir == 0) {
					for(int i = n - 2; i >= 0; i--) {
						for(int j = 0; j < n; j++) {
							if(d[i][j] == 0) continue; // 빈 칸이면 건너뜀
							if(d[i + 1][j] == 0) {
								d[i + 1][j] = d[i][j];
								merged[i + 1][j] = merged[i][j];
								d[i][j] = 0;
								ok = true;
							} else if(d[i + 1][j] == d[i][j]) {
								if(merged[i][j] == false && merged[i + 1][j] == false) {
									d[i + 1][j] *= 2;
									merged[i + 1][j] = true;
									d[i][j] = 0;
									ok = true;
								}
							}
						}
					}
				} else if(dir == 1) {
					for(int i = 1; i < n; i++) {
						for(int j = 0; j < n; j++) {
							if(d[i][j] == 0) continue;
							if(d[i - 1][j] == 0) {
								d[i - 1][j] = d[i][j];
								merged[i - 1][j] = merged[i][j];
								d[i][j] = 0;
								ok = true;
							} else if(d[i - 1][j] == d[i][j]) {
								if(merged[i][j] == false && merged[i - 1][j] == false) {
									d[i - 1][j] *= 2;
									merged[i - 1][j] = true;
									d[i][j] = 0;
									ok = true;
								}
							}
						}
					}
				} else if(dir == 2) {
					for(int j = 1; j < n; j++) {
						for(int i = 0; i < n; i++) {
							if(d[i][j] == 0) continue;
							if(d[i][j - 1] == 0) {
								d[i][j - 1] = d[i][j];
								merged[i][j - 1] = merged[i][j];
								d[i][j] = 0;
								ok = true;
							} else if(d[i][j - 1] == d[i][j]) {
								if(merged[i][j] == false && merged[i][j - 1] == false) {
									d[i][j - 1] *= 2;
									merged[i][j - 1] = true;
									d[i][j] = 0;
									ok = true;
								}
							}
						}
					}
				} else if(dir == 3) {
					for(int j = n - 2; j >= 0; j--) {
						for(int i = 0; i < n; i++) {
							if(d[i][j] == 0) continue;
							if(d[i][j + 1] == 0) {
								d[i][j + 1] = d[i][j];
								merged[i][j + 1] = merged[i][j];
								d[i][j] = 0;
								ok = true;
							} else if(d[i][j + 1] == d[i][j]) {
								if(merged[i][j] == false && merged[i][j + 1] == false) {
									d[i][j + 1] *= 2;
									merged[i][j + 1] = true;
									d[i][j] = 0;
									ok = true;
								}
							}
						}
					}
				} // else if(dir == 3) 끝
				
				if(ok == false) break;
			} // while(true) 끝
			
		} // for 끝
		
		int ans = 0;
		
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				if(ans < d[i][j]) {
					ans = d[i][j];
				}
			}
		}
		
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		
		int n = Integer.parseInt(br.readLine());
		int[][] a = new int[n][n];
		
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j = 0; j < n; j++) {
				a[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		int ans = 0;
		for(int k = 0; k < (1<<(LIMIT * 2)); k++) { // 1<<(10) ==> 2^10 까지
			int[] dir = gen(k); // 방향을 만들기
			int cur = check(a, dir); // 그 방향으로 이동시키기
			if(ans < cur) ans = cur; // 최대값인지 아닌지 확인
		}
		
		System.out.println(ans);
	}
}
