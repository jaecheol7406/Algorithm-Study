package com.exam.swtest;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

/**
 *  새로운 게임 2 : https://www.acmicpc.net/problem/17837
 *  
 *  function call : main() -> check_go() -> change_dir() -> go() -> add()
 *  
 *  Sol)
 *  1000턴이 지나도 4개의 말이 쌓이지 않으면 게임 종료
 *  말을 번호순으로 이동시키면서 종료 조건을 충족하는지 확인
 *  
 *  체스판에 올라가있는 말의 정보들을 2차원 배열의 각 칸에 Queue를 만들어 저장해서 문제를 푼
 *  
 */
public class Ex17837 {
	
	static class Pair {
		int x;
		int y;
		int dir;
		
		public Pair(int x, int y, int dir) {
			this.x = x;
			this.y = y;
			this.dir = dir;
		}
	}
	
	static int[] dx = {0, 0, 0, -1, 1}; // 1~4 우좌상하
	static int[] dy = {0, 1, -1, 0, 0};
	
	static int n; // 체스판의 크기
	static int l; // 말의 개수
	static int[][] a; // 체스판
	static int ans;
	static int gnum;
	static int qsize;
	static int nx, ny;
	static boolean find;
	
	static ArrayList<Pair> horse; // 말의 정보
	static ArrayList<Integer> tmp;
	static Queue<Integer>[][] q;
	
	@SuppressWarnings("unchecked")
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		n = Integer.parseInt(st.nextToken());
		l = Integer.parseInt(st.nextToken());
		
		// 0 : 흰색 , 1 : 빨간색 , 2 : 파란색
		a = new int[n + 2][n + 2];		
		q = new LinkedList[n + 2][n + 2]; // q[][] 드론의 정보
		for(int i = 0; i <= n + 1; i++) {
			for(int j = 0; j <= n + 1; j++) {
				a[i][j] = 2; // 체스판의 범위를 벗어난 경우(i 또는 j가 0 또는 n+1인 경우) 파란색(2)와 같으므로 초기값은 2
				q[i][j] = new LinkedList<>(); // 2차원 배열 q는 각 칸마다 LinkedList를 생성해주어야 함.
			}
		}
		
		for(int i = 1; i <= n; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j = 1; j <= n; j++) {
				a[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		horse = new ArrayList<>();
		horse.add(new Pair(0, 0, 0));
		
		for(int i = 1; i <= l; i++) {
			st = new StringTokenizer(br.readLine());
			int tx = Integer.parseInt(st.nextToken());
			int ty = Integer.parseInt(st.nextToken());
			int tdir = Integer.parseInt(st.nextToken());
			
			horse.add(new Pair(tx, ty, tdir));
			q[tx][ty].add(i);
		}
		
		ans = -1; // ans의 결과값
		
		for(int turn = 1; turn <= 1000; turn++) {
			for(int now = 1; now <= l; now++) {
				nx = horse.get(now).x;
				ny = horse.get(now).y;
				gnum = check_go(now); // gnum : 말의 이동 방법을 미리 확인
				
				if(gnum == 2) { // gnum 2 : 방향만 바뀌는 경우
					change_dir(now); // change_dir : 현재 말의 방향만 바꿔줌
				} else {
					if(gnum == 1) change_dir(now); // gnum 1 : 방향이 바뀌고 이동하는 경우
					go(now); // go : gnum 이  0 또는 1일 때 말의 이동
					add(); // add : 임시 저장한 tmp를 이동한 말 위에 쌓아올림.
				}
				
				if(q[nx][ny].size() >= 4) { // 종료조건: 말이 4개 쌓이는 경우 턴 종료
					ans = turn;
					break;
				}
			}
			
			if(ans != -1) break; // //종료조건을 통해 결과값 ans가 바뀐 경우 break
		}
		
		System.out.println(ans);
	}
	
	
	// 결과값 gcnt(0: 그냥 이동, 1: 방향 전환 이동, 2: 방향만 전환)
	static int check_go(int now) { 
		int tdir = horse.get(now).dir;
		int gcnt = 0;
		
		if(a[nx + dx[tdir]][ny + dy[tdir]] == 2) {
			gcnt++;
			if(a[nx - dx[tdir]][ny - dy[tdir]] == 2) gcnt++;
		}
		
		return gcnt;
	}
	
	
	// change_dir: 말의 이동방향을 반대로 전환
	static void change_dir(int now) { 
		int tdir = horse.get(now).dir;
		
		if(tdir == 1) horse.get(now).dir = 2;
		else if(tdir == 2) horse.get(now).dir = 1;
		else if(tdir == 3) horse.get(now).dir = 4;
		else horse.get(now).dir = 3;
	}
	
	
	// go : 말의 이동
	static void go(int cur) { 
		tmp = new ArrayList<Integer>(); // tmp : 말 번호 임시 저장 장소
		find = false; // find : 현재 말 위에 쌓여져 있는 말들만 이동하기 위해 확인하는 변수
		qsize = q[nx][ny].size(); // qsize : 현재 좌표에서의 말 개수
		
		for(int s = 0; s < qsize; s++) {
			int a = q[nx][ny].poll();
			if(a == cur) find = true; // 현재 말을 발견한 경우 find = true
			if(find) tmp.add(a); // 현재 말부터 위에 쌓인 말들은 tmp 에 넣어줌.
			else q[nx][ny].add(a); // 그렇지 않은 말들은 그대로 다시 넣어줌
		}
		
		// 말의 좌표 이동
		nx = horse.get(cur).x = horse.get(cur).x + dx[horse.get(cur).dir];
		ny = horse.get(cur).y = horse.get(cur).y + dy[horse.get(cur).dir];
	}
	
	
	// add : 임시 저장한 말 번호들을 2차원 배열 Queue에 추가
	static void add() { 
		if(a[nx][ny] == 0) { // 이동하려는 위치가 0(빈 칸)인 경우
			for(int s = 0; s < tmp.size(); s++) {
				q[nx][ny].add(tmp.get(s));
				horse.get(tmp.get(s)).x = nx;
				horse.get(tmp.get(s)).y = ny;
			}
		} else { // 이동하려는 위치가 1(빨간색)인 경우
			for(int s = tmp.size() - 1; s >= 0; s--) {
				q[nx][ny].add(tmp.get(s));
				horse.get(tmp.get(s)).x = nx;
				horse.get(tmp.get(s)).y = ny;
			}
		}
	}
	
}
