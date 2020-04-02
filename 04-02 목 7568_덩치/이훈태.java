package com.exam.month04;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

/**
 *  덩치 : https://www.acmicpc.net/problem/7568
 *  
 *  시뮬레이션(?)
 *  
 *  문제의 조건을 그대로 구현한다.
 *  모든 사람의 키와 몸무게를 비교하여 "더 크다" 가 존재하면 순위를 +1 해준다.
 */
public class Ex7568 {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int n = Integer.parseInt(br.readLine());
		
		int[][] spec = new int[n][2];  // 몸무게, 키
		int[] rank = new int[n];       // 순위
		
		for(int i = 0; i < n; i++) {
			String[] str = br.readLine().split(" ");
			spec[i][0] = Integer.parseInt(str[0]);
			spec[i][1] = Integer.parseInt(str[1]);
			
			rank[i] = 1;
		}
		
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				if(i == j) continue;
				
				if(spec[i][0] > spec[j][0] && spec[i][1] > spec[j][1]) {
					rank[j]++;
				}
			}
		}
		
		for(int a : rank) {
			System.out.print(a + " ");
		}
		
	}
}
