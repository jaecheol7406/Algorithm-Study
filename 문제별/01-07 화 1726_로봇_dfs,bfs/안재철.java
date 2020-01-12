import java.io.IOException;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

/*
���� ���忡�� �κ��� �̿�ǰ� �ִ�. �츮 ���� ������ �κ��� �ٶ󺸴� �������� �˵��� ���� �����̸�, �����̴� ������ ��, ��, ��, �� ��� �ϳ��̴�. �κ��� �̵��� �����ϴ� ��ɾ�� ������ ���� �� �����̴�.
��� 1. Go k
  - k�� 1, 2 �Ǵ� 3�� �� �ִ�. ���� ���ϰ� �ִ� �������� kĭ ��ŭ �����δ�.
��� 2. Turn dir
  - dir�� left �Ǵ� right �̸�, ���� ���� �Ǵ� ���������� 90�� ȸ���Ѵ�.
���� �� �˵��� ��ġ�Ǿ� �ִ� ���°� �Ʒ��� ���� 0�� 1�� �̷���� ���簢�� ������� �κ����� �Էµȴ�. 0�� �˵��� ��� �־� �κ��� �� �� �ִ� �����̰�, 1�� �˵��� ���� �κ��� �� �� ���� �����̴�. �κ��� (4, 2) �������� ������ ���ϰ� ���� ��,  �� �κ��� (2, 4) �������� �������� ���ϵ��� �̵���Ű�� ���� �Ʒ��� ���� 9���� ������� �����ϴ�.
�κ��� ���� ��ġ�� �ٶ󺸴� ������ �־����� ��, �κ��� ���ϴ� ��ġ�� �̵���Ű��, ���ϴ� �������� �ٶ󺸵��� �ϴµ� �ּ� �� ���� ����� �ʿ����� ���ϴ� ���α׷��� �ۼ��Ͻÿ�.
�Է�
ù° �ٿ� ���� �� �˵� ��ġ ���¸� ��Ÿ���� ���簢���� ���� ���� M�� ���� ���� N�� ��ĭ�� ���̿� �ΰ� �־�����. �̶� M�� N�� �� �� 100������ �ڿ����̴�. �̾� M�ٿ� ���� �� �ٿ� N���� �� ������ �˵� ��ġ ���¸� ��Ÿ���� ���� 0 �Ǵ� 1�� ��ĭ�� ���̿� �ΰ� �־�����. ���� �ٿ��� �κ��� ��� ������ ��ġ (��� ���� ��ȣ)�� �ٶ󺸴� ������ ��ĭ�� ���̿� �ΰ� �־�����. ������ �ٿ��� �κ��� ���� ������ ��ġ (��� ���� ��ȣ)�� �ٶ󺸴� ������ ��ĭ�� ���̿� �ΰ� �־�����. ������ ������ 1, ������ 2, ������ 3, ������ 4�� �־�����. ����������� �������������� �׻� �̵��� �����ϴ�.
���
ù° �ٿ� �κ��� ���� ������ ���ϴ� �������� �̵���Ű�µ� �ʿ��� �ּ� ��� Ƚ���� ����Ѵ�. */

class MoveInfo{
	int x;
	int y;
	int dir;
	int commandNum;

	public MoveInfo(int x, int y, int dir, int commandNum) {
		this.x = x;
		this.y = y;
		this.dir = dir;
		this.commandNum = commandNum;
	}
}

