package _2020_04;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.Objects;
import java.util.Queue;
/*
 * 16236_아기 상어
 * 
 * solve -> getDist
 * 
 * 주어진 대로 풀었음. Fish 클래스 만들어서 리스트에 저장해놓고, 반복해서 순회해서 x,y,size에 대해 정렬해서 먹을 물고기 정함.
 * 먹을 수 있는 물고기 없으면 끝내고 시간 출력.
 * 있으면 해당 물고기 먹고 해당 거리만큼 t 증가
 * 
 */
public class Main3 {
	static int[] dx = {0,0,1,-1};
	static int[] dy = {1,-1,0,0};
	
	static int N;
	static int[][] map;
	static int t;
	static int sharkX, sharkY;
	static int sharkSize = 2;
	static int eatCount = 0;
	static List<Fish> fishes = new ArrayList<>();
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		N = Integer.parseInt(br.readLine());
		map = new int[N][N];
		for(int i = 0; i < N; i++) {
			String[] input = br.readLine().split(" ");
			for(int j = 0; j < N; j++) {
				map[i][j] = Integer.parseInt(input[j]);
				if(map[i][j] == 0)
					continue;
				
				if(map[i][j] == 9) {
					sharkX = i;
					sharkY = j;
				} else
					fishes.add(new Fish(i, j, map[i][j], 0));
			}
		}
		
		solve();
	}
	
	static void solve() {
		while(true) {
			if(fishes.size() == 0)
				break;
			
			List<Fish> edible = new ArrayList<>();
			for(Fish fish : fishes) {
				if(fish.size >= sharkSize)
					continue;
				
				int dist = getDist(fish);
				if(dist != -1) {
					edible.add(fish);
					fish.dist = dist;
				}
			}
			if(edible.size() == 0)
				break;
			
			Collections.sort(edible);
			Fish eat = edible.get(0);
			map[sharkX][sharkY] = 0;
			sharkX = eat.x;
			sharkY = eat.y;
			map[sharkX][sharkY] = 9;
			if(++eatCount == sharkSize) {
				eatCount = 0;
				sharkSize++;
			}
			
			int idx = fishes.indexOf(eat);
			fishes.remove(idx);
			
			t += eat.dist;
		}
		
		System.out.println(t);
	}
	
	static int getDist(Fish fish) {
		Queue<int[]> q = new LinkedList<int[]>();
		q.add(new int[] {sharkX, sharkY, 0});
		
		boolean[][] visit = new boolean[N][N];
		visit[sharkX][sharkY] = true;
		
		while(!q.isEmpty()) {
			int[] info = q.poll();
			int x = info[0];
			int y = info[1];
			int d = info[2];
			
			if(x == fish.x && y == fish.y)
				return d;
			
			for(int i = 0; i < 4; i++) {
				int nx = x + dx[i];
				int ny = y + dy[i];
				
				if(!(0 <= nx && nx < N && 0 <= ny && ny < N) || visit[nx][ny])
					continue;
				
				int v = map[nx][ny];
				
				if(v > sharkSize)
					continue;
				
				q.add(new int[] {nx,ny,d + 1});
				visit[nx][ny] = true;
			}
		}
		
		return -1;
	}
}

class Fish implements Comparable<Fish> {
	int x;
	int y;
	int size;
	int dist;
	
	public Fish(int x, int y, int size, int dist) {
		super();
		this.x = x;
		this.y = y;
		this.size = size;
		this.dist = dist;
	}

	@Override
	public int compareTo(Fish o) {
		if(dist == o.dist) {
			if(x == o.x) {
				return Integer.compare(y, o.y);
			}
			
			return Integer.compare(x, o.x);
		}
		
		return Integer.compare(dist, o.dist);
	}
	
	@Override
	public boolean equals(Object obj) {
		Fish ano = (Fish)obj;
		if(x == ano.x && y == ano.y && size == ano.size)
			return true;
		return false;
	}
	
	@Override
	public int hashCode() {
		return Objects.hash(x,y,size);
	}
}