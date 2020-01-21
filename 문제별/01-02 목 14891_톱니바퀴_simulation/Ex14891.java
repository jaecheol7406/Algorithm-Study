package com.exam.day0102;

import java.util.Scanner;

/**
 *  톱니바퀴 : https://www.acmicpc.net/problem/14891
 *  문제 유형 : Simulation
 *  시간복잡도 : O(N)
 */
public class Ex14891 {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int n = 4; // 톱니바퀴 수
		char[][] a = new char[4][8];
		
		// 4개의 톱니바퀴 정보를 입력 받는다.
        for (int i = 0; i < n; i++) {
            a[i] = sc.next().toCharArray();
        }
		
        int k = sc.nextInt(); // 회전 횟수
        
        // 회전 횟수만큼 반복
        while(k-- > 0) {
        	int num = sc.nextInt() - 1; // 회전시킨 톱니바퀴의 번호
        	int dir = sc.nextInt();     // 방향(1 : 시계 방향, -1 : 반시계 방향)
        	
        	// 먼저, 톱니가 어떤 방향으로 돌지를 먼저 구하자(톱니바퀴는 동시에 회전해야 하기 때문에)
        	int[] d = new int[n];
        	d[num] = dir;
        	
        	// 왼쪽 톱니 방향 구하기
        	for(int i = num - 1; i >= 0; i--) {
        		if(a[i][2] != a[i + 1][6]) {
        			d[i] = -d[i + 1];
        		} else {
        			// 한 톱니바퀴가 회전하지 않으면 그 톱니바퀴의 왼쪽 톱니바퀴도 회전하지 않는다.
        			break;
        		}
        	}
        	
        	// 오른쪽 톱니 방향 구하기
        	for(int i = num + 1; i < n; i++) {
        		if(a[i - 1][2] != a[i][6]) {
        			d[i] = -d[i - 1];
        		} else {
        			// 한 톱니바퀴가 회전하지 않으면 그 톱니바퀴의 왼쪽 톱니바퀴도 회전하지 않는다.
        			break;
        		}
        	}
        	
        	// 톱니를 돌린다
        	for(int i = 0; i < n; i++) {
        		if(d[i] == 0) continue; // 회전하지 않으므로 패스
        		
        		if(d[i] == 1) { // 시계 방향 회전
        			char temp = a[i][7];
        			for(int j = 7; j >= 1; j--) {
        				a[i][j] = a[i][j - 1];
        			}
        			
        			a[i][0] = temp;
        		} else if(d[i] == -1) { // 반시계 방향 회전
        			char temp = a[i][0];
        			for(int j = 0; j < 7; j++) {
        				a[i][j] = a[i][j + 1];
        			}
        			
        			a[i][7] = temp;
        		}
        	}
        } // 회전 끝.
        
        int ans = 0; // 정답
        
//        for(int i = 0; i < n; i++) {
//        	if(a[i][0] == '1') {
//        		if(i == 0) {
//        			ans += 1;
//        		} else if(i == 1) {
//        			ans += 2;
//        		} else if(i == 2) {
//        			ans += 4;
//        		} else if(i == 3) {
//        			ans += 8;
//        		}
//        	}
//        }
        
        for(int i = 0; i < n; i++) {
        	if(a[i][0] == '1') {
        		ans |= (1 << i);
        	}
        }
        
        System.out.println(ans);
	}
}
