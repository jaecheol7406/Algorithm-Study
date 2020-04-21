package com.exam.swtest;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

/**
 *  게리맨더링 2 : https://www.acmicpc.net/problem/17779
 *  
 *  Sol)
 *  BruteForce 방식으로 푼다.
 *  모든 경우의 수를 하는데 경계면을 먼저 그리고 1, 2, 3, 4 경계선을 그어준다.
 *  그 다음 각 모서리 공간을 채우고 사람을 카운트하여 제일 작은 경우를 구한다.
 */
public class Ex17779 {
	static int n;
	
	static int[][] map = new int[20][20];
	static int[][] gu = new int[20][20];
	
	static void fill(int x, int y, int val) {
		if(x < 0 || x > n - 1 || y < 0 || y > n - 1) return;
		if(gu[x][y] != 0) return;
		
		gu[x][y] = val;
		fill(x-1, y, val);
		fill(x+1, y, val);
		fill(x, y-1, val);
		fill(x, y+1, val);
	}
	
	static int solve() {
		int ans = Integer.MAX_VALUE;
		
		for(int x = 0; x <= n - 3; x++) {
			for(int y = 1; y <= n - 2; y++) {
				for(int d1 = 1; x + d1 <= n - 2 && y - d1 >= 0; d1++) {
					for(int d2 = 1; x + d1 + d2 <= n - 1 && y + d2 <= n - 1; d2++) {
						for(int i = 0; i < n; i++) {
							Arrays.fill(gu[i], 0);
						}
						
						for(int i = 0; i <= d1; i++) {
							gu[x + i][y - i] = 5;
							gu[x + d2 + i][y + d2 - i] = 5;
						} // 경계면
						for(int i = 0; i <= d2; i++) {
							gu[x + i][y + i] = 5;
							gu[x + d1 + i][y - d1 + i] = 5;
						} // 경계면
						
						for(int r = x - 1; r >= 0; r--) {
							gu[r][y] = 1;
						}
						for(int c = y+d2 + 1; c < n; c++) {
							gu[x+d2][c] = 2;
						}
						for(int c = y-d1 - 1; c >= 0; c--) {
							gu[x+d1][c] = 3;
						}
						for(int r = x+d1+d2 + 1; r < n; r++) {
							gu[r][y-d1+d2] = 4;
						}
						
						fill(0, 0, 1);
						fill(0, n-1, 2);
						fill(n-1, 0, 3);
						fill(n-1, n-1, 4);
						
						int[] people = new int[6];
						for(int r = 0; r < n; r++) {
							for(int c = 0; c < n; c++) {
								people[gu[r][c]] += map[r][c];
							}
						}
						
						people[5] += people[0];
						
						int min = Integer.MAX_VALUE;
						int max = 0;
						
						for(int i = 1; i <= 5; i++) {
							min = Math.min(min, people[i]);
							max = Math.max(max, people[i]);
						}
						
						ans = Math.min(ans, max - min);
					}
				}
			}
		}
		
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		
		n = Integer.parseInt(br.readLine());
		
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j = 0; j < n; j++) {
				map[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		System.out.println(solve());
	}
}
