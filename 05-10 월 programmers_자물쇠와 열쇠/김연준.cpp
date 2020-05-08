/*
프로그래머스 : 자물쇠와 열쇠
문제 유형 : 완전탐색


1. (키의 오른쪽 맨 밑과 자물쇠의 왼쪽 맨 위) 부터 (키의 왼쪽 맨위와 자물쇠의 오른쪽 맨 밑)까지 맞춰보는 모든 경우의 수를 탐색해야함.
2. 이를 위해, 1번을 수행할 수 있는 새로운 2차원 벡터를 할당하고, 여기에 자물쇠의 값들을 입력시킨다. 자물쇠의 좌표는 기존 좌표에서 키의 size만큼 움직여야함
3. 키를 4번 rotate(90도 회전)하는 경우를 모두 탐색.
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