import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

/*
<�׸� 1>�� ���� ���簢�� ����� ������ �ִ�. 1�� ���� �ִ� ����, 0�� ���� ���� ���� ��Ÿ����. 
ö���� �� ������ ������ ����� ������ ������ ������ �����ϰ�, ������ ��ȣ�� ���̷� �Ѵ�. 
���⼭ ����Ǿ��ٴ� ���� � ���� �¿�, Ȥ�� �Ʒ����� �ٸ� ���� �ִ� ��츦 ���Ѵ�. 
�밢���� ���� �ִ� ���� ����� ���� �ƴϴ�. 
<�׸� 2>�� <�׸� 1>�� �������� ��ȣ�� ���� ���̴�. 
������ �Է��Ͽ� �������� ����ϰ�, �� ������ ���ϴ� ���� ���� ������������ �����Ͽ� ����ϴ� ���α׷��� �ۼ��Ͻÿ�.

�Է�
ù ��° �ٿ��� ������ ũ�� N(���簢���̹Ƿ� ���ο� ������ ũ��� ������ 5��N��25)�� �Էµǰ�, �� ���� N�ٿ��� ���� N���� �ڷ�(0Ȥ�� 1)�� �Էµȴ�.

���
ù ��° �ٿ��� �� �������� ����Ͻÿ�. �׸��� �� ������ ���� ���� ������������ �����Ͽ� �� �ٿ� �ϳ��� ����Ͻÿ�.
*/

public class Main {
	
	public static final int[][] moveDir = new int[][]{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

	static int N;
	static int[][] map;
	static boolean[][] visit;
	
	static List<Integer> estates = new ArrayList<>();
	
	public static void main(String[] args) throws IOException{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		N = Integer.parseInt(br.readLine());
		map = new int[N][N];
		visit = new boolean[N][N];
		
		for(int i = 0; i < N; i++) {
			String input = br.readLine();
			for(int j = 0; j < N; j++) {
				map[i][j] = Integer.parseInt(String.valueOf(input.charAt(j)));
			}
		}
		
		printResult();
	}
	
	static void printResult() {
		bfs();
		Collections.sort(estates);
		System.out.println(estates.size());
		for(int houseNum : estates)
			System.out.println(houseNum);
	}
	
	static void bfs() {
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < N; j++) {
				if(visit[i][j] || map[i][j] == 0)
					continue;
				
				oneEstate(i, j);
			}
		}
	}
	
	static void oneEstate(int i, int j) {
		Queue<int[]> queue = new LinkedList<>();
		int houseNum = 0;
		
		queue.offer(new int[] {i, j});
		visit[i][j] = true;
		houseNum++;
		
		while(!queue.isEmpty()) {
			int[] coord = queue.poll();
			int x = coord[0];
			int y = coord[1];
			
			for(int k = 0; k < 4; k++) {
				int moveX = x + moveDir[k][0];
				int moveY = y + moveDir[k][1];
				
				if(!(0 <= moveX && moveX < N && 0 <= moveY && moveY < N))
					continue;
				
				if(!visit[moveX][moveY] && map[moveX][moveY] == 1) {
					queue.offer(new int[] {moveX, moveY});
					visit[moveX][moveY] = true;
					houseNum++;
				}
			}
		}
		
		estates.add(houseNum);
	}
}
