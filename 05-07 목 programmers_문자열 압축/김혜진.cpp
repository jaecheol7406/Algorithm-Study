/*
주의점: s 길이가 1인 경우 예외처리 필요

문자열을 1개 ~ 문자열길이/2 개로 나누는 경우를 모두 해 본다
*/
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(string s) {    
    int minLength = 1000;
    
    string answer = "";
    string lastString = "";
    
    bool matched = true;
    int casNum=1;
    
    if(s.size() == 1) return 1; // s 길이가 1인 경우 예외처리

    for(int t=1; t<=s.size()/2; t++) {
        answer = "";
        casNum = 1;
        lastString = "";
        
        for(int i=0; i<t; i++) { // 제일 처음부분
            lastString += s[i];
        }    
        
        for(int i=t; i<s.size(); i+=t) { // i: 매번 시작점
            matched = true;
            
            for(int j=i; j<i+t; j++) {
                if(j >= s.size()) {  // 마지막 구간의 길이가 t가 안 될 경우
                    matched = false;
                    break;
                }
                
                if(lastString[j-i] != s[j]) {
                    matched = false;
                    break;
                }
            }
            
            if(matched) {
                casNum++;
            }
            else {
                if(casNum > 1)
                    answer += to_string(casNum);
                answer += lastString;
                casNum = 1;
                
                lastString="";
                for(int j=i; j<i+t; j++) {
                     if(j >= s.size()) break; // 마지막 구간의 길이가 t가 안 될 경우
                    lastString += s[j];
                }
            }
        }
        
		// 마지막 구간에 대한 처리
        if(casNum > 1)
                answer += to_string(casNum);
            answer += lastString;
        
        if(minLength > answer.size()) minLength = answer.size();
    }
    
    
    return minLength;
}