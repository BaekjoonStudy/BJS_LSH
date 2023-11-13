#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

vector<int> E[20001]; // 간선 저장
int visited[20001]; // 방문체크, visited[3] = 2 라면 3번 노드는 1번 노드로부터 2만큼 떨어졌다는 뜻
queue<int> q;

int solution(int n, vector<vector<int>> edge) {
    int answer = 0;
    
    for (auto x : edge) {
        E[x[0]].push_back(x[1]);
        E[x[1]].push_back(x[0]);
    }
    
    visited[1] = 1;
    for (auto x : E[1]) {
        q.push(x);
        visited[x] = 1;
    }
    
    int max_len = 1; // 1번 노드로부터 가장 멀리 떨어진 거리를 저장
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (auto x : E[cur]) {
            if (visited[x] == 0) {// 방문한적이 없다면
                q.push(x);
                visited[x] = visited[cur] + 1;
                if (max_len < visited[x]) { // 거리가 업데이트되면
                    answer = 1; // 가장 멀리 떨어지는 노드 수를 1로 초기화
                    max_len = visited[x];
                }
                else if (max_len == visited[x]) // 거리가 max와 같다면
                    answer++;
            }
        }
    }
    
    return answer;
}
