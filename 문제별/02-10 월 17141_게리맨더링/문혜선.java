//14460KB, 104ms, 2485B
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {
	static int N, minDiff=Integer.MAX_VALUE;
	static int[] distPop, connectNum;
	static int[][] adjDistrict;
	static ArrayList<int[]> al = new ArrayList<>();
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		
		N = Integer.parseInt(br.readLine());
		distPop = new int[N];
		connectNum = new int[N];
		adjDistrict = new int[N][N]; 
		st = new StringTokenizer(br.readLine());
		for(int i=0; i<N; i++)
			distPop[i] = Integer.parseInt(st.nextToken());
		for(int i=0; i<N; i++) {
			st = new StringTokenizer(br.readLine());
			connectNum[i] = Integer.parseInt(st.nextToken());
			for(int ii=0; ii<connectNum[i]; ii++)
				adjDistrict[i][Integer.parseInt(st.nextToken()) -1] = 1;
		}//입력끝
		for(int r=1; r< N; r++) 
		{
			int[] bucket = new int[r];
			Combination_nCr(0, 0, bucket, r);
		}
		for(int i=0; i<al.size()/2; i++) 
		{
			if (!isConnected(al.get(i)) || !isConnected(al.get(al.size() -i - 1))) continue;
			int diff = substractPopultion(al.get(i));
			if(minDiff > diff) 
				minDiff =  diff;	
		}
		System.out.println(minDiff==Integer.MAX_VALUE ? -1 : minDiff);
	}

	static void Combination_nCr(int idxN, int idxK, int[] bucket, int k) {
		if (k == 0) {
			al.add(bucket.clone());
			return;
		}
		for (int i = idxN; i < N; i++) {
			if (idxK == 0 || bucket[idxK - 1] < i)
			{
				bucket[idxK] = i;
				Combination_nCr(idxN + 1, idxK + 1, bucket, k - 1);
			}
		}
	}
	
	static boolean isConnected(int[] ary) {
		if(ary.length ==1) return true;
		
		boolean[] visited = new boolean[N]; 
		for(int v : ary)
			visited[v] = true;
		
		Queue<Integer> Q = new LinkedList<Integer>();
		Q.add(ary[0]);
		while (!Q.isEmpty()) {
			int v = Q.poll(); 
			visited[v] = false;

			for (int j = 0; j < adjDistrict[v].length; j++) {
				if (adjDistrict[v][j] == 0) continue;
				if (!visited[j]) continue;
				Q.add(j);
				visited[j] = false;
			}
		}
		for(boolean v : visited)
			if(v) return false;
		return true;
	}
	static int substractPopultion(int[] bucket) {
		int sumB=0, total=0;
		for(int e : distPop) total += e;
		for(int b : bucket) {
			sumB += distPop[b];
		}
		return Math.abs(total - sumB - sumB);
	}
}
