/*
	 순서 : main - axis():C연산인 경우 y=x축 대칭
	 알고리즘
	 C연산인 경우에는 y=x축대칭을 한다
	 A[i]씩 오름차순 정렬을 한 다음에 0을 제외하고 개수를 세서 al벡터에 [숫자,횟수]형태로 저장
	 횟수[1]를 기준으로 오름차순 정렬
	 sorted(int[])에 고정배열로 담은 다음 rltAry로 배열을 추가시켜준다 (A[i]에 바로 추가가 안되기 때문)
	 행과 열 최대값을 갱신시켜준다
	 flag변수로 C연산을 한 경우에는 다시 축대칭을 시켜 원위치로 만든다
*/
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;

public class 이차월배열과연산_내풀이 {

	public static void main(String[] args) {
// 정렬된 결과를 배열에 넣을 때는, 수와 등장 횟수를 모두 넣으며, 순서는 수가 먼저이다.
//		행 또는 열의 크기가 100을 넘어가는 경우에는 처음 100개를 제외한 나머지는 버린다.
		Scanner sc = new Scanner(System.in);
		int r=sc.nextInt(), c=sc.nextInt(), k=sc.nextInt();
		int[][] A = new int[3][3];
		for(int i=0; i<3; i++) for(int j=0; j<3; j++) A[i][j]=sc.nextInt();
		sc.close();
		
		int minSec=0, sizeR=3, sizeC=3;//
		while(A[r-1][c-1] != k) {
			A = (sizeR>=sizeC) ? A : axis(A, sizeR, sizeC);//C연산의 경우 정렬은 r연산과 동일하므로 위치만 바꾼다음에 정렬한다
			boolean flag = (sizeR>=sizeC) ? false : true; //정렬 후 c연산은 다시 y=x축대칭해야함
			int[] sorted;//배열한 결과값
			
			ArrayList<int[]> rltAry = new ArrayList<>();
			for(int i=0; i<A.length; i++)
			{
				Arrays.sort(A[i]);//오름차순으로 먼저 정렬
				int g[]= (A[i][0]==0) ? new int[A[i].length-1] : new int[A[i].length];
				int num, cnt=1;
				ArrayList<int[]> al = new ArrayList<>();
				for(int j=1; j<A[i].length; j++) {//인덱스 시작을 1부터
					if(A[i][j] == 0) continue;
					if(A[i][j-1] == A[i][j]) 
						cnt++;//A[i][j]까지 같은숫자 개수
					else {
						num = A[i][j-1];
						al.add(new int[]{num,cnt});
						cnt=1;
					}
					
					if(j==A[i].length-1) {//마지막 배열은 별도로 추가해줘야한다
						num = A[i][j];
						al.add(new int[]{num,cnt});
					}
				}
				
				al.sort(new Comparator<int[]>(){//[숫자,횟수] 중에서 횟수[1]를 기준으로 오름차순 정렬
					@Override
					public int compare(int[] o1, int[] o2) {
						int v1=o1[1], v2=o2[1];//[숫자,횟수] 중에서 횟수[1]를 기준으로한다
						
						if(v1==v2) return 0;
						else if(v1 > v2) return 1;
						else return -1;
					}
				});
				
				sorted = new int[2* al.size()];
				int idxS=0;
				for(int[] a : al) {
					sorted[idxS++] = a[0];
					sorted[idxS++] = a[1];
				}
				
//				System.out.println(Arrays.toString(sorted));
//				A[i] = sorted.clone(); 크기때문에 안됨
				rltAry.add(sorted);

				if(flag)
					sizeR = (sizeR < sorted.length) ? sorted.length : sizeR;
				else
					sizeC = (sizeC < sorted.length) ? sorted.length : sizeC;//R연산 ->열의 개수증가
					
			}
			
			A = new int[sizeR][sizeC];
			for(int i=0; i<A.length; i++) {
				A[i] = rltAry.get(i).clone();//ArrayList<int> -> int[]q배열로 clone으로 대입가능
//				System.out.println(Arrays.toString(A[i]));
			}
			
			
			if(flag)
				A = axis(A,sizeR, sizeC);
			minSec++;
		}
		System.out.println(minSec);
	}
	static int[][] axis(int[][] P, int r, int c){//y=x축대칭, 직사각형 배열인 경우
//		int[][] R = new int[c][r]; //행열이 직사각형인경우
		
		for(int i=0; i<P.length; i++)
			for(int j=i; j<P[0].length; j++) //in[0].length : 열개수
			{
				int t = P[i][j];
				P[i][j] = P[j][i];
				P[j][i] = t;
			}
		return P;
	}

}
//https://www.acmicpc.net/problem/17140