import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Deque;
import java.util.LinkedList;
/*
 * 1021_회전하는 큐
 * 
 * main() 에서 모두 해결.
 * 
 * 1. Deque에 1 ~ N 까지 넣는다.
 * 2. arr에 M개의 꺼낼 숫자 넣는다.
 * 3. arr에서 M개의 숫자 처음부터 순회 하여 빼는 반복문 시작.
 * 		(1) 꺼낼 숫자(target) 나올때 까지 Deque에서 앞에서 꺼내 뒤에 다시 넣는다. (2번연산)
 * 		(2) 꺼낸 숫자가 target이면  min(앞에서 꺼낸 횟수, Deque의 size - 앞에서 꺼낸 횟수)를 total에 더한다.
 * 			-> 뒤에서 꺼낸 횟수 (3번 연산)이 더 적을 수 있기 때문에 뒤에서 꺼낸 횟수 = (Deque의 size - 앞에서 꺼낸 횟수)와 비교 후 적은값 선택한다.
 * 			-> target이 나올 때까지 앞에서 빼서 뒤에 넣는거랑, target이 나올 때 까지 뒤에서 뺀 후 앞에 넣는거랑 큐의 상태가 같기떄문.
 * 4. M개의 숫자 모두 꺼내면 반복문 탈출 후 total 출력
 */
public class Main2 {
	static int N, M;
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] input = br.readLine().split(" ");
		N = Integer.parseInt(input[0]);
		M = Integer.parseInt(input[1]);
		
		int[] arr = new int[M];
		input = br.readLine().split(" ");
		for(int i = 0; i < M; i++)
			arr[i] = Integer.parseInt(input[i]);
			
		Deque<Integer> dq = new LinkedList<Integer>();
		for(int i = 1; i <= N; i++)
			dq.add(i);
		
		int total = 0;
		int idx = 0;
		while(idx < M) {
			int target = arr[idx];
			
			int size = dq.size();
			int front = 0;
			while(true) {
				int ele = dq.pollFirst();
				if(ele != target) {
					dq.addLast(ele);
					front++;
				} else {
					int back = size - front;
					total += Integer.min(front, back);
					break;
				}
			}
			idx++;
		}
		System.out.println(total);
	}
}