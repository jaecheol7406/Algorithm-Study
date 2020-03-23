import java.io.BufferedReader;
import java.io.InputStreamReader;
/*
 * 15662_톱니바퀴 (2)
 * 1. 입력 : String 배열에 톱니바퀴 정보 저장(wheels), 하나의 톱니바퀴는 String으로 표현, 이후 K만큼 회전정보 입력받으며 rotate 호출
 * 2. rotate() : 매개변수는 기준 톱니바퀴의 인덱스, 회전방향임. 기준 톱니바퀴에서 왼쪽, 오른쪽으로 가며 회전하고 기준 톱니바퀴는 맨 마지막에 회전함.
 * 		(1) 왼쪽
 * 			1. 기준 톱니바퀴의 왼쪽 톱니바퀴부터 시작해서 맨 끝까지 검사하는데, 현재 톱니바퀴의 오른쪽 극과 이전 톱니바퀴의 왼쪽극과 비교
 * 			2. 같으면 break;
 * 			3. 다르면 rotateWheel() 함수로 회전 (전 톱니바퀴의 dir의 반대), 1.부터 반복
 * 				rotateWheel() : 문자열 조작으로 1, -1에 따라 시계, 반시계 회전
 * 		(2) 오른쪽도 위와 동일, 방향만 반대
 * 		(3) 가운데(기준) 톱니바퀴 회전
 * 3. 12시가 S인 개수 출력
 */
public class Main3 {
	static int T, K;
	static String[] wheels;
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		T = Integer.parseInt(br.readLine());
		
		wheels = new String[T];
		for(int i = 0; i < T; i++)
			wheels[i] = br.readLine();
		
		K = Integer.parseInt(br.readLine());
		for(int i = 0; i < K; i++) {
			String[] input = br.readLine().split(" ");
			int whNum = Integer.parseInt(input[0]) - 1;
			int dir = Integer.parseInt(input[1]);
			
			rotate(whNum, dir);
		}
		
		int count = 0;
		for(int i = 0; i < T; i++) {
			String wh = wheels[i];
			if(wh.charAt(0) == '1')
				count++;
		}
		System.out.println(count);
	}	
	
	static void rotate(int idx, int dir) {
		int tempIdx = idx;
		int tempDir = dir;
		String std = wheels[idx];
		
		int leftAdj = std.charAt(6);
		while(--idx >= 0) {
			String now = wheels[idx];
			int rightAdj = now.charAt(2);
			if(leftAdj == rightAdj)
				break;
			
			leftAdj = now.charAt(6);
			
			dir = 0 - dir;
			rotateWheel(idx, dir);
		}
		
		idx = tempIdx;
		dir = tempDir;
		
		int rightAdj = std.charAt(2);
		while(++idx < T) {
			String now = wheels[idx];
			leftAdj = now.charAt(6);
			if(leftAdj == rightAdj)
				break;
			
			rightAdj = now.charAt(2);
			
			dir = 0 - dir;
			rotateWheel(idx, dir);
		}
		
		rotateWheel(tempIdx, tempDir);
	}
	
	static void rotateWheel(int wheelIdx, int dir) {
		String wheel = wheels[wheelIdx];
		if(dir == 1)
			wheels[wheelIdx] = wheel.charAt(wheel.length() - 1) + wheel.substring(0, wheel.length() - 1);
		else
			wheels[wheelIdx] = wheel.substring(1) + wheel.charAt(0);	
	}
}