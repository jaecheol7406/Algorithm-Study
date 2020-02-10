import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;
/* 
 * 17837_새로운 게임 2
 */
public class Main2 {
	public static final int[][] moveDir = new int[][]{{}, {0, 1}, {0, -1}, {-1, 0}, {1, 0}}; // 동, 서, 북, 남
	public static final int WHITE = 0;
	public static final int RED = 1;
	public static final int BLUE = 2;
	
	static int N, K;
	static ArrayList<Node>[][] boardNode;
	static int[][] boardStatus;
	static Node[] nodes;
	
	static int turn = 0;
	static boolean gameSet = false;
	
	public static void main(String[] args) {
		input();
		solve();
	}
	
	static void input() {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		K = sc.nextInt();
		boardNode = new ArrayList[N + 1][N + 1];
		nodes = new Node[K + 1];

		boardStatus = new int[N + 1][N + 1];
		
		for(int i = 1; i <= N; i++) {
			for(int j = 1; j <= N; j++) {
				boardStatus[i][j] = sc.nextInt();
				boardNode[i][j] = new ArrayList<>();
			}
		}
		
		for(int i = 1; i <= K; i++) {
			int x = sc.nextInt();
			int y = sc.nextInt();
			int dir = sc.nextInt();
			Node node = new Node(i, x, y, dir);
			nodes[i] = node;
			boardNode[x][y].add(node);
		}
				
		sc.close();
	}
	
	static void solve() {
		while(true) {
			turn++;

			for(int i = 1; i <= K; i++) {
				move(nodes[i]);
				if(gameSet)
					break;
			}
			if(gameSet || turn > 1000) {
				if(turn >= 1000)
					System.out.println(-1);
				else
					System.out.println(turn);
				
				return;
			}
		}
	}
	
	// 각 말 이동
	static void move(Node node) {
		int nextX = node.x + moveDir[node.dir][0];
		int nextY = node.y + moveDir[node.dir][1];
		
		// 범위 벗어날 때
		if(!inScope(nextX, nextY)) {
			changeDir(node); // 방향 바꾸고
			
			// 다음 갈 곳 계산
			int nextX2 = node.x + moveDir[node.dir][0];
			int nextY2 = node.y + moveDir[node.dir][1];
			
			// 파란색이면 이동 안하고 끝
			if(boardStatus[nextX2][nextY2] == BLUE)
				return;
			
			// 아니면 이동 (재귀)
			move(node);
			return;
		} 
		
		// 범위 안벗어날 때
		
		// 파란색일 때
		if(boardStatus[nextX][nextY] == BLUE) {
			changeDir(node); // 방향 바꾸고
			
			// 다음갈 곳 계산
			int nextX2 = node.x + moveDir[node.dir][0];
			int nextY2 = node.y + moveDir[node.dir][1];
			
			// 범위 안벗어나고 파란색이면 이동 안하고 끝
			if(inScope(nextX2, nextY2) && boardStatus[nextX2][nextY2] == BLUE)
				return;
			
			// 그 외(범위 벗어날 때 or 범위 안벗어나는데 파란색 아닐 때) 이동
			move(node);
			return;
		} 
		
		// 빨간색 or 하얀색일 때
		
		// 해당 말 위에있는 말들 떼어서 sublist에 저장
		List<Node> nodeList = boardNode[node.x][node.y];
		List<Node> sublist = new ArrayList<>();
		for(int i = 0; i < nodeList.size(); i++) {
			Node n = nodeList.get(i);
			if(n.nodeNum == node.nodeNum) {
				for(int j = i; j < nodeList.size(); j++)
					sublist.add(boardNode[node.x][node.y].get(j));
				int subSize = sublist.size();
				for(int j = 0; j < subSize; j++)
					boardNode[node.x][node.y].remove(i);
				break;
			}
		}
		
		// 빨간색일 때는 sublist 거꾸로 뒤집음
		if(boardStatus[nextX][nextY] == RED)
			Collections.reverse(sublist);
		
		// sublist 이동할 곳 위에 붙임
		for(int i = 0; i < sublist.size(); i++) {
			Node n = sublist.get(i);
			boardNode[nextX][nextY].add(n);
			// 좌표 변경
			n.x = nextX;
			n.y = nextY;
			
			// 4 이상 쌓이면 게임 끝, return
			if(boardNode[nextX][nextY].size() == 4) {
				gameSet = true;
				return;
			}
		}
	}
	
	// 방향 변경
	static void changeDir(Node node) {
		if(node.dir == 1 || node.dir == 3)
			node.dir++;
		else
			node.dir--;
	}
	
	// 범위 확인
	static boolean inScope(int x, int y) {
		if(1 <= x && x <= N && 1 <= y && y <= N)
			return true;
		return false;
	}
}

// 말
class Node {
	int nodeNum;
	int x;
	int y;
	int dir;
	
	public Node(int nodeNum, int x, int y, int dir) {
		this.nodeNum = nodeNum;
		this.x = x;
		this.y = y;
		this.dir = dir;
	}
}