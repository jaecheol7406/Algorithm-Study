/*
	순서 : main - Combination_split() - getsum()
	Combination_split() : 2팀으로 나누는 전체 경우의 수 . 참가인원에 따라 전체경우의수가 nCn-1만큼 필요한데 조합을 계산하는 함수가 없으므로 동적할당으로 add시킨다
	getsum() : 매개변수로 들어있는 배열값이 2팀으로나뉜 인원의 이름표. 2중for문으로 두 조합의 경우의 능력치의 합을 구한다
	
	알고리즘
	2팀으로 2등분하는경우를 조합dfs로 풀어서 모든경우의 수를 동적할당된 al에 add한다
	N/2를 기준으로 팀이 대칭을 이루므로 for문으로 N/2만큼 돌아서 팀내부의 능력치 합을 더한다(getSuk)
	각팀의 절댓값차이를 구한다
		
*/
import java.util.ArrayList;
import java.util.Scanner;

public class 스타트와링크_내풀이 {
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
	static void Combination_split(int idxN, int idxR, int[] bucket, int k) {//2등분하면 행의개수가  nCn/2로 동적할당
		if(k==0) {
			al.add(bucket);
			return;
		}
		for(int i=idxN; i<N; i++) {
			bucket[idxR] = i;//0부터시작, 1부터시작
			if(idxR==0 ||bucket[idxR-1] < bucket[idxR]) 
				Combination_split(idxN+1, idxR+1, bucket, k-1);
		}
	}
}
