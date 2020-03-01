package com.exam.day0226;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

/**
 *  양념 반 후라이드 반 : https://www.acmicpc.net/problem/16917
 */
public class Ex16917 {
	/*
	 *  양념 치킨 한 마리의 가격 : A원
	 *  후라이드 치킨 한 마리의 가격 : B원
	 *  반반 치킨 한 마리의 가격 : C원
	 *  파티를 위해 양념 치킨 최소 X마리, 후라이드 치킨 최소 Y마리를 구매
	 *  (반반 치킨을 두 마리 구입해 양념 치킨 하나와 후라이드 치킨 하나를 만드는 방법도 가능)
	 *  
	 *  Goal : 상도가 치킨을 구매하는 금액의 최솟값
	 *  
	 *  ★★★ 해결 방법 S ★★★
	 *  먼저, 양 1 + 후 1 가격과 반반 2 (양 1 + 후 1) 가격 비교.
	 *  양 1 + 후 1 가격이 더 싸다면 반반을 구매하지 않고 구매하고자 하는 치킨을 다 사면됨.
	 *  반반 2 가 더 싸다면 반반 2 를 최소 마리 구매 후 남은 치킨을 구매하면 됨.
	 *  예외 케이스에 대해서 계산 필수
	 *  ★★★ 해결 방법 E ★★★
	 */
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		int A = Integer.parseInt(st.nextToken());
		int B = Integer.parseInt(st.nextToken());
		int C = Integer.parseInt(st.nextToken());
		
		int X = Integer.parseInt(st.nextToken());
		int Y = Integer.parseInt(st.nextToken());
		
		long ans = 0;
		
		if(A + B >= 2 * C) {
			if(X >= Y) {
				ans += 2 * C * Y + A * (X - Y);
			} else {
				ans += 2 * C * X + B * (Y - X);
			}
		} else {
			ans += A * X + B * Y;
		}
		
		long tmp = 0;
		if(X >= Y) {
			tmp += 2 * C * X;
		} else {
			tmp += 2 * C * Y;
		}
		
		ans = Math.min(ans, tmp);
		
		System.out.println(ans);
	}
}
