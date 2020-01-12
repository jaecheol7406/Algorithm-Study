import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main3 {
	public static final int WHEEL_NUM = 4;
	public static final int WHEEL_TOOTH_NUM = 8;
	public static final int RIGHT_ADJOIN_IDX = 2;
	public static final int LEFT_ADJOIN_IDX = 6;
	static String[] wheels;

	public static void main(String[] args) throws IOException{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		wheels = new String[WHEEL_NUM + 1];
		for(int i = 1; i <= WHEEL_NUM; i++)
			wheels[i] = br.readLine();

		int k = Integer.parseInt(br.readLine());
		while(k-- > 0) {
			String[] s = br.readLine().split(" ");
			int wheelNum = Integer.parseInt(s[0]);
			int direction = Integer.parseInt(s[1]);
			rotation(wheelNum, direction);
			
			for(int i = 1; i <= 4; i++) {
				for(int j = 0; j < 8; j++) {
					System.out.print(wheels[i].charAt(j));
				}
				System.out.println();
			}
			
			System.out.println(wheelNum + " " + direction);
			
		}
		
		int score = 0;
		
		for(int i = 1; i <= WHEEL_NUM; i++) {
			if(wheels[i].charAt(0) == '1')
				score += Math.pow(2, i - 1);
		}
		
		System.out.println(score);
	}
	
	static void rotation(int wheelNum, int direction) {
		int tempNum = wheelNum;
		int tempDir = direction;
		
		// 왼쪽으로 굴리기
		int rightWheelAdjoinIdx = wheels[wheelNum].charAt(LEFT_ADJOIN_IDX);
		
		while(--wheelNum >= 1) {
			String left = wheels[wheelNum];
			
			// 인접 톱니의 극 같으면 회전 안함
			if(left.charAt(RIGHT_ADJOIN_IDX) == rightWheelAdjoinIdx)
				break;
			
			rightWheelAdjoinIdx = wheels[wheelNum].charAt(LEFT_ADJOIN_IDX);
			
			if(direction == 1) {
				rotationLeft(wheelNum);
				direction = -1;
			}
			else {
				rotationRight(wheelNum);
				direction = 1;
			}
		}

		wheelNum = tempNum;
		direction = tempDir;
		
		// 오른쪽으로 굴리기
		int leftWheelAdjoinIdx = wheels[wheelNum].charAt(RIGHT_ADJOIN_IDX);
		
		while(++wheelNum <= WHEEL_NUM) {
			String right = wheels[wheelNum];
			if(leftWheelAdjoinIdx == right.charAt(LEFT_ADJOIN_IDX))
				break;
			
			leftWheelAdjoinIdx = wheels[wheelNum].charAt(RIGHT_ADJOIN_IDX);
			
			if(direction == 1) {
				rotationLeft(wheelNum);
				direction = -1;
			}
			else {
				rotationRight(wheelNum);
				direction = 1;
			}
		}
		
		// 맨 처음 톱니바퀴 회전
		if(tempDir == 1) 
			rotationRight(tempNum);
		else 
			rotationLeft(tempNum);
	}
	
	// 반시계방향 회전
	static void rotationLeft(int wheelNum) {
		wheels[wheelNum] = wheels[wheelNum].substring(1) + wheels[wheelNum].charAt(0);
	}

	// 시계방향 회전
	static void rotationRight(int wheelNum) {
		wheels[wheelNum] = wheels[wheelNum].charAt(WHEEL_TOOTH_NUM - 1) + wheels[wheelNum].substring(0, WHEEL_TOOTH_NUM - 1);
	}
} 