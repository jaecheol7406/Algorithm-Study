/*
���α׷��ӽ� : �ڹ���� ����
���� ���� : ����Ž��


1. (Ű�� ������ �� �ذ� �ڹ����� ���� �� ��) ���� (Ű�� ���� ������ �ڹ����� ������ �� ��)���� ���纸�� ��� ����� ���� Ž���ؾ���.
2. �̸� ����, 1���� ������ �� �ִ� ���ο� 2���� ���͸� �Ҵ��ϰ�, ���⿡ �ڹ����� ������ �Է½�Ų��. �ڹ����� ��ǥ�� ���� ��ǥ���� Ű�� size��ŭ ����������
3. Ű�� 4�� rotate(90�� ȸ��)�ϴ� ��츦 ��� Ž��.
*/
#include <string>
#include <vector>
#include <iostream>
using namespace std;
int boardSize, keySize, lockSize;
vector<vector<int>> board;

bool match(vector<vector<int>>& key, vector<vector<int>> board, int x, int y) {
    for (int i = x; i < x + keySize; i++) {
        for (int j = y; j < y + keySize; j++) {
            board[i][j] += key[i - x][j - y];
            if (board[i][j] == 2)
                return false;
        }
    }
    for (int i = keySize - 1; i < keySize + lockSize - 1; i++) {
        for (int j = keySize - 1; j < keySize + lockSize - 1; j++) {
            if (board[i][j] == 0)
                return false;
        }
    }
    return true;
}
void rotate(vector<vector<int>>& key) {
    vector<vector<int>> tmp(keySize, vector<int>(keySize, 0));
    for (int i = 0; i < keySize; i++) {
        for (int j = 0; j < keySize; j++) {
            tmp[i][j] = key[j][keySize - i - 1];
        }
    }
    key = tmp;
}
bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    bool answer = true;
    keySize = key.size();
    lockSize = lock.size();
    boardSize = lockSize + (keySize - 1) * 2;
    vector<vector<int>> board(boardSize, vector<int>(boardSize, 0));

    for (int i = keySize - 1; i < keySize + lockSize - 1; i++) {
        for (int j = keySize - 1; j < keySize + lockSize - 1; j++) {
            board[i][j] = lock[i - keySize + 1][j - keySize + 1];
        }
    }
    for (int r = 0; r < 4; r++) {
        for (int i = 0; i < keySize + lockSize - 1; i++) {
            for (int j = 0; j < keySize + lockSize - 1; j++) {
                if (match(key, board, i, j)) {
                    return true;
                }
            }
        }
        rotate(key);
    }
    return false;
}