/*
1. DFS�� ���� �͵鳢�� ���� �׷��� �ľ��Ѵ�.
   ���� �׷��� dfs �迭�� ���� ���ڷ� ������ �ȴ�. ��: 1 1
                                                       0 2
2. dfs �迭���� �׷� �� �׷캰 ������ �ľ��� alreadyInGroup �迭�� �ִ´�.
   ��: alreadyInGroup[1] = 2 / alreadyInGroup[2] = 1;

3. alreadyInGroup[i] >= 4 ��� �Ͷ߸��� �߷��� �����Ѵ�.
   1) �Ͷ߸���: map[i][j] = '.'
   2) �߷� �����ϱ�: ��� �Ͷ߸� ��(j��)�� ���ؼ�, 11��° ����� ���ʷ� �˻縦 �Ѵ�.
                     
					 btm ������ �� ������ �ѿ䰡 ��ġ�ؾ� �ϴ� �� ��ȣ��,
					 ���ʿ��� 11�̰� �ѿ䰡 �߰ߵǸ� -- ��Ų��. (�ѿ� 1�� �߽߰�, �� ������ �߰ߵǴ� �ѿ�� 10�� �࿡ ��ġ�ؾ� ��.)

					 11��° ����� �˻縦 �ϴµ� �ѿ䰡 �߰ߵ��� ���,
					 ���� i�� != btm �̶�� �� �ѿ��� �Ʒ��� ������ �ִٴ� ���̹Ƿ�,
					 i���� ���� btm�࿡ �� �ѿ並 �̵���Ų��.

4. �̹� map ���¿��� �Ͷ߸��� ������ �Ͼ�ٸ� ctn�� true�� �ٲپ� while���� ��ӵǰ� �Ѵ�.
   �Ͷ߸��� ������ �Ͼ�� �ʾҴٸ�, while���� Ż���� ������ �����ϰ� �ȴ�.
	   
*/
#include <iostream>
using namespace std;
	
char map[15][15];										// .�� R �� ǥ��Ǵ� �ѿ� ����
int dfs[15][15];										// �ѿ� �׷��� ������ ��ġ���� �׷� �̸��� ǥ��
int alreadyInGroup[100];								// �� �ѿ� �׷캰 �Ҽ� �ѿ� ����

int groupNum = 0;										// �׷� �̸��� ���� �� ���Ǵ� ����
bool ctn = true;										// �� �� �Ͷ߸� ����, �� �Ͷ߸� �� �ִ��� �˻����� ���� ����
int boomNum = 0;										// �� �� ���Ҵ���.

void Input() {
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			cin >> map[i][j];
		}
	}
}

void Print() {
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			printf("%c", map[i][j]);
		}
		cout << endl;
	}
	
}

int dir[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
void DFS(int x, int y, int cnt) {
	dfs[x][y] = groupNum;
	int tmpx, tmpy;

	for (int i = 0; i < 4; i++) {
		tmpx = x + dir[i][0];
		tmpy = y + dir[i][1];

		if (tmpx < 0 || tmpy < 0 || 12 <= tmpx || 6 <= tmpy) continue;
		if (map[tmpx][tmpy] == map[x][y] && dfs[tmpx][tmpy] == 0) {
			dfs[tmpx][tmpy] = dfs[x][y];
			DFS(tmpx, tmpy, cnt + 1);
		}
	}
}


void Init() {

	ctn = false;

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			dfs[i][j] = 0;
		}
	}

	for (int i = 0; i < groupNum; i++) {
		alreadyInGroup[i] = 0;
	}

	groupNum = 0;

}

void Down(int y) {
	int btm = 11; // ��Ұ� �����ϴ� ���� �Ʒ�
	for (int i = 11; i >= 0; i--) {
		if (map[i][y] != '.') {
			if (i != btm) { // �߷��� �����ؼ� �Ʒ��� �������� �Ѵ�
				map[btm][y] = map[i][y];
				map[i][y] = '.';
			}
			btm--;
		}
	}
}


void Boom(int groupName) {
	
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			if (dfs[i][j] == groupName) {
				map[i][j] = '.'; // dfs[i][j] == groupName�� �ֵ��� map���� �����

				/*cout << "�߷� ���� �� =====" << endl;
				Print();*/
				
				Down(j); // j ���� ���Ͽ� �߷� ����

				/*cout << "�߷� ���� �� =====" << endl;
				Print();*/
			}
		}
	}
}

int main() {

	Input();

	while (ctn) {

		Init();

		// DFS�� �׷��� ������
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 6; j++) {
				if (map[i][j] != '.' && dfs[i][j] == 0) {
					groupNum++;
					DFS(i, j, 0);
				}
			}
		}
		/*for (int i = 0; i < 12; i++) {        // ���� �׷��� Ȯ���ϴ� �ڵ�
			for (int j = 0; j < 6; j++) {
				cout << dfs[i][j];
			}
			cout << endl;
		}*/


		// ������� �׷� �ľ��ϱ�
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 6; j++) {
				if (dfs[i][j] != 0) {
					alreadyInGroup[dfs[i][j]]++;
				}
			}
		}


		for (int i = 1; i <= groupNum; i++) {
			// cout << i << "�� �׷� ����: " << alreadyInGroup[i] << endl;

			// ������ 4 �̻��� �׷� �Ͷ߸��� �Ʒ��� ����߸���
			if (alreadyInGroup[i] >= 4) {
				Boom(i);
				ctn = true;									// ���� �� �ִٴ� ǥ��
			}
		}
		// Print();

		if (ctn) {											// �̹� �ǿ��� ���� �� �ִٸ�, boomNum++
			boomNum++;
		}

	}

	cout << boomNum;

	return 0;
}