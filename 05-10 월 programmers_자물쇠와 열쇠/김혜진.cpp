/*
반례: key [[0, 0, 0], [0, 0, 0], [1, 0, 0]]
lock [[1, 1, 1, 0], [1, 1, 1, 1], [1, 1, 1, 1], [1, 1, 1, 1]]
answer: true
 
안 되는 이유: 접근방법 자체가 잘못됨 
현재 오른쪽/아래쪽으로 key가 뻗쳐나가는 걸 처리하지 못함 (key의 크기를 M*M까지로 제한해버림)
Key가 20*20일 경우 Key는 약 60*60까지의 경우가 가능함
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

bool Test(int M, int N, vector<vector<int>> lock) { // M != N인 경우를 생각해야 함
    for(int i=0; i<N; i++) {
        for(int j=0; j<N;j++) {
            /*if(lock[i][j] == 0 && thisKey[i][j] != 1 ) // 홈0인데 돌기1가 아니다
                return false;
            if(lock[i][j] == 1 && thisKey[i][j] == 1) // 돌기1인데 돌기1이다
                return false;*/
            if(lock[i][j] == 0) { // 홈인데
                if(i>=M || j>=M) return false; // key가 그 범위까지 못 간다
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
    
    // 시작점 정하기
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
            
            
            // 돌려보기
            for(int gakdo=0; gakdo<=270; gakdo += 90) {
                Round(M, key, gakdo);
                /*cout << gakdo << "도로 회전 결과" << endl;
                PrintThis(M);*/
                if(Test(M, lock.size(), lock)) return true;
            }
        }
    }
    
    return false;
}