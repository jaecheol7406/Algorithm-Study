package com.exam.month03;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

/**
 *  체스판 다시 칠하기 : https://www.acmicpc.net/problem/1018
 *  
 *  Solution
 *   ① 먼저 8 * 8 체스판을 만든다. (흰색으로 시작하는 체스판, 검은색으로 시작하는 체스판)
 *   ② 그 다음, 입력 받은 M*N 보드를 8*8 체스판을 놓고 움직이면서 칠해야 하는 정사각형 개수의 최소값을 찾는다.
 */
public class Ex1018 {
	
	 static String[] Wresult = {"WBWBWBWB","BWBWBWBW","WBWBWBWB","BWBWBWBW","WBWBWBWB","BWBWBWBW","WBWBWBWB","BWBWBWBW"};
	 static String[] Bresult = {"BWBWBWBW","WBWBWBWB","BWBWBWBW","WBWBWBWB","BWBWBWBW","WBWBWBWB","BWBWBWBW","WBWBWBWB"};
	
	 static int checkW(String[] chess, int a, int b) {
		 int result = 0;
		 
		 for(int i = a; i < a + 8; i++) {
			 for(int j = b; j < b + 8; j++) {
				 if(chess[i].charAt(j) == Wresult[i - a].charAt(j - b)) {
					 result++;
				 }
			 }
		 }
		 
		 return result;
	 }
	 
	 static int checkB(String[] chess, int a, int b) {
		 int result = 0;
		 
		 for(int i = a; i < a + 8; i++) {
			 for(int j = b; j < b + 8; j++) {
				 if(chess[i].charAt(j) == Bresult[i - a].charAt(j - b)) {
					 result++;
				 }
			 }
		 }
		 
		 return result;
	 }
	 
	 
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		String[] str = br.readLine().split(" ");
		int n = Integer.parseInt(str[0]); // 행
		int m = Integer.parseInt(str[1]); // 열
		
		String[] chess = new String[n];
		int result = 2500;
		
		for(int i = 0; i < n; i++) {
			chess[i] = br.readLine();
		}
		
		for(int i = 0; i < n - 7; i++) {
			for(int j = 0; j < m - 7; j++) {
				result = Math.min(result, Math.min(checkW(chess, i, j), checkB(chess, i, j)));
			}
		}
		
		System.out.println(result);
	}
}
