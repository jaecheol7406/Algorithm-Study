package com.exam.month03;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

/**
 *  설탕 배달 : https://www.acmicpc.net/problem/2839
 *	
 *	Solution
 *   ① 먼저 가장 최소가될 수 있는 5kg 봉지로 나누어 담을 수 있는지 판단한다.
 *   ② 5로 나눠질때까지 3을 빼준다. 3으로 빼가면서 크기가 <= 0 이면 종료한다.
 */
public class Ex2839 {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int n = Integer.parseInt(br.readLine());
		int ans = 0;
		
		while (true) {
			if (n % 5 == 0) { // 5로 나누어지면 
				System.out.println(n / 5 + ans);
				break;
			} else if (n <= 0) {
				System.out.println("-1");
				break;
			}
			
			n = n - 3; // 3 으로 나눈다
			ans++;     // 봉지 수 1개 추가
		}
	}
}
