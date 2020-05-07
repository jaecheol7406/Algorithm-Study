#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int solution(string s) {
    int len = s.size();
    int answer = len;
    for (int i = 1; i <= len / 2; i++) {
        string comp = s.substr(0, i);
        string result = "";
        int cnt = 1;
        int j;
        for (j = i; j <= len; j += i) {
            if (s.substr(j, i) == comp) {
                cnt++;
            }
            else {
                if (cnt == 1) {
                    result += comp;
                }
                else {
                    result += to_string(cnt) + comp;
                }
                comp = s.substr(j, i);
                if (comp.size() < i)
                    result += comp;
                cnt = 1;
            }
        }
        answer = min(answer, (int)result.size());
    }

    return answer;
}