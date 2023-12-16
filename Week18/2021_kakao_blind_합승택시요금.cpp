#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

int INF = 1e7;
vector<int> table(201,INF), table_s(201,INF), table_a(201,INF), table_b(201,INF);
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
vector<pair<int,int>> graph[201];

void func(int s) { // 다익스트라
    pq = priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>>(); // clear
    table[s] = 0;
    pq.push({0, s});
    
    while (!pq.empty()) {
        int d = pq.top().first;
        int cur = pq.top().second;
        pq.pop();
        if (table[cur] != d)
            continue;
        
        for (auto next : graph[cur]) {
            if (table[cur] + next.first >= table[next.second]) 
                continue;
            table[next.second] = table[cur] + next.first;
            pq.push({table[cur] + next.first, next.second});
        }
    }
}

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer;
    for (auto f : fares) {
        graph[f[0]].push_back({f[2],f[1]});
        graph[f[1]].push_back({f[2],f[0]});
    }
    
    func(s);
    table_s = table;
    fill(&table[0], &table[0] + n + 1, INF);
    
    func(a);
    table_a = table;
    fill(&table[0], &table[0] + n + 1, INF);
    
    func(b);
    table_b = table;
    
    answer = table_s[1] + table_a[1] + table_b[1];
    for (int i = 2; i <= n; i++) 
        answer = min(answer, table_s[i] + table_a[i] + table_b[i]);

    return answer;
}
