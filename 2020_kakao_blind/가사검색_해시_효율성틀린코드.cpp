#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

unordered_map<string, int> m;

void func(string s) {
    string tmp = s;
    for (int i = 0; i < s.size(); i++) {
        tmp[i] = '?';
        m.insert({tmp,0});
        m[tmp]++;
    }
    tmp = s;
    for (int i = s.size()-1; i > 0; i--) {
        tmp[i] = '?';
        m.insert({tmp,0});
        m[tmp]++;
    }
}

vector<int> solution(vector<string> words, vector<string> queries) {
    vector<int> answer;
    
    for (auto w : words) {
        func(w);
    }
    
    for (auto q : queries) {
        answer.push_back(m[q]);
    }
    
    return answer;
}
