#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

vector<vector<int>> solution(vector<vector<int>> rc, vector<string> operations) { 
    int r = rc.size(), c = rc[0].size();
    deque<int> col1, col2;
    int idx = 0; // 맨 위 행 인덱스
    for (auto r : rc) {
        col1.push_back(r[0]);
        col2.push_back(r[c-1]);
    }
    
    deque<int> rows[r];
    for(int i = 0; i < r; i++)
        for(int j = 1; j <= c-2; j++)
            rows[i].push_back(rc[i][j]);
    
    for (auto o : operations) {
        if (o[0] == 'R') { // Rotate
            rows[idx].push_front(col1.front());
            col1.pop_front();
            
            col2.push_front(rows[idx].back());
            rows[idx].pop_back();
            
            rows[(idx+r-1)%r].push_back(col2.back());
            col2.pop_back();
            
            col1.push_back(rows[(idx+r-1)%r].front());
            rows[(idx+r-1)%r].pop_front();
        }
        else { // ShiftRow
            col1.push_front(col1.back());
            col1.pop_back();
            col2.push_front(col2.back());
            col2.pop_back();
            
            idx = (idx == 0) ? r-1 : idx-1;
        }
    }
    
    vector<vector<int>> answer(r, vector<int>(c));
    for(int i = 0; i < r; i++){
        answer[i][0] = col1[i];
        for(int j = 1; j <= c-2; j++)
            answer[i][j] = rows[(i + idx) % r][j-1];
        answer[i][c-1] = col2[i];
    }

    return answer;
}
