import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;

/*����
N��Mũ���� �迭�� ǥ���Ǵ� �̷ΰ� �ִ�.

1	0	1	1	1	1
1	0	1	0	1	0
1	0	1	0	1	1
1	1	1	0	1	1
�̷ο��� 1�� �̵��� �� �ִ� ĭ�� ��Ÿ����, 0�� �̵��� �� ���� ĭ�� ��Ÿ����. �̷��� �̷ΰ� �־����� ��, (1, 1)���� ����Ͽ� (N, M)�� ��ġ�� �̵��� �� ������ �ϴ� �ּ��� ĭ ���� ���ϴ� ���α׷��� �ۼ��Ͻÿ�. �� ĭ���� �ٸ� ĭ���� �̵��� ��, ���� ������ ĭ���θ� �̵��� �� �ִ�.

���� �������� 15ĭ�� ������ (N, M)�� ��ġ�� �̵��� �� �ִ�. ĭ�� �� ������ ���� ��ġ�� ���� ��ġ�� �����Ѵ�.

�Է�
ù° �ٿ� �� ���� N, M(2 �� N, M �� 100)�� �־�����. ���� N���� �ٿ��� M���� ������ �̷ΰ� �־�����. ������ ������ �پ �Է����� �־�����.

���
ù° �ٿ� ������ �ϴ� �ּ��� ĭ ���� ����Ѵ�. �׻� ������ġ�� �̵��� �� �ִ� ��츸 �Է����� �־�����.

���� �Է� 1 
4 6
101111
101010
101011
111011

���� ��� 1 
15

���� �Է� 2 
4 6
110110
110110
111111
111101

���� ��� 2 
9

���� �Է� 3 
2 25
1011101110111011101110111
1110111011101110111011101

���� ��� 3 
38

���� �Է� 4 
7 7
1011111
1110001
1000001
1000001
1000001
1000001
1111111

���� ��� 4 
13
*/

public class Main4 {
	public static final int[][] moveDir = new int[][]{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

	static int N, M;
	static int[][] miro;
	static boolean[][] visit;
	
	public static void main(String[] args) throws IOException{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		String[] input = br.readLine().split(" ");
		N = Integer.parseInt(input[0]);
		M = Integer.parseInt(input[1]);
		miro = new int[N + 1][M + 1];
		visit = new boolean[N + 1][M + 1];
		for(int i = 1; i <= N; i++) {
			String s = br.readLine();
			for(int j = 1; j <= M; j++)
				miro[i][j] = Integer.parseInt(String.valueOf(s.charAt(j - 1)));
		}
		System.out.println(bfs());
	}
	
	static int bfs() {
		Queue<int[]> q = new LinkedList<>();
		
		q.add(new int[] {1, 1, 1});
		while(!q.isEmpty()) {
			int[] pos = q.poll();
			int x = pos[0];
			int y = pos[1];
			
			if(x == N && y == M)
				return pos[2];
			
			visit[x][y] = true;
			
			for(int i = 0; i < 4; i++) {
				int movex = x + moveDir[i][0];
				int movey = y + moveDir[i][1];
				
				if(!(1 <= movex && movex <= N && 1 <= movey && movey <= M))
					continue;
				
				if(visit[movex][movey] || miro[movex][movey] == 0)
					continue;
				
				visit[movex][movey] = true;
				
				q.add(new int[] {movex, movey, pos[2] + 1});
			}
		}
		return -1;
	}
}
