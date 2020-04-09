/*
 순서 : main - Combinarion_nCm - activate
 
 알고리즘 조합으로 m개의 활성 세포를 고르고
 activate 함수에서 BFS를 이용하여 돌린다
 
 시간초과 나서 결국실패
	
*/
import java.awt.Point;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class 연구소3_2회_내풀이 {
	static int N, M, A[][], cntWall = 0, ansMin = Integer.MAX_VALUE,
			compass[][] = { { -1, 0 }, { 0, -1 }, { 1, 0 }, { 0, 1 } };
	static boolean Mm[][];
	static ArrayList<Point> virus = new ArrayList<>();

	public static void main(String[] args) throws IOException {
//		Scanner sc = new Scanner(System.in);
//		N = sc.nextInt();		M = sc.nextInt();	sc.nextLine();
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		
		
		A = new int[N][N];
		Mm = new boolean[N][N];
		for (int i = 0; i < N; i++) {
			st = new StringTokenizer(br.readLine());
			for (int j = 0; j < N; j++) {
				A[i][j] = Integer.parseInt(st.nextToken());
				if (A[i][j] == 1) {
					Mm[i][j] = true;
					cntWall++;
				} 
				if (A[i][j] == 2)
					virus.add(new Point(i, j));
			}
		}
//		sc.close();

		Combinarion_nCm(0, 0, new Point[M], M);

		System.out.println(ansMin >= N*N ? -1 : ansMin);
	}

	static void Combinarion_nCm(int idxN, int idxM, Point[] bucket, int k) {
		if (k == 0) 
		{
			activate(bucket);
			return;
		}
		for (int i = idxN; i < virus.size(); i++) {
			bucket[idxM] = virus.get(i);
			Combinarion_nCm(idxN + 1, idxM + 1, bucket, k - 1);
		}
	}

	static Queue<Point> Q = new LinkedList<>();
	static Queue<Point> tmpQ = new LinkedList<>();
	static void activate(Point[] vp) {
		int Retsec = 0, contaminated = virus.size() + cntWall;// 빈칸과 비활성화된 바이러스를 찾아야한다
		
		Q.clear(); 
		Q.addAll(Arrays.asList(vp));
		
		boolean[][] m = new boolean[N][N];
		for (int i = 0; i < N; i++) m[i] = Mm[i].clone();
		for (Point p : virus) 
			m[p.x][p.y] = true;
		

		while (contaminated < N * N) {
			tmpQ.clear();
			while (!Q.isEmpty()) {
				int r = Q.peek().x, c = Q.poll().y;

				for (int d = 0; d < 4; d++) {
					int nr = r + compass[d][0], nc = c + compass[d][1];
					if (nr<0 || nc<0 || nr>=N || nc>=N) continue;
					if (A[nr][nc] == 1) continue;
					if (m[nr][nc]) continue;

					m[nr][nc] = true;// 중복큐 입력방지
					tmpQ.offer(new Point(nr, nc));
				}
			}
			contaminated += tmpQ.size();
			Q.addAll(tmpQ);
			Retsec++;
			if (Retsec > N*N) break;
			
		}
		if (ansMin > Retsec) 
			ansMin = Retsec;
	}
}
