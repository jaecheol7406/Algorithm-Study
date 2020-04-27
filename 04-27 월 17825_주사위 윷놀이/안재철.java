package _2020_04;
import java.io.BufferedReader;
import java.io.InputStreamReader;
/*
 * 17825_주사위 윷놀이 (디버딩중)
 * 
 * main -> solve -> dfs -> GameBoard 클래스의 move
 * 
 * GameBoard 클래스 생성자 4 넣어서 호출. -> Horse로 말 표현, 4개의 Horse 객체가 생성.  게임판은 4개의 배열로 표현. 첫번째는 원모양, 나머지는 파란색에서 출발하는 3개
 * 말이 있다는걸 표시하는 possess 게임판 크기과 같은 크기의 배열로 표신함.
 * 
 * 주사위 10개의 턴에 각각 말 4개씩 해보는 경우의수 4 ^ 10 == 2 ^ 20 만큼 dfs 진행.
 * 각 dfs에서는 생성한 GameBoard 객체의 move 메소드로 선택한 말 이동, 10번 다 이동하면 지금까지의 점수 maxScore에 업데이트.
 */
public class Main {
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
	public static final int[][] board = {
			{2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40}, 
			{10,13,16,19,25,30,35,40},
			{20,22,24,25,30,35,40},
			{30,28,27,26,25,30,35,40}
	};
	
	int horseNum;

	Horse[] horses;
	int score;
	boolean[][] possess= new boolean[4][];
	
	public GameBoard(int horseNum) {
		this.horseNum = horseNum;

		horses = new Horse[horseNum];
		for(int i = 0; i < horseNum; i++)
			horses[i] = new Horse();

		this.score = 0;
		
		for(int i = 0; i < 4; i++)
			possess[i] = new boolean[board[i].length];
	}

	public boolean move(int horseIdx, int num) {		
		Horse h = this.horses[horseIdx];
		int b = h.board;
		
		if(h.idx + num >= board[b].length) { // 해당 보드의 인덱스 넘어가면 도착
			h.state = 1;
			possess[b][h.idx] = false; // 원래 칸 더이상 차지하지 않도록 표시
			return true;
		} 
		
		if(possess[b][h.idx + num]) // 움직이려는 곳에 말이 있으면 못움직임.
			return false;
		
		if(h.idx != -1) // 시작에서 출발한 것이 아니면
			possess[b][h.idx] = false; // 원래 칸 더이상 차지하지 않도록 표시
		h.idx += num; // 이동 후
		this.score += board[b][h.idx]; // 점수 획득
		
		if(h.board == 0) { // 첫번째 보드인데 파란색 칸으로 이동했다면 가운데 있는 1,2,3 보드로 넘어감.
			int temp = h.idx;
			h.idx = 0;
			if(temp == 4)
				h.board = 1;
			else if(temp == 9)
				h.board = 2;
			else if(temp == 14)
				h.board = 3;
			else
				h.idx = temp;
		}

		possess[h.board][h.idx] = true; // 이동 후 해당 칸 차지
		return true;
	}
	
	@Override
	protected GameBoard clone() throws CloneNotSupportedException {
		GameBoard copy = (GameBoard)super.clone();
		for(int i = 0; i < copy.horseNum; i++)
			copy.horses[i] = this.horses[i].clone();
		for(int i = 0; i < 4; i++)
			copy.possess[i] = this.possess[i].clone();
		return copy;
	}
}

class Horse implements Cloneable {
	int state; // 0 : 도착 x(시작 or 보드판 위), 1 : 도착
	int board; // 0,1,2,3
	int idx; // 각 보드의 위치 (인덱스)

	public Horse() {
		this.state = 0;
		this.board = 0;
		idx = -1;
	}
	
	@Override
	protected Horse clone() throws CloneNotSupportedException {
		return (Horse)super.clone();
	}
}