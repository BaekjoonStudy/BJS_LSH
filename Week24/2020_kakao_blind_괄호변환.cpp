#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

string flip(string u) {
    string ret = "";
    for (int i = 1; i < u.size() - 1; i++) {
        if (u[i] == '(')
            ret += ')';
        else 
            ret += '(';
    }
    return ret;
}

string func(string p) {
    string u = "", v = "";
    if (p == "")
        return "";
    
    int cnt = 0, isBool = 0;
    for (int i = 0; i < p.size(); i++) {
        if (p[i] == '(')
            cnt++;
        else
            cnt--;
        
        if (cnt < 0)
            isBool = 1;
        
        if (cnt == 0) { // 균형잡힌 괄호 문자열 완성
            u = p.substr(0,i+1);
            v = p.substr(i+1);
            if (isBool == 1) // 올바른 괄호 문자열 아님
                return "(" + func(v) + ")" + flip(u);
            return u + func(v);
        }
    }
    return "";
}

string solution(string p) {
    string answer = "";
    
    answer = func(p);
   
    return answer;
}
