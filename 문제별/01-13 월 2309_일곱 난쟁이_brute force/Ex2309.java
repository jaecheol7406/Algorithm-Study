package com.exam.day0113;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

/**
 *  일곱 난쟁이 : https://www.acmicpc.net/problem/2309
 *  문제 유형 : bruteforce
 */
public class Ex2309 {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int n = 9;
		int[] a = new int[n];
		int sum = 0;
		boolean check = false;
		
		for(int i = 0; i < n; i++) {
			a[i] = Integer.parseInt(br.readLine());
			sum += a[i];
		}
		
		Arrays.sort(a);
		
		for(int i = 0; i < n; i++) {
			if(check) break;
			
			for(int j = i + 1; j < n; j++) {
				if(sum - a[i] - a[j] == 100) {
					a[i] = 0;
					a[j] = 0;
					check = true;
					break;
				}
			}
		}
		
		for(int i = 0; i < n; i++) {
			if(a[i] != 0) {
				System.out.println(a[i]);
			}
		}
		
	}
}
