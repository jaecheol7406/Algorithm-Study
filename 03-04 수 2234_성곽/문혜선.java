/* 1, 2������
 * �Է�(15-��)���� �迭���� �޾� �̵��ؾ� �� ���Ⱚ �Է� 
 * 2����int���迭��  DFS�� �׷캰�� ��ȣ�ű��, �׷캰�� ���̰���ؼ� HashMap�� ���
 * ������ �ε����� ������ �������� 2���� �迭����
 * setDir(): �Է°��� ����ū ���������� �������� ���⼳���ϴ� �ε��� return
 * 2������ �̻� �������� ��찡 �����Ƿ� A[i][j]==0����  8, 4, 2,1�� ����(-)
 * 
 * 
 * 3������
 * ���̼������ memo��ȣ ������������ ������ �� ���� �ε���(x=0, y=1)���� Ž��
 * �����迭�� ã�°��� ������ ���� ū ���� �ǹǷ� flag�� return
 * -> tk����, ä�� Ʋ�Ƚ��ϴ�
 */

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Scanner;

public class ����_��Ǯ�� {
	static int ans1=0, ans2=0, ans3=0, area;
	static int[][] A, M, compass= { {0,-1}, {-1,0}, {0,1}, {1,0}};//���ϵ���
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
		//���̼������ memo��ȣ ������������ ����
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