public class Main {
	public static final int[][] moveDir = new int[][]{{0, 0}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}}; // 0 : ���� �ε���

	static int M, N;
	static int[][] map;
	static boolean[][][] visit;

	static int startX, startY, endX, endY;
	static int startDir, endDir;

	static int minCommand = Integer.MAX_VALUE;

	public static void main(String[] args) throws IOException{
		Scanner sc = new Scanner(System.in);

		M = sc.nextInt();
		N = sc.nextInt();

		map = new int[M + 1][N + 1];
		visit = new boolean[M + 1][N + 1][5];

		for(int i = 1; i <= M; i++) {
			for(int j = 1; j <= N; j++) {
				map[i][j] = sc.nextInt();
			}
		}

		startX = sc.nextInt();
		startY = sc.nextInt();
		startDir = sc.nextInt();
		endX = sc.nextInt();
		endY = sc.nextInt();
		endDir = sc.nextInt();

//		dfs(startX, startY, startDir, 0);
		bfs();

		System.out.println(minCommand);

		sc.close();
	}	
	
	// bfs : ����
	static void bfs() {
		Queue<MoveInfo> queue = new LinkedList<>();

		int commandNum = 0;

		queue.add(new MoveInfo(startX, startY, startDir, commandNum));

		while(!queue.isEmpty()) {
			MoveInfo mi = queue.poll();
			visit[mi.x][mi.y][mi.dir] = true;

			if(mi.x == endX && mi.y == endY) {
				int newCommandNum = turn(mi.dir, endDir, mi.commandNum);

				minCommand = Integer.min(minCommand, newCommandNum);
				visit[endX][endY][endDir] = false;
				continue;
			}

			for(int goDir = 1; goDir <= 4; goDir++) {
				if(mi.commandNum != 0 && turn(mi.dir, goDir, mi.commandNum) == mi.commandNum + 2)
					continue;

				int moveX = 0, moveY = 0, step;

				for(step = 1; step <= 3; step++) {
					moveX = mi.x + moveDir[goDir][0] * step;
					moveY = mi.y + moveDir[goDir][1] * step;

					if(!(1 <= moveX && moveX <= M && 1 <= moveY && moveY <= N && !visit[moveX][moveY][goDir] && map[moveX][moveY] == 0))
						break;

					int newCommandNum = turn(mi.dir, goDir, mi.commandNum);

					queue.add(new MoveInfo(moveX, moveY, goDir, ++newCommandNum));
				}			
			}
		}
	}
	
	//���?: �޸� �ʰ�
	static void dfs(int x, int y, int dir, int commandNum) {
		visit[x][y][dir] = true;

		if(x == endX && y == endY) {
			int newCommandNum = turn(dir, endDir, commandNum);
			minCommand = Integer.min(minCommand, newCommandNum);
			return;
		}

		for(int goDir = 1; goDir <= 4; goDir++) {
			for(int step = 1; step <= 3; step++) {
				int moveX = x + moveDir[goDir][0] * step;
				int moveY = y + moveDir[goDir][1] * step;
				
				if(!(1 <= moveX && moveX <= M && 1 <= moveY && moveY <= N && !visit[moveX][moveY][goDir] && map[moveX][moveY] == 0))
					break;
				
				int newCommandNum = turn(dir, goDir, commandNum);
				dfs(moveX, moveY, goDir, ++newCommandNum);
			}	
		}
		
		visit[x][y][dir] = false;
	}
	
	// ȸ���� ���� ������ ���� Ƚ�� ����
	static int turn(int nowDir, int goDir, int commandNum) {
		if(nowDir == 1 || nowDir == 2) { // ���� ���� ��, ���� ��
			if(goDir == 3 || goDir == 4) // ������ ������ ��, ���̸�
				commandNum += 1; // �ѹ� ȸ��
			else if(goDir != nowDir) // ������ ������ ��, ���̰� �ݴ�����̸�?�ι� ȸ��, ���������̸� ȸ�� x
				commandNum += 2;
		} else { // ���� ���� ��, ���� ��
			if(goDir == 1 || goDir == 2) // ������ ������ ��, ���̸�
				commandNum += 1; // �ѹ� ȸ��
			else if(goDir != nowDir) // ������ ������ ��, ���̰� �ݴ�����̸�?�ι� ȸ��, ���������̸� ȸ�� x
				commandNum += 2; // �ι� ȸ��
		}

		return commandNum; 
	}
}