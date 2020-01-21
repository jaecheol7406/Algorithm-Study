package com.exam.day0113;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

/**
 *  한수 : https://www.acmicpc.net/problem/1065
 */
public class Ex1065 {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int n = Integer.parseInt(br.readLine());
		int ans = 0;
		
		if(n < 100) {
			System.out.println(n);
			return;
		}
		
		ans = 99;
		
		for(int i = 100; i <= n; i++) {
			int a = i / 100;
			int b = (i / 10) % 10;
			int c = i % 10;
			
			if(a - b == b - c) ans++;
		}
		
		System.out.println(ans);
	}
}
