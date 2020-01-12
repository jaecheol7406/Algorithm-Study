import java.io.IOException;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

/*
¸¹Àº °øÀå¿¡¼­ ·Îº¿ÀÌ ÀÌ¿ëµÇ°í ÀÖ´Ù. ¿ì¸® ¿ùµå °øÀåÀÇ ·Îº¿Àº ¹Ù¶óº¸´Â ¹æÇâÀ¸·Î ±Ëµµ¸¦ µû¶ó ¿òÁ÷ÀÌ¸ç, ¿òÁ÷ÀÌ´Â ¹æÇâÀº µ¿, ¼­, ³², ºÏ °¡¿îµ¥ ÇÏ³ªÀÌ´Ù. ·Îº¿ÀÇ ÀÌµ¿À» Á¦¾îÇÏ´Â ¸í·É¾î´Â ´ÙÀ½°ú °°ÀÌ µÎ °¡ÁöÀÌ´Ù.
¸í·É 1. Go k
  - k´Â 1, 2 ¶Ç´Â 3ÀÏ ¼ö ÀÖ´Ù. ÇöÀç ÇâÇÏ°í ÀÖ´Â ¹æÇâÀ¸·Î kÄ­ ¸¸Å­ ¿òÁ÷ÀÎ´Ù.
¸í·É 2. Turn dir
  - dirÀº left ¶Ç´Â right ÀÌ¸ç, °¢°¢ ¿ŞÂÊ ¶Ç´Â ¿À¸¥ÂÊÀ¸·Î 90¡Æ È¸ÀüÇÑ´Ù.
°øÀå ³» ±Ëµµ°¡ ¼³Ä¡µÇ¾î ÀÖ´Â »óÅÂ°¡ ¾Æ·¡¿Í °°ÀÌ 0°ú 1·Î ÀÌ·ç¾îÁø Á÷»ç°¢Çü ¸ğ¾çÀ¸·Î ·Îº¿¿¡°Ô ÀÔ·ÂµÈ´Ù. 0Àº ±Ëµµ°¡ ±ò·Á ÀÖ¾î ·Îº¿ÀÌ °¥ ¼ö ÀÖ´Â ÁöÁ¡ÀÌ°í, 1Àº ±Ëµµ°¡ ¾ø¾î ·Îº¿ÀÌ °¥ ¼ö ¾ø´Â ÁöÁ¡ÀÌ´Ù. ·Îº¿ÀÌ (4, 2) ÁöÁ¡¿¡¼­ ³²ÂÊÀ» ÇâÇÏ°í ÀÖÀ» ¶§,  ÀÌ ·Îº¿À» (2, 4) ÁöÁ¡¿¡¼­ µ¿ÂÊÀ¸·Î ÇâÇÏµµ·Ï ÀÌµ¿½ÃÅ°´Â °ÍÀº ¾Æ·¡¿Í °°ÀÌ 9¹øÀÇ ¸í·ÉÀ¸·Î °¡´ÉÇÏ´Ù.
·Îº¿ÀÇ ÇöÀç À§Ä¡¿Í ¹Ù¶óº¸´Â ¹æÇâÀÌ ÁÖ¾îÁ³À» ¶§, ·Îº¿À» ¿øÇÏ´Â À§Ä¡·Î ÀÌµ¿½ÃÅ°°í, ¿øÇÏ´Â ¹æÇâÀ¸·Î ¹Ù¶óº¸µµ·Ï ÇÏ´Âµ¥ ÃÖ¼Ò ¸î ¹øÀÇ ¸í·ÉÀÌ ÇÊ¿äÇÑÁö ±¸ÇÏ´Â ÇÁ·Î±×·¥À» ÀÛ¼ºÇÏ½Ã¿À.
ÀÔ·Â
Ã¹Â° ÁÙ¿¡ °øÀå ³» ±Ëµµ ¼³Ä¡ »óÅÂ¸¦ ³ªÅ¸³»´Â Á÷»ç°¢ÇüÀÇ ¼¼·Î ±æÀÌ M°ú °¡·Î ±æÀÌ NÀÌ ºóÄ­À» »çÀÌ¿¡ µÎ°í ÁÖ¾îÁø´Ù. ÀÌ¶§ M°ú NÀº µÑ ´Ù 100ÀÌÇÏÀÇ ÀÚ¿¬¼öÀÌ´Ù. ÀÌ¾î MÁÙ¿¡ °ÉÃÄ ÇÑ ÁÙ¿¡ N°³¾¿ °¢ ÁöÁ¡ÀÇ ±Ëµµ ¼³Ä¡ »óÅÂ¸¦ ³ªÅ¸³»´Â ¼ıÀÚ 0 ¶Ç´Â 1ÀÌ ºóÄ­À» »çÀÌ¿¡ µÎ°í ÁÖ¾îÁø´Ù. ´ÙÀ½ ÁÙ¿¡´Â ·Îº¿ÀÇ Ãâ¹ß ÁöÁ¡ÀÇ À§Ä¡ (Çà°ú ¿­ÀÇ ¹øÈ£)¿Í ¹Ù¶óº¸´Â ¹æÇâÀÌ ºóÄ­À» »çÀÌ¿¡ µÎ°í ÁÖ¾îÁø´Ù. ¸¶Áö¸· ÁÙ¿¡´Â ·Îº¿ÀÇ µµÂø ÁöÁ¡ÀÇ À§Ä¡ (Çà°ú ¿­ÀÇ ¹øÈ£)¿Í ¹Ù¶óº¸´Â ¹æÇâÀÌ ºóÄ­À» »çÀÌ¿¡ µÎ°í ÁÖ¾îÁø´Ù. ¹æÇâÀº µ¿ÂÊÀÌ 1, ¼­ÂÊÀÌ 2, ³²ÂÊÀÌ 3, ºÏÂÊÀÌ 4·Î ÁÖ¾îÁø´Ù. Ãâ¹ßÁöÁ¡¿¡¼­ µµÂøÁöÁ¡±îÁö´Â Ç×»ó ÀÌµ¿ÀÌ °¡´ÉÇÏ´Ù.
Ãâ·Â
Ã¹Â° ÁÙ¿¡ ·Îº¿À» µµÂø ÁöÁ¡¿¡ ¿øÇÏ´Â ¹æÇâÀ¸·Î ÀÌµ¿½ÃÅ°´Âµ¥ ÇÊ¿äÇÑ ÃÖ¼Ò ¸í·É È½¼ö¸¦ Ãâ·ÂÇÑ´Ù. */

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
	public static final int[][] moveDir = new int[][]{{0, 0}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}}; // 0 : ï¿½ï¿½ï¿½ï¿½ ï¿½Îµï¿½ï¿½ï¿½

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
	
	// bfs : ï¿½ï¿½ï¿½ï¿½
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
	
	//ï¿½ï¿½ï¿?: ï¿½Ş¸ï¿½ ï¿½Ê°ï¿½
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
	
	// È¸ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ È½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
	static int turn(int nowDir, int goDir, int commandNum) {
		if(nowDir == 1 || nowDir == 2) { // ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½
			if(goDir == 3 || goDir == 4) // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½, ï¿½ï¿½ï¿½Ì¸ï¿½
				commandNum += 1; // ï¿½Ñ¹ï¿½ È¸ï¿½ï¿½
			else if(goDir != nowDir) // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½, ï¿½ï¿½ï¿½Ì°ï¿½ ï¿½İ´ï¿½ï¿½ï¿½ï¿½ï¿½Ì¸ï¿?ï¿½Î¹ï¿½ È¸ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ì¸ï¿½ È¸ï¿½ï¿½ x
				commandNum += 2;
		} else { // ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½
			if(goDir == 1 || goDir == 2) // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½, ï¿½ï¿½ï¿½Ì¸ï¿½
				commandNum += 1; // ï¿½Ñ¹ï¿½ È¸ï¿½ï¿½
			else if(goDir != nowDir) // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½, ï¿½ï¿½ï¿½Ì°ï¿½ ï¿½İ´ï¿½ï¿½ï¿½ï¿½ï¿½Ì¸ï¿?ï¿½Î¹ï¿½ È¸ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ì¸ï¿½ È¸ï¿½ï¿½ x
				commandNum += 2; // ï¿½Î¹ï¿½ È¸ï¿½ï¿½
		}

		return commandNum; 
	}
}