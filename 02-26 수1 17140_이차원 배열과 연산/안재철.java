import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Scanner;
/*
 * 17140_이차원 배열과 연산
 * 
 * 1. R연산
 * 		(1) 각 행마다 행 개수만큼 HashMap 배열을 따로 만든다. HashMap에는 key : 숫자, value : 숫자의 개수 저장되어있음.
 * 		(2) 해쉬맵 중 가장 크기가 큰 size * 2 만큼 new int[] 해줌. 배열의 크기는 해쉬맵의 size * 2(key, value 2개) 만큼 나옴.
 * 		(3) 이후 각 행의 HashMap을 sort메소드로 value에 대해 오름차순, key에 대해 오름차순으로 정렬 후 key, value 값들을 각 행에 갱신
 * 
 * 2. C연산
 * 		(1) 배열 왼쪽으로 회전
 * 		(2) 위의 R연산 진행
 * 		(3) 다시 오른쪽으로 회전해서 원위치
 */
public class Main2 {
	static int r, c, k;
	static int[][] arr;
	static int time;

	public static void main(String[] args) {
		input();
		solve();
		System.out.println(time);
	}

	static void input() {
		Scanner sc = new Scanner(System.in);
		r = sc.nextInt();
		c = sc.nextInt();
		k = sc.nextInt();
		arr = new int[3][3];
		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++)
				arr[i][j] = sc.nextInt();
		sc.close();
	}

	static void solve() {
		while(true) {
			if(r - 1 < arr.length && c - 1 < arr[0].length && arr[r - 1][c - 1] == k)
				break;
			
			time++;
			if(time > 100) {
				time = -1;
				return;
			}
				
				
			if(arr.length >= arr[0].length)
				R();
			else
				C();

		}
	}

	static void R() {
		HashMap<Integer, Integer>[] map = new HashMap[arr.length];
		int max = -1;
		for(int i = 0; i < arr.length; i++) {
			map[i] = new HashMap<>();
			for(int j = 0; j < arr[i].length; j++) {
				int n = arr[i][j];
				if(n == 0)
					continue;

				map[i].put(n, map[i].getOrDefault(n, 0) + 1);
			}
			max = Integer.max(max, map[i].size());
		}

		if(max > 50)
			max = 50;
		
		for(int i = 0; i < arr.length; i++) {
			arr[i] = new int[max * 2];

			sort(arr[i], map[i]);
		}
	}

	static void sort(int[] row, HashMap<Integer, Integer> map) {
		List<Map.Entry<Integer, Integer>> list = new LinkedList<>(map.entrySet());

		Collections.sort(list, new Comparator<Map.Entry<Integer, Integer>>() {
			@Override
			public int compare(Entry<Integer, Integer> o1, Entry<Integer, Integer> o2) {
				if(o1.getValue() < o2.getValue())
					return -1;
				else if (o2.getValue() < o1.getValue())
					return 1;

				if(o1.getKey() < o2.getKey())
					return -1;
				else 
					return 1;
			}
		});

		int idx = 0;
		for(Map.Entry<Integer, Integer> entry : list) {
			if(idx >= 100)
				break;

			row[idx++] = entry.getKey();
			row[idx++] = entry.getValue();
		}
	}

	static void C() {
		arr = rotationLeft(arr);
		R();
		arr = rotationRight(arr);
	}

	// 직사각형 2차원 배열 우로 90도 회전
	static int[][] rotationRight(int[][] arr) {
		int n = arr.length;
		int m = arr[0].length;
		int[][] temp = new int[m][n];
		for(int i = 0; i < m; i++) {
			for(int j = 0; j < n; j++) {
				temp[i][j] = arr[n - 1 - j][i];
			}
		}
		return temp;
	}

	// 직사각형 2차원 배열 좌로 90도 회전
	static int[][] rotationLeft(int[][] arr) {
		int n = arr.length;
		int m = arr[0].length;
		int[][] temp = new int[m][n];
		for(int i = 0; i < m; i++) {
			for(int j = 0; j < n; j++) {
				temp[i][j] = arr[j][m - 1 - i];
			}
		}
		return temp;
	}
}