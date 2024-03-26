#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

vector<pair<int, int>> graph[50001]; // 걸리는시간, 다음지점
int G[50001], S[50001];

vector<int> func(int start, int n) { // 다익스트라
    pair<int,int> ret;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> table(n+1, 1e9);
    
    pq.push({ 0, start });
    table[start] = 0;

    while (!pq.empty()) {
        int cur = pq.top().second;
        int intensity = pq.top().first;
        pq.pop();
        
        if (S[cur] == 1) { // 산봉우리
            // ret = {intensity, cur};
            break;
        }
        
        for (auto next : graph[cur]) {
            if (G[next.second] == 1) // 출입구
                continue;

            if (table[next.second] <= max(intensity, next.first))
                continue;

            table[next.second] = max(intensity, next.first);
            pq.push({ table[next.second], next.second });
        }
    }
    return table;
}

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
    vector<int> answer(2, 1e9);
    
    for (auto p : paths) {
        graph[p[0]].push_back({ p[2],p[1] });
        graph[p[1]].push_back({ p[2],p[0] });
    }
    
    for (auto g : gates) {
        G[g] = 1;
    }

    for (auto s : summits) {
        S[s] = 1;
    }
    
    for (auto g: gates) {
        vector<int> table = func(g,n);
        for(auto s : summits) {
            if (answer[1] > table[s]) {
                answer[0] = s;
                answer[1] = table[s];
            }
            else if (answer[1] == table[s] && answer[0] > s)
                answer[0] = s;      
        }
    }

    return answer;
}
