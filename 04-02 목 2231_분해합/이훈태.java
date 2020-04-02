package com.exam.day0217;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

/**
 *  분해합 : https://www.acmicpc.net/problem/2231
 *  
 *  BruteForce
 *  
 *  문제의 조건 그대로 구현한다.
 *  각 자리수를 문자열로 받아 숫자로 변환하여 계산한다음 비교한다.
 */
public class Ex2231 {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int n = Integer.parseInt(br.readLine());
		
		int ans = 0;
		for(int i = n; i > 0; i--) {
			int sum = 0;
			String str = String.valueOf(i);
			
			for(int j = 0; j < str.length(); j++) {
				sum += str.charAt(j) - 48;
			}
			
			if((i + sum) == n) {
				ans = i;
			}
		}
		
		if(ans == 0) {
			System.out.println(0);
		} else {
			System.out.println(ans);
		}
	}
}
