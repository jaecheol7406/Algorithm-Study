import java.util.Scanner;
/* 17406_배열 돌리기 4
 */
public class Main {
	
	static int N, M, K;
	static int[][] arr;
	static int[][] rotations;
	static int minValue = Integer.MAX_VALUE;
	
	public static void main(String[] args) {
		input();
		solve();
		print();
	}
	
	static void input() {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		M = sc.nextInt();
		K = sc.nextInt();
		arr = new int[N + 1][M + 1];
		rotations = new int[K][3];
		for(int i = 1; i <= N; i++) {
			for(int j = 1; j <= M; j++) {
				arr[i][j] = sc.nextInt();
			}
		}
		for(int i = 0; i < K; i++) {
			rotations[i][0] = sc.nextInt();
			rotations[i][1] = sc.nextInt();
			rotations[i][2] = sc.nextInt();
		}
		sc.close();
	}
	
	static void solve() {
		boolean[] check = new boolean[K];
		int[] data = new int[K];
		dfs(data, 0, check, arr);		
	}
	
	/*
	 * K개의 회전 연산 순서의 모든 경우의 수를 dfs로 구한다. rotations 배열에 회전연산 정보가 저장되어있는데, 인덱스가 0 ~ k - 1 까지다.
	 * 0 ~ k - 1의 회전연산 인덱스를 집어 넣기 위해 data, dataIdx를 사용한다.
	 * 0 ~ k - 1 인덱스가 사용됨을 알려주는 check 배열을 사용한다.
	 * 해당 회전연산에 대해 회전을 시킨 arr 배열을 dfs마다 넣어, 최종적으로 모든 회전연산이 수행되었을 때 arr의 값을 구한다. (dfs 종단점)
	 */ 
	static void dfs(int[] data, int dataIdx, boolean[] check, int[][] arr) {
		// 모든 회전 연산이 수행되면 (dfs 종단점) 회전된 배열값 구해서 비교, 저장
		if(dataIdx == data.length) {
			int value = valueOf(arr);
			if(minValue > value)
				minValue = value;
//			// 순열 출력
//			for(int i = 0; i < K; i++)
//				System.out.print(data[i]);
//			System.out.println();
			return;
		}
		
		// 회전 연산의 인덱스의 모든 순서(중복없는 순열)를 dfs로 구함. 해당 인덱스마다 회전을 시켜 dfs에 회전시킨 배열 집어 넣는다.
		for(int i = 0; i < K; i++) {
			if(check[i])
				continue;
			
			int[][] temp = copyOf(arr);
			rotate(temp, i); // 회전
			
			check[i] = true; // 해당 인덱스가 나왔다는 표시
			data[dataIdx++] = i;
			dfs(data.clone(), dataIdx, check.clone(), temp);
			check[i] = false; // 표시 해제
			data[--dataIdx] = 0;
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
	
	// 회전 연산
	static void rotate(int[][] arr, int rotateIdx){
		int[] rotateInfo = rotations[rotateIdx];
		int centerX = rotateInfo[0];
		int centerY = rotateInfo[1];
		int s = rotateInfo[2];
		int stdX = centerX - s;
		int stdY = centerY - s;
		
		int[][] temp = copyOf(arr);
		
		int rotateSize = s * 2 + 1;
		for(int startX = stdX, startY = stdY; startX < centerX; startX++, startY++) {			
			for(int i = 0; i < rotateSize - 1; i++) {
				arr[startX][startY + i + 1] = temp[startX][startY + i];
				arr[startX + 1 + i][startY + rotateSize - 1] = temp[startX + i][startY + rotateSize - 1];
				arr[startX + rotateSize - 1][startY + rotateSize - 1 - (i + 1)] = temp[startX + rotateSize - 1][startY + rotateSize - 1 - i];
				arr[startX + rotateSize - 1 - (i + 1)][startY] = temp[startX + rotateSize - 1 - i][startY];
			}
			
			rotateSize -= 2;
		}
	}
	
	// 배열의 값 구하기
	static int valueOf(int[][] arr) {
		int minSum = Integer.MAX_VALUE;
		for(int i = 1; i < arr.length; i++) {
			int sum = 0;
			for(int j = 1; j < arr[i].length; j++)
				sum += arr[i][j];

			if(minSum > sum)
				minSum = sum;
		}
		return minSum;
	}
	
	static void print() {
		System.out.println(minValue);
	}
}