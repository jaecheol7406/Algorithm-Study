/*
���� key��
0, 0, 0
1, 0, 0
0, 1, 1

�̰� lock��
1, 1, 1
1, 1, 0
1, 0, 1
�̶��

board ����(60*60 ũ��)�� ���� lock�� ����
00000000000000000...
00000000000000000...
00111000000000000...
00110000000000000...
00101000000000000...
00000000000000000...
00000000000000000...

key�� (0, 0) ~ (4, 4)�� ���������� �ϰԲ� board�� ���� ��,
board�� lock�� ���� �������� 2 �Ǵ� 0�� �߰ߵ��� ������ true
*/
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int N, M;
vector<vector<int>> board(60, vector<int>(60, 0));
vector<vector<int>> backup(60, vector<int>(60, 0));

void Rotate(vector<vector<int>> &key) {
    vector<vector<int>> tmp(M, vector<int>(M, 0));
    
    for(int j=0; j<M; j++) {
        for(int i=0; i<M; i++) {
            tmp[j][i] = key[(M-1)-i][j];
        }
    }
    
    key = tmp;
}

bool Test() {
    for(int i=M-1; i<(M-1)+N; i++) {
        for(int j=M-1; j<(M-1)+N; j++) {
            if(board[i][j] == 0) return false;
            if(board[i][j] == 2) return false;
        }
    }
    return true;
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    N = lock.size();
    M = key.size();
    
    // board ����� lock ����
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            board[i+(M-1)][j+(M-1)] = lock[i][j];
            backup[i+(M-1)][j+(M-1)] = lock[i][j];
        }
    }
    // board ���
    /*for(int i=0; i<(M-1)*2+N; i++) {
        for(int j=0; j<(M-1)*2+N; j++) {
            cout << board[i][j];
        }
        cout << endl;
    }*/
    
    
    // key�� (0,0) ���ۿ������� (M-1) + (N-1)���۱��� �غ���
    // cout << (M-1) + (N-1);
    for(int r=0; r<4; r++) {
        Rotate(key);
        for(int rp=0; rp<= (M-1)+(N-1); rp++) {
            for(int cp=0; cp<= (M-1)+(N-1); cp++) {
                // cout << "rp:" << rp << " cp:" << cp << endl;
                board = backup; // �ʱ�ȭ
                
                /*cout << "�ʱ�ȭ ����:" << endl;
                // board ���
                for(int i=0; i<(M-1)*2+N; i++) {
                    for(int j=0; j<(M-1)*2+N; j++) {
                        cout << board[i][j];
                    }
                    cout << endl;
                }*/

                // key�� ��ġ �ű��
                for(int i=0; i<M; i++){
                    for(int j=0; j<M; j++) {
                        board[rp+i][cp+j] += key[i][j];
                    }
                }

                /*cout << "key ���� ��" << endl;
                // board ���
                for(int i=0; i<(M-1)*2+N; i++) {
                    for(int j=0; j<(M-1)*2+N; j++) {
                        cout << board[i][j];
                    }
                    cout << endl;
                }
                cout << "======" << endl;*/
                
                if(Test()) {
                    return true;
                }

            }
        }
    }
    
    return false;
}