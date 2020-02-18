import java.util.Scanner;

public class 배열돌리기4 {
	static int N, M, K;
	static int[][] A, info;
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt(); M=sc.nextInt(); K=sc.nextInt(); sc.nextLine();
		A = new int[N+1][M+1];//(1,1)
		for(int i=1; i<=N; i++)
			for(int j=1; j<=M; j++)
				A[i][j] = sc.nextInt();
		info = new int[K][3];
		for(int i=0; i<K; i++) {//(,,)연산 순서대로X, 순열문제
			info[i][0]=sc.nextInt(); info[i][1]=sc.nextInt(); info[i][2]=sc.nextInt(); sc.nextLine();
		}//			r						 s						  c
		sc.close();
		
		int[][] B = A;
		System.out.println( Permutation_nPn(0, B, K) );
	}
	static int Permutation_nPn(int idxN, int[][] B, int r) {//nPn = n!
		
		if(r==0) 
			return getMinimun(B);
		
		int min=Integer.MAX_VALUE;
		for(int i=idxN; i<info.length; i++)
		{
			int[][] rotated = rotate(B, info[i]);
			int sum = Permutation_nPn(idxN+1, rotated, r-1);
			if(min > sum)
				min=sum;
		}
		return min;
	}
	static int[][] rotate(int[][] I, int[] rcs) {
		if(I == null) return null;;
		
		int[][] R = new int[I.length][];
		for(int r=0; r<I.length; r++)
			R[r] = I[r].clone();
		
		int r=rcs[0], c=rcs[1], s=rcs[2];
		
		for(int depth=0; depth <s; depth++) 
		{= 
			int ur = r-s + depth, uc = c-s + depth;
			int lr = r+s - depth, lc = c+s - depth;
			
			int u_value= R[ur][uc];
			
			for(int i=ur; i<lr; i++)
				R[i][uc] = R[i + 1][uc];// ↑
//			System.out.println(Arrays.deepToString(R));
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      x			for(int i=uc; i<lc; i++)
				R[lr][i] = R[lr][i+1];	// ←
//			System.out.println(Arrays.deepToString(R));
			for(int i=lr; i >ur; i--)
				R[i][lc] = R[i - 1][lc];// ↓
//			System.out.println(Arrays.deepToString(R));
			for(int i=lc; i<uc -1; i++)
				R[ur][i + 1] = R[ur][i];// →
			R[ur][uc+1] = u_value;
		}
		
		return R;
	}
	static int getMinimun(int[][] B) {
		int min = Integer.MAX_VALUE;
		for(int i=1; i<=N; i++) {
			int sum=0;
			for(int j=1; j<=M; j++) 
				sum += B[i][j];
			min = (min > sum) ? sum : min;
		}
		return min;
	}
}
