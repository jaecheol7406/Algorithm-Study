import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Scanner;
/* 
5653. [모의 SW 역량테스트] 줄기세포배양
 */
public class Main4 {
	public static final int[][] moveDir = new int[][]{{0, 1}, {0, -1}, {1, 0}, {-1, 0}}; // 동, 서, 남, 북

	static int T;
	static int N, M, K;
	static Cell[][] map;
	static List<Pos> nodePosList; // 세포가 존재하는 곳의 좌표 리스트
	static HashMap<Pos, Integer> propagateMap; // 번식된 세포의 좌표값과 생명력 정보를 해쉬로 관리

	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		T = sc.nextInt();
		for(int t = 1; t <= T; t++){
			N = sc.nextInt();
			M = sc.nextInt();
			K = sc.nextInt();
			map = new Cell[1001][1001]; // 배양용기
			nodePosList = new ArrayList<>();

			int startI = 500 - N / 2; // 배양용기의 중앙에 초기 상태 세포들 위치
			int startJ = 500 - M / 2;
			for(int i = startI; i < startI + N; i++) {
				for(int j = startJ; j < startJ + M; j++) {
					int life = sc.nextInt();
					if(life != 0) {
						map[i][j] = new Cell(life, Cell.INACTIVE, 0); // 생명력 있으면 비활성화 상태로 저장, 태어난 시간 0으로 저장
						nodePosList.add(new Pos(i, j)); // 세포의 좌표 정보 리스트에 추가
					}
				}
			}

			System.out.print("#" + t + " ");
			System.out.println(solve());
		}

		sc.close();
	}

	static int solve() {
		for(int time = 1; time <= K; time++) { // time : 전체 흘러간 시간
			propagateMap = new HashMap<>(); // 번식 정보 초기화

			for(Pos pos : nodePosList) { // 모든 세포에 대해
				int x = pos.x;
				int y = pos.y;

				Cell node = map[x][y];
				
				// 죽었으면 무시
				if(node.state == Cell.DEAD)
					continue;
				
				// 세포가 태어난 후 흘러간 시간
				int passedTime = time - node.bornTime;
				
				if(passedTime == node.life) // 그 시간이 생명력과 같아지면
					node.state = Cell.ACTIVE; // 활성화
				else if(passedTime == node.life + 1) // 활성화되고 1시간 지나면 
					propagation(x, y, node.life); // 번식

				if(passedTime == node.life * 2) // 활성화 되고 생명력만큼 더 지나면
					node.state = Cell.DEAD; // 주금

				map[x][y] = node;
			}
			
			// 번식된 세포 update
			for(Pos pos : propagateMap.keySet()) {
				map[pos.x][pos.y] = new Cell(propagateMap.get(pos), Cell.INACTIVE, time);
				nodePosList.add(pos);
			}
		}
		
		int alive = 0;
		
		// 죽지 않은 세포만 count
		for(Pos pos : nodePosList) {
			Cell node = map[pos.x][pos.y];
			if(node.state != Cell.DEAD)
				alive++;
		}

		return alive;
	}

	static void propagation(int x, int y, int life) {
		for(int i = 0; i < moveDir.length; i++) { // 동서남북 4방향에 대해 번식 가능성 검사
			int nextx = x + moveDir[i][0];
			int nexty = y + moveDir[i][1];
			Pos nextPos = new Pos(nextx, nexty);
			
			// 이미 세포가 있으면 번식 불가능
			if(map[nextx][nexty] != null)
				continue;
			
			// 번식 가능하면 해당 좌표와 생명력을 해쉬맵에 저장 -> 해당 좌표에 저장하면 또 다른 세포가 번식할 때 원래 있던 세포인지 번식한 세포인지 구분 불가능
			if(!propagateMap.containsKey(nextPos))
				propagateMap.put(nextPos, life);
			else { // 이미 해당 좌표에 있으면
				int another = propagateMap.get(nextPos); // 이미 있는 세포의 생명력과 
				if(life > another) // 비교해서
					propagateMap.put(nextPos, life); // 큰 놈이 차지함.
			}
		}
	}
}

// 세포
class Cell {
	public static final int INACTIVE = 0; // 비활성화
	public static final int ACTIVE = 1; // 활성화
	public static final int DEAD = -1; // 죽음

	int life; // 생명력
	int state; // 상태
	int bornTime; // 태어난 시간

	public Cell(int life, int state, int time) {
		this.life = life;
		this.state = state;
		this.bornTime = time;
	}
}

// 세포의 좌표, 해쉬맵에서 containsKey 호출 시 equals, hashCode 활용하기 때문에 overriding 해줘야 한다.
class Pos {
	int x;
	int y;

	public Pos(int x, int y) {
		this.x = x;
		this.y = y;
	}

	@Override
	public boolean equals(Object o) {
		Pos ano = (Pos)o;
		if(this.x == ano.x && this.y == ano.y)
			return true;
		else
			return false;
	}

	@Override
	public int hashCode() {

		final int prime = 31;
		int hashCode = 1;

		hashCode = prime * hashCode + this.x;
		hashCode = prime * hashCode + this.y;

		return hashCode;
	}
}