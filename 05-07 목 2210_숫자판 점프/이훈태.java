package com.exam.month05;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashSet;
import java.util.StringTokenizer;

/**
 *  숫자판 점프 : https://www.acmicpc.net/problem/2210
 *  
 *  시간복잡도 : O(25 * 4^5)
 *  
 *  go(x, y, num, len) : 현재 (x,y)에 있고 지금까지 만든 수의 길이는 len, 만든 수는 num
 */
public class Ex2210 {
	static int[] dx = {0, -1, 0, 1};
	static int[] dy = {1, 0, -1, 0};
	
	static int n = 5;
	static int[][] a = new int[5][5];
	static HashSet<Integer> ans = new HashSet<>();
	
	
	// 현재 (x,y)에 있고 지금까지 만든 수의 길이는 len, 만든 수는 num
	static void go(int x, int y, int num, int len) {
		if (len == 6) {
			ans.add(num);
			return;
		}
		
		for (int k = 0; k < 4; k++) {
			int nx = x + dx[k];
			int ny = y + dy[k];
			
			if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
				go(nx, ny, num * 10 + a[nx][ny], len + 1);
			}
		}
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		
		for (int i = 0; i < n; i++) {
			st = new StringTokenizer(br.readLine());
			for (int j = 0; j < n; j++) {
				a[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				go(i, j, a[i][j], 1);
			}
		}
		
		System.out.println(ans.size());
	}
}