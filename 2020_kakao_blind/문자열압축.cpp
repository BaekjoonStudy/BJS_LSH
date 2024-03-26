#include <string>
#include <vector>
#include <iostream>

using namespace std;

int func(string s, int i) {
    int ret = s.size();
    
    int cnt = 1;
    for (int x = 0; x < s.size() - i; x += i) {
        if (s.substr(x,i) == s.substr(x+i,i)) {
            cnt++;
            ret -= i;
        }
        else {
            if (cnt != 1) {
                ret += to_string(cnt).size(); // 반복된 횟수 문자열 추가
                cnt = 1;
            }
        }
    }
    
    if (cnt != 1)
        ret += to_string(cnt).size(); // 반복된 횟수 문자열 추가

    return ret;
}

int solution(string s) {
    int answer = 1e9;
    
    for (int i = 1; i <= s.size(); i++) {
        answer = min(answer, func(s, i));
    }
    
    return answer;
}
