/* 1, 2번문제
 * 입력(15-값)으로 배열값을 받아 이동해야 할 방향값 입력 
 * 2차원int형배열로  DFS로 그룹별로 번호매기기, 그룹별로 넓이계산해서 HashMap에 등록
 * 방향의 인덱스는 지수를 기준으로 2차원 배열생성
 * setDir(): 입력값중 가장큰 이진수값을 기준으로 방향설정하는 인덱스 return
 * 2갈래길 이상 나눠지는 경우가 있으므로 A[i][j]==0까지  8, 4, 2,1를 누적(-)
 * 
 * 
 * 3번문제
 * 넓이순서대로 memo번호 내림차순으로 정렬한 뒤 작은 인덱스(x=0, y=1)부터 탐색
 * 인접배열에 찾는값이 있으면 가장 큰 값이 되므로 flag로 return
 * -> tk맞음, 채점 틀렸습니다
 */

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Scanner;

public class 성곽_내풀이 {
	static int ans1=0, ans2=0, ans3=0, area;
	static int[][] A, M, compass= { {0,-1}, {-1,0}, {0,1}, {1,0}};//서북동남
	static HashMap<Integer, Integer> hm = new HashMap<>();
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n=sc.nextInt(); int m=sc.nextInt(); sc.nextLine();
		A = new int[m][n];
		for(int i=0; i<m; i++) for(int j=0; j<n; j++) A[i][j] = 15 - sc.nextInt();
		sc.close();
		M = new int[m][n];
		int num=0;
		for(int i=0; i<m; i++) for(int j=0; j<n; j++) {
			if(M[i][j] != 0) continue;
			ans1++;
			area=0;
			dfs(i, j, ++num);
		}
		//넓이순서대로 memo번호 내림차순으로 정렬
		ArrayList<Integer> alV = new ArrayList<>();
		alV.addAll( hm.keySet() );
		Collections.sort(alV, new Comparator<Object>() {
			@Override
			public int compare(Object o1, Object o2) {
				Object v1=hm.get(o1), v2=hm.get(o2);
				return ((Comparable) v2).compareTo(v1);
			}
		});
		boolean flag=false;
		for(int x=0; x<ans1-1; x++) for(int y=1; y<ans1; y++){
		for(int i=0; i<m; i++) for(int j=0; j<n; j++) {
			if(flag) break;
			if(M[i][j] != alV.get(x)) continue;
			for(int d=0; d<4; d++) {
				int ni=i+compass[d][0], nj=j+compass[d][1];
				if(ni<0 || nj<0 || ni>=m || nj>=n) continue;
				if(alV.get(y) != M[ni][nj]) continue;
				{
					ans3=hm.get(alV.get(x)) + hm.get(alV.get(y));
					flag=true;
					break;
				}
			}
			if(flag) break;
		}
		}
		System.out.println(ans1);
		System.out.println(ans2);
		System.out.println(ans3);
	}
	static void dfs(int i, int j, int num) {
		M[i][j] = num;
		area++;
		
		while(A[i][j] > 0)
		{
			int d = setDir(A[i][j]);
			int ni = i + compass[d][0], nj = j + compass[d][1];

			if (M[ni][nj] == 0) 
				dfs(ni, nj,num);

			A[i][j] -= (int) Math.pow(2, d);
		}
		
		ans2 = Math.max(ans2, area);
		hm.put(num, area);
		
	}
	static int setDir(int num) {
		if(num >= 8) return 3;
		if(num >= 4) return 2;
		if(num >= 2) return 1;
		else return 0;
	}

}
