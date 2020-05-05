package _2020_04;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
/*
 * 2210_숫자판 점프
 * 
 * main -> bfs or dfs
 * 
 * bfs가 좀 더 빠름
 */
public class Main {
	static int[] dx = {0,0,1,-1};
	static int[] dy = {1,-1,0,0};
	
	static int[][] map = new int[5][5];
	static List<String> re = new ArrayList<>();
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		for(int i = 0; i < 5; i++) {
			String[] input = br.readLine().split(" ");
			for(int j = 0; j < 5; j++)
				map[i][j] = Integer.parseInt(input[j]);
		}
		
		for(int i = 0; i < 5; i++) {
			for(int j = 0; j < 5; j++) {
				bfs(i, j); // dfs(i, j, String.valueOf(map[i][j]));
			}
		}
		
		System.out.println(re.size());
	}
	
	static void dfs(int x, int y, String num) {
		if(num.length() == 6) {
			if(!re.contains(num))
				re.add(num);
			return;
		}
		
		for(int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			
			if(!(0 <= nx && nx < 5 && 0 <= ny && ny < 5))
				continue;
			
			dfs(nx, ny, num + String.valueOf(map[nx][ny]));
		}
	}
	
	static void bfs(int sx, int sy) {
		Queue<Info> q = new LinkedList<>();
		q.add(new Info(sx, sy, String.valueOf(map[sx][sy])));
		
		while(!q.isEmpty()) {
			Info n = q.poll();
			if(n.num.length() == 6) {
				if(!re.contains(n.num))
					re.add(n.num);
				
				continue;
			}
			
			for(int i = 0; i < 4; i++) {
				int nx = n.x + dx[i];
				int ny = n.y + dy[i];
				
				if(!(0 <= nx && nx < 5 && 0 <= ny && ny < 5))
					continue;
				
				q.add(new Info(nx, ny, n.num + String.valueOf(map[nx][ny])));
			}
		}
	}
}

class Info {
	int x;
	int y;
	String num;
	
	public Info(int x, int y, String num) {
		super();
		this.x = x;
		this.y = y;
		this.num = num;
	}
}