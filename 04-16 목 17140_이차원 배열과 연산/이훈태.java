package com.exam.day0226;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

/**
 *  이차원 배열과 연산 : https://www.acmicpc.net/problem/17140
 *  
 *  Sol)
 *  먼저 행과 열의 개수를 비교하여 R연산을 할지 C연산을 할지 결정하고
 *  각 숫자를 카운트하여 각 숫자의 개수를 배열에 담는다.
 *  그 다음 문제의 조건에 맞게 정렬하고 배열에 다시 담는다.
 *  이 작업을 (R,C) == K 일 때까지 반복하여 t 를 return
 */
public class Ex17140 {
	
	static int R, C, K;
	static int[][] a = new int[100][100];
	
	static class Number {
		int n;     // 숫자
		int count; // 동작 횟수

		Number(int num, int cnt) {
			n = num;
			count = cnt;
		}
	}
	
	static int solve() {
		int rsize = 3; // 행의 크기 초기화
		int csize = 3; // 열의 크기 초기화
		
		for(int t = 0; t <= 100; t++) {
			// 처음부터 (r,c) 값이 K 인지 check
			if(a[R][C] == K) return t;
			
			// R 연산을 할지 C 연산을 할지 check
			if(rsize >= csize) {
				// R 연산 시작
				for(int i = 0; i < rsize; i++) { // 한 행씩
					List<Number> numList = new ArrayList<Number>();
					
					// 각 숫자를 카운트 하기 위한 변수. 각 수를 카운트 배열의 index 로 하여 카운트
					// index 100까지 사용할 수 있게 101로 선언
					int[] cnt = new int[101]; 
					for(int j = 0; j < csize; j++) { // 행은 고정되어 있고 열을 하나씩 이동하면서 각 숫자를 카운트
						cnt[a[i][j]]++;
					}
					
					// 정렬을 위해서 numList 에 값을 넣는다.
					for(int c = 1; c <= 100; c++) {
						if(cnt[c] > 0) {
							numList.add(new Number(c, cnt[c]));
						}
					}
					
					// 등장횟수의 오름차순 정렬.
					// 람다 expression 으로 간단하게 비교해서 정렬
					numList.sort((lhs, rhs)-> {
						return lhs.count - rhs.count;
					});
					
					int idx = 0;
					for(Number num : numList) {
						if(idx >= 99) break;      // index 100 이 넘지 않기 위해
						a[i][idx++] = num.n;      // 숫자를 먼저 넣고
						a[i][idx++] = num.count;  // 등장횟수 넣고
					}
					
					// R 연산을 수행했기 때문에 열의 개수가 더 커질 수 있기 때문에 
					csize = Math.max(csize, idx);
					for(; idx < 100; idx++) {
						a[i][idx] = 0;
					}
				}
			} else {
				// C 연산 시작
				for(int j = 0; j < csize; j++) {
					List<Number> numList = new ArrayList<Number>();
					int[] cnt = new int[101];
					for(int i = 0; i < rsize; i++) {
						cnt[a[i][j]]++;
					}
					
					for(int c = 1; c <= 100; c++) {
						if(cnt[c] > 0) {
							numList.add(new Number(c, cnt[c]));
						}
					}
					
					numList.sort((lhs, rhs)-> {
						return lhs.count - rhs.count;
					});
					
					int idx = 0;
					for(Number num : numList) {
						if(idx >= 99) break;
						a[idx++][j] = num.n;
						a[idx++][j] = num.count;
					}
					
					rsize = Math.max(rsize, idx);
					for(; idx < 100; idx++) {
						a[idx][j] = 0;
					}
				}
			}
		} // for문 종료. 100번 돌때까지 (r,c) 값이 K 가 되지 못한다면 -1 을 반환
		
		return -1;
	}
	
	public static void main(String[] args) throws IOException {
		 BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		 StringTokenizer st = new StringTokenizer(br.readLine());
		 
		 R = Integer.parseInt(st.nextToken()) - 1;
		 C = Integer.parseInt(st.nextToken()) - 1;
		 K = Integer.parseInt(st.nextToken());
		 
		 for(int i = 0; i < 3; i++) {
			 st = new StringTokenizer(br.readLine());
			 for(int j = 0; j < 3; j++) {
				 a[i][j] = Integer.parseInt(st.nextToken());
			 }
		 }
		 
		 System.out.println(solve());
	}
}
