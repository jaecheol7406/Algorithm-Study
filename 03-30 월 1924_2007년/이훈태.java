package com.exam.month03;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

/**
 *  2007년 : https://www.acmicpc.net/problem/1924
 *  
 *  Solution
 *  ① 1월 1일과 x월 y일의 일 수 차이를 구한다.
 *  ② 7(일주일)로 나눈 나머지에 해당하는 요일을 출력한다.
 */
public class Ex1924 {
	
	static int[] dayMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	static String[] day = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		int x = Integer.parseInt(st.nextToken());
		int y = Integer.parseInt(st.nextToken());
		
		int totalDay = 0;
		
		for(int i = 0; i < x - 1; i++) {
			totalDay += dayMonth[i];
		}
		
		totalDay += y; // 남은 일 수
		totalDay -= 1; // 출발이 1일 이므로
		
		System.out.println(day[totalDay % 7]);
	}
}
