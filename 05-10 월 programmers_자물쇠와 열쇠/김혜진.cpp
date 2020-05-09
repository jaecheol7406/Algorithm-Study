/*
�ݷ�: key [[0, 0, 0], [0, 0, 0], [1, 0, 0]]
lock [[1, 1, 1, 0], [1, 1, 1, 1], [1, 1, 1, 1], [1, 1, 1, 1]]
answer: true
 
�� �Ǵ� ����: ���ٹ�� ��ü�� �߸��� 
���� ������/�Ʒ������� key�� ���ĳ����� �� ó������ ���� (key�� ũ�⸦ M*M������ �����ع���)
Key�� 20*20�� ��� Key�� �� 60*60������ ��찡 ������
*/
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int posKey[20][20];
int thisKey[20][20];

void InitPos () {
    for(int i=0; i<20; i++) {
        for(int j=0; j<20; j++) {
            posKey[i][j] = 0;
        }
    }
}

void InitThis () {
    for(int i=0; i<20; i++) {
        for(int j=0; j<20; j++) {
            thisKey[i][j] = 0;
        }
    }
}

void PrintPos(int M) {
    for(int i=0; i<M; i++) {
        for(int j=0; j<M; j++) {
            cout << posKey[i][j];
        }
        cout << endl;
    }
}

void PrintThis(int M) {
    for(int i=0; i<M; i++) {
        for(int j=0; j<M; j++) {
            cout << thisKey[i][j];
        }
        cout << endl;
    }
}

void Round(int M, vector<vector<int>> key, int gakdo) {
    if(gakdo == 90) {
        for(int j=0; j<M; j++) {
            for(int i=0; i<M; i++) {
                thisKey[j][i] = posKey[(M-1)-i][j];
            }
        }
    }
    else if(gakdo == 180) {
        for(int j=0; j<M; j++) {
            for(int i=0; i<M; i++) {
                thisKey[i][j] = posKey[(M-1)-i][(M-1)-j];
            }
        }
    }
    else if(gakdo == 270) {
        for(int j=0; j<M; j++) {
             for(int i=0; i<M; i++) {
                thisKey[j][i] = posKey[i][(M-1)-j];
            }
        }
    }
    else if(gakdo == 0) {
        for(int i=0; i<M; i++) {
            for(int j=0; j<M; j++) {
                thisKey[i][j] = posKey[i][j];
            }
        }
    }
}

bool Test(int M, int N, vector<vector<int>> lock) { // M != N�� ��츦 �����ؾ� ��
    for(int i=0; i<N; i++) {
        for(int j=0; j<N;j++) {
            /*if(lock[i][j] == 0 && thisKey[i][j] != 1 ) // Ȩ0�ε� ����1�� �ƴϴ�
                return false;
            if(lock[i][j] == 1 && thisKey[i][j] == 1) // ����1�ε� ����1�̴�
                return false;*/
            if(lock[i][j] == 0) { // Ȩ�ε�
                if(i>=M || j>=M) return false; // key�� �� �������� �� ����
                if(thisKey[i][j] != 1) return false;
            }
            else if(lock[i][j] == 1) {
                if(i>=M || j>=M) continue;
                if(thisKey[i][j] == 1) return false;
            }
        }
    }
    
    return true;
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    int M=key.size();
    
    int ridx = 0;
    int cidx = 0;
    
    // ������ ���ϱ�
    for(int rp = -(M-1); rp <= (M-1); rp++) {
        for(int cp = -(M-1); cp <= (M-1); cp++) {
            // cout << "rp: " << rp << " cp: " << cp << endl;
            ridx = 0;
            InitPos();
            
            for(int i=0; i<M; i++) {
                ridx = i + rp;
                if(ridx<0 || ridx>=M) continue;
                
                cidx = 0;
                for(int j=0; j<M; j++) {
                    cidx = j + cp;
                    if(cidx<0 || cidx>=M) continue;
                    
                    posKey[i][j] = key[ridx][cidx];
                    
                }
                
            }
            
            
            // ��������
            for(int gakdo=0; gakdo<=270; gakdo += 90) {
                Round(M, key, gakdo);
                /*cout << gakdo << "���� ȸ�� ���" << endl;
                PrintThis(M);*/
                if(Test(M, lock.size(), lock)) return true;
            }
        }
    }
    
    return false;
}