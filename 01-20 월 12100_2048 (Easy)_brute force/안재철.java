import java.util.Scanner;
/* 12100_2048 (Easy)
 */
public class Main {
	
	static int N;
	static int[][] map;
	static int[][] isCombined;
	static int maxValue = -1;
	
	public static void main(String[] args){
		input();
		solve();
		print();
	}
	
	static void input() {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		map = new int[N][N];
		isCombined = new int[N][N];
		
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < N; j++)
				map[i][j] = sc.nextInt();
		}
		
		sc.close();
	}
	
	static void solve() {
		dfs(map, 0);
	}
	
	static void dfs(int[][] map, int moveCount) {
		
		// 5번 이동 끝나면 최대값 계산
		if(moveCount == 5) {
			int maxArrValue = -1;
			
			for(int i = 0; i < N; i++)
				for(int j = 0; j < N; j++)
					maxArrValue = Integer.max(maxArrValue, map[i][j]);
			
			maxValue = Integer.max(maxValue, maxArrValue);
			return;
		}
		
		int[][] temp = copyOf(map);
		
		// 90도 4번 회전하면서 블록 이동, 각각 경우에 대해 dfs
		for(int k = 0; k < 4; k++) {
			rotation(temp);
			int[][] tempShift = copyOf(temp);
			
			for(int j = 0; j < N; j++) {
				int prev = 0;
				int newIdx = 0;
				
				for(int i = 0; i < N; i++) {
					int cur = temp[i][j];
					if(cur == 0)
						continue;
					
					if(prev == 0) {
						prev = cur;
						continue;
					}
					
					if(prev == cur) {
						temp[newIdx++][j] = prev * 2;
						prev = 0;
					} else {
						temp[newIdx++][j] = prev;
						prev = cur;
					}
					
				}
				
				if(prev != 0)
					temp[newIdx++][j] = prev;
				
				for(int i = newIdx; i < N; i++)
					temp[i][j] = 0;
			}
			
			dfs(temp, moveCount + 1);
			temp = copyOf(tempShift);
		}
		
		
	}
	
	// 2차원배열 복사
	static int[][] copyOf(int[][] source){
		int[][] copy = new int[source.length][source[0].length];
		
		for(int i = 0; i < source.length; i++) {
			copy[i] = source[i].clone();
		}
		
		return copy;
	}
	
	// 오른쪽으로 90도 회전
	static void rotation(int[][] arr) {
		int N = arr.length;
		for(int i = 0 ; i < N/2 ; i++){
            for(int j = i ; j < N - i - 1 ; j++){

                int k = arr[i][j];
                arr[i][j] = arr[N - 1 - j][i];
                arr[N - 1 - j][i] = arr[N - 1 - i][N - 1 - j];
                arr[N - 1 - i][N - 1 - j] = arr[j][N - 1 - i];
                arr[j][N - 1 - i] = k;
            }
        }
	}
	
	static void print() {
		System.out.println(maxValue);
	}
}