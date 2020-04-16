package _2020_04;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
/*
 * 17140_이차원 배열과 연산
 * 
 * solve ->  ROp() or COp()
 * 
 * 배열 크기를 나타내는 R, C를 전역변수에 놓고 R >= C면 ROp, 아니면 COp 연산 호출한다. 연산과정에서 R, C가 바뀐다. 처음에는 3, 3
 * 각 연산에서는 해쉬맵을 이용함.
 * 
 * R 연산을 예로 들면,
 * 전체 R 개수 만큼의 해쉬맵 배열을 만들고, 각 행마다 해쉬맵에 숫자 갯수 정보를 저장해놓고, 가장 큰 해쉬맵 크기 * 2 만큼 C를 바꾼다.
 * 그 후 arr = new int[R][C] 해서 배열 새로 만들고 각 해쉬맵마다 정렬 후 정보들을 저장한다.
 * 
 * C 연산도 똑같은데 반대로 C 에 대해 해쉬맵 만들어서 진행한다.
 */
public class Main2 {
	static int r, c, k;
	static int[][] arr = new int[3][3];
	static int R = 3, C = 3;

	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] input = br.readLine().split(" ");
		r = Integer.parseInt(input[0]) - 1;
		c = Integer.parseInt(input[1]) - 1;
		k = Integer.parseInt(input[2]);

		for(int i = 0; i < 3; i++) {
			input = br.readLine().split(" ");
			for(int j = 0; j < 3; j++)
				arr[i][j] = Integer.parseInt(input[j]);
		}

		solve();
	}

	static void solve() {
		int t = 0;
		while(true) {
			if(t == 101) {
				t = -1;
				break;
			}
			
			if(r < R && c < C && arr[r][c] == k)
				break;

			if(R >= C)
				ROp();
			else
				COp();
			
			t++;
		}
		
		System.out.println(t);
	}

	static void ROp() {
		int maxSize = -1;

		HashMap<Integer, Integer>[] mapArr = new HashMap[R];
		for(int i = 0; i < R; i++) {
			HashMap<Integer, Integer> map = new HashMap<>();

			for(int j = 0; j < C; j++) {
				if(arr[i][j] == 0)
					continue;

				map.put(arr[i][j], map.getOrDefault(arr[i][j], 0) + 1);
			}

			mapArr[i] = map;

			if(maxSize < map.size() * 2)
				maxSize = map.size() * 2;
		}
		
		if(maxSize > 100)
			C = 100;
		else
			C = maxSize;
		
		arr = new int[R][C];

		for(int i = 0; i < R; i++) {

			List<Map.Entry<Integer, Integer>> list = new LinkedList<>(mapArr[i].entrySet());
			Collections.sort(list, new Comparator<Entry<Integer, Integer>>() {

				@Override
				public int compare(Entry<Integer, Integer> o1, Entry<Integer, Integer> o2) {
					if(o1.getValue() < o2.getValue())
						return -1;

					if(o1.getValue() > o2.getValue())
						return 1;

					if(o1.getKey() < o2.getKey())
						return -1;

					if(o1.getKey() > o2.getKey())
						return 1;

					return 0;
				}
			});

			int idx = 0;
			for(Entry<Integer, Integer> en : list) {
				arr[i][idx++] = en.getKey();
				arr[i][idx++] = en.getValue();
				
				if(idx == 100)
					break;
			}
		}
	}

	static void COp() {
		int maxSize = -1;

		HashMap<Integer, Integer>[] mapArr = new HashMap[C];
		for(int j = 0; j < C; j++) {
			HashMap<Integer, Integer> map = new HashMap<>();

			for(int i = 0; i < R; i++) {
				if(arr[i][j] == 0)
					continue;

				map.put(arr[i][j], map.getOrDefault(arr[i][j], 0) + 1);
			}

			mapArr[j] = map;

			if(maxSize < map.size() * 2)
				maxSize = map.size() * 2;
		}
		
		if(maxSize > 100)
			R = 100;
		else
			R = maxSize;
		
		arr = new int[R][C];

		for(int j = 0; j < C; j++) {

			List<Map.Entry<Integer, Integer>> list = new LinkedList<>(mapArr[j].entrySet());
			Collections.sort(list, new Comparator<Entry<Integer, Integer>>() {

				@Override
				public int compare(Entry<Integer, Integer> o1, Entry<Integer, Integer> o2) {
					if(o1.getValue() < o2.getValue())
						return -1;

					if(o1.getValue() > o2.getValue())
						return 1;

					if(o1.getKey() < o2.getKey())
						return -1;

					if(o1.getKey() > o2.getKey())
						return 1;

					return 0;
				}
			});

			int idx = 0;
			for(Entry<Integer, Integer> en : list) {
				arr[idx++][j] = en.getKey();
				arr[idx++][j] = en.getValue();
				
				if(idx == 100)
					break;
			}
		}
	}
}