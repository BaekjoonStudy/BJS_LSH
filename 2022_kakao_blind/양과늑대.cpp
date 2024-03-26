#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> E[18], I;
int visited[18][18][18]; // [노드][양][늑대]
int max_ans = 0;

void func(int node, int sheep, int wolf) {
    if (node == 0) {
        max_ans = max(max_ans, sheep);
        // return;
    }
        
    for (auto next : E[node]) {
        if (I[next] == 0) { // 양
            if (visited[next][sheep+1][wolf] == 0) { // 방문하지 않았음
                I[next] = -1;
                visited[next][sheep+1][wolf] = 1;
                func(next, sheep+1, wolf);
                visited[next][sheep+1][wolf] = 0;
                I[next] = 0;
            }
        }
        else if (I[next] == 1) { // 늑대
            if (visited[next][sheep][wolf+1] == 0 && sheep > wolf+1) { // 방문하지 않았음
                I[next] = -1;
                visited[next][sheep][wolf+1] = 1;
                func(next, sheep, wolf+1);
                visited[next][sheep][wolf+1] = 0;
                I[next] = 1;
            }
        }
        else if (I[next] == -1) { // 아무것도 없음
            if (visited[next][sheep][wolf] == 0) { // 방문하지 않았음
                visited[next][sheep][wolf] = 1;
                func(next, sheep, wolf);
                visited[next][sheep][wolf] = 0;
            }
        }
    }
}

int solution(vector<int> info, vector<vector<int>> edges) {
    int answer = 0;
    
    I = info;
    for (auto edge : edges) {
        E[edge[0]].push_back(edge[1]);
        E[edge[1]].push_back(edge[0]);
    }
    
    I[0] = -1;
    visited[0][1][0] = 1;
    func(0,1,0);
    
    return max_ans;
}
