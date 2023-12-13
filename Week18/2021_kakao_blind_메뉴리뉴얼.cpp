#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

vector<string> c_size[11]; // 코스 수에 따라 정리, ex) c_size[2] = {"AB", "AC", "BD"} >> "AB","AC","BD"가 2개로 구성된 코스 중 가장 많이 나온 코스라는 의미
map<string, int> c_count; // 각 코스별 횟수 카운팅, ex) c_count["AB"] = 3 >> "AB"가 세 번 나왔다는 의미
int max_count[11]; // max_count[10] = 5 >> 코스 수가 10개인 코스 중 가장 많이 나온 코스는 5번 나온 코스라는 의미

bool comp(string a, string b) {
    int isbool = (a.size() <= b.size()) ? 0 : 1;
    if (isbool == 0) {
        for (int i = 0; i < a.size(); i++) {
            if (a[i] < b[i])
                return true;
            else if (a[i] > b[i])
                return false;
        }
        return true;
    }
    else {
        for (int i = 0; i < b.size(); i++) {
            if (a[i] < b[i])
                return true;
            else if (a[i] > b[i])
                return false;
        }
        return false;
    }
}

void dfs(string cur, vector<int> visit, string order, int i, int idx) {
    if (cur.size() == i) {
        c_count.insert({cur,0});
        c_count[cur]++;
        if (c_count[cur] > max_count[i]) {
            c_size[i].clear();
            c_size[i].push_back(cur);
            max_count[i] = c_count[cur];
        }
        else if (c_count[cur] == max_count[i]) {
            c_size[i].push_back(cur);
        }
    }
    
    for (int j = idx; j < order.size(); j++) { // AB와 BA처럼 중복되는 경우를 방지하기 위함
        if (visit[j] == 0) { 
            visit[j] = 1;
            dfs(cur+order[j], visit, order, i, j);
            visit[j] = 0;
        }
    }
}


void func(string order, vector<int> course) {
    for (auto i : course) {
        vector<int> visit(order.size(), 0);
        dfs("", visit, order, i, 0);
    }
}

vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;
    
    for (auto& o : orders) {
        sort(&o[0], &o[0]+o.size());
        func(o, course);
    }
    
    for (auto i : course) {
        for (auto set : c_size[i]) {
            if (c_count[set] >= 2)
                answer.push_back(set);
        }
    }

    sort(answer.begin(), answer.end(), comp);
    
    return answer;
}
