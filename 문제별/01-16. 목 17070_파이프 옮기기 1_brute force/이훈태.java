package com.exam.day0116;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

/**
 *  파이프 옮기기 1 : https://www.acmicpc.net/problem/17070
 */
public class Ex17070 {
	
	static int n;
	static int[][] map;
	static int ans;
	
	static boolean check(int x, int y) {
		if(x < 0 || x >= n || y < 0 || y >= n) {
			return false;
		}
		
		return true;
	}
	
	static void go(int x, int y, int d) {
		if(x == n - 1 && y == n - 1) {
			ans++;
			return;
		}
		
		if(d != 2 && check(x, y + 1) && map[x][y + 1] == 0) {
			go(x, y + 1, 0);
		}
		
		if(d != 0 && check(x + 1, y) && map[x + 1][y] == 0) {
			go(x + 1, y, 2);
		}
		
		if(check(x + 1, y + 1) && map[x + 1][y] == 0 && map[x + 1][y + 1] == 0 && map[x][y + 1] == 0) {
			go(x + 1, y + 1, 1);
		}
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		
		n = Integer.parseInt(br.readLine());
		
		map = new int[n][n];
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j = 0; j < n; j++) {
				map[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		ans = 0;
		go(0, 1, 0);
		System.out.println(ans);
	}
}
