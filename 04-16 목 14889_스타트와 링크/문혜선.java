/*
	���� : main - Combination_split() - getsum()
	Combination_split() : 2������ ������ ��ü ����� �� . �����ο��� ���� ��ü����Ǽ��� nCn-1��ŭ �ʿ��ѵ� ������ ����ϴ� �Լ��� �����Ƿ� �����Ҵ����� add��Ų��
	getsum() : �Ű������� ����ִ� �迭���� 2�����γ��� �ο��� �̸�ǥ. 2��for������ �� ������ ����� �ɷ�ġ�� ���� ���Ѵ�
	
	�˰���
	2������ 2����ϴ°�츦 ����dfs�� Ǯ� ������� ���� �����Ҵ�� al�� add�Ѵ�
	N/2�� �������� ���� ��Ī�� �̷�Ƿ� for������ N/2��ŭ ���Ƽ� �������� �ɷ�ġ ���� ���Ѵ�(getSuk)
	������ �������̸� ���Ѵ�
		
*/
import java.util.ArrayList;
import java.util.Scanner;

public class ��ŸƮ�͸�ũ_��Ǯ�� {
	static int N, s[][], c[][];
	static ArrayList<int[]> al;
	public static void main(String[] args) { 
		Scanner sc = new Scanner(System.in);
		N=sc.nextInt(); sc.nextLine();
		s=new int[N][N];
		for(int i=0; i<N; i++) for(int j=0; j<N; j++) s[i][j]=sc.nextInt();
		sc.close();
		
		al = new ArrayList<>();
		Combination_split(0, 0, new int[N/2], N/2);
		
		int ansMin=Integer.MAX_VALUE;
		for(int i=0; i<N/2; i++) {
			int sub = Math.abs(getSum(al.get(i)) - getSum(al.get(al.size()-i-1)));
			if(ansMin <sub)
				ansMin = sub;
		}
		
		System.out.println(ansMin);
	}
	static int getSum(int[] a) {
		int sum=0;
		for(int i=0; i<N/2-1; i++)
			for(int j=i+1; j<N/2; j++) {
				int p1=a[i], p2=a[j];
				sum += s[p1][p2] + s[p2][p1];
				
			}
		return sum;
	}
	static void Combination_split(int idxN, int idxR, int[] bucket, int k) {//2����ϸ� ���ǰ�����  nCn/2�� �����Ҵ�
		if(k==0) {
			al.add(bucket);
			return;
		}
		for(int i=idxN; i<N; i++) {
			bucket[idxR] = i;//0���ͽ���, 1���ͽ���
			if(idxR==0 ||bucket[idxR-1] < bucket[idxR]) 
				Combination_split(idxN+1, idxR+1, bucket, k-1);
		}
	}
}
