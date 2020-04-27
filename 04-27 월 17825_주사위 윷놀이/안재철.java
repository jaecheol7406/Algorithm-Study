package _2020_04;
import java.io.BufferedReader;
import java.io.InputStreamReader;
/*
 * 17825_주사위 윷놀이
 * 
 * main -> solve -> dfs -> GameBoard 클래스의 move
 * 
 * GameBoard 클래스 생성자 4 넣어서 호출. -> Horse로 말 표현, 4개의 Horse 객체가 생성.  게임판은  32개짜리 배열로 표현 (1 ~ 31 인덱스)
 * 말이 있다는걸 표시하는 possess : 게임판 크기과 같은 크기의 배열로 표시함.
 * 
 * 주사위 10개의 턴에 각각 말 4개씩 해보는 경우의수 4 ^ 10 == 2 ^ 20 만큼 dfs 진행.
 * 각 dfs에서는 생성한 GameBoard 객체의 move 메소드로 선택한 말 이동, 10번 다 이동하면 지금까지의 점수 maxScore에 업데이트.
 */
public class No17825_주사위윷놀이 {
	static int[] nums = new int[10];
	static GameBoard gb = new GameBoard(4);

	static int maxScore;

	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] input = br.readLine().split(" ");
		for(int i = 0; i < 10; i++) {
			int num = Integer.parseInt(input[i]);
			nums[i] = num;
		}

		solve();
	}

	static void solve() throws CloneNotSupportedException {
		dfs(0, gb);
		System.out.println(maxScore);
	}

	static void dfs(int moveIdx, GameBoard gb) throws CloneNotSupportedException {
		if(moveIdx == 10) {
			if(gb.score > maxScore)
				maxScore = gb.score;
			
			return;
		}

		int num = nums[moveIdx];
		
		for(int i = 0; i < gb.horseNum; i++) {
			if(gb.horses[i].state == 0) { // 아직 도착 안했으면 이동 시도
				GameBoard temp = gb.clone();
				if(!temp.move(i, num)) // 이동하려는 칸에 말 이미 있으면 이동 취소
					continue;
				
				dfs(moveIdx + 1, temp); // 이동 후 다음 턴
			}
		}
	}
}

class GameBoard implements Cloneable {
	public static final int[] board = {-1,
			2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,
			13,16,19,
			22,24,
			28,27,26,
			25,30,35};
	
	int horseNum;

	Horse[] horses;
	int score;
	boolean[] possess = new boolean[32];
	
	public GameBoard(int horseNum) {
		this.horseNum = horseNum;

		horses = new Horse[horseNum];
		for(int i = 0; i < horseNum; i++)
			horses[i] = new Horse();

		this.score = 0;
	}
	
	public boolean move(int horseIdx, int num) {
		Horse h = this.horses[horseIdx];
		int tempIdx = 0;
		
		if(h.idx == 0) {
			tempIdx = num;
		} else if(h.idx == 5 || 21 <= h.idx && h.idx <= 23) {
			tempIdx = h.idx;
			if(h.idx == 5)
				tempIdx = 20;
			
			tempIdx += num;
			
			if(24 <= tempIdx && tempIdx <= 26)
				tempIdx += 5;
			else if(tempIdx == 27)
				tempIdx = 20;
			else if(tempIdx >= 28) {
				h.state = 1;
				possess[h.idx] = false;
				return true;
			}
			
		} else if(h.idx == 10 || 24 <= h.idx && h.idx <= 25) {
			tempIdx = h.idx;
			if(h.idx == 10)
				tempIdx = 23;
			
			tempIdx += num;
			
			if(26 <= tempIdx && tempIdx <= 28)
				tempIdx += 3;
			else if(tempIdx == 29)
				tempIdx = 20;
			else if(tempIdx >= 30) {
				h.state = 1;
				possess[h.idx] = false;
				return true;
			}
			
		} else if(h.idx == 15 || 26 <= h.idx && h.idx <= 28) {
			tempIdx = h.idx;
			if(h.idx == 15)
				tempIdx = 25;
			
			tempIdx += num;
			
			if(29 <= tempIdx && tempIdx <= 31)
				;
			else if(tempIdx == 32)
				tempIdx = 20;
			else if(tempIdx >= 33) {
				h.state = 1;
				possess[h.idx] = false;
				return true;
			}
			
		} else if(29 <= h.idx && h.idx <= 31) {
			tempIdx = h.idx + num;
			if(tempIdx >= 33) {
				h.state = 1;
				possess[h.idx] = false;
				return true;
			}
			
			if(tempIdx == 32)
				tempIdx = 20;
			
		} else {
			tempIdx = h.idx + num;
			if(tempIdx >= 21) {
				h.state = 1;
				possess[h.idx] = false;
				return true;
			}
		}
		
		if(possess[tempIdx])
			return false;
		
		possess[h.idx] = false;
		h.idx = tempIdx;
		possess[h.idx] = true;
		this.score += board[h.idx];
		
		return true;
	}
	
	@Override
	protected GameBoard clone() throws CloneNotSupportedException {
		GameBoard copy = (GameBoard)super.clone();
		for(int i = 0; i < copy.horseNum; i++)
			copy.horses[i] = this.horses[i].clone();
		copy.possess = this.possess.clone();
		return copy;
	}
}

class Horse implements Cloneable {
	int state; // 0 : 도착 x(시작 or 보드판 위), 1 : 도착
	int idx; // 위치

	public Horse() {
		this.state = 0;
		idx = 0;
	}
	
	@Override
	protected Horse clone() throws CloneNotSupportedException {
		return (Horse)super.clone();
	}
}