package com.exam.month03;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

/**
 *  X보다 작은 수 : https://www.acmicpc.net/problem/10871
 *  
 *  Solution
 *   - 입력받은 a 배열을 for문을 통해 x 값과 비교하여 작으면 출력한다.
 */
public class Ex10871 {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		int n = Integer.parseInt(st.nextToken());
		int x = Integer.parseInt(st.nextToken());
		
		int[] a = new int[n];
		
		st = new StringTokenizer(br.readLine());
		for(int i = 0; i < n; i++) {
			a[i] = Integer.parseInt(st.nextToken());
		}
		
		for(int i = 0; i < n; i++) {
			if (a[i] < x) {
				System.out.print(a[i] + " ");
			}
		}
	}
}
