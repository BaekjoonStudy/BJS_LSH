#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

deque<int> col1, col2; // 맨 왼쪽 열, 맨 오른쪽 열을 열 기준으로 저장
deque<deque<int>> row;  // 맨 왼쪽 열과 맨 오른쪽 열을 뺀 가운데 열을 행 기준으로 저장

vector<vector<int>> solution(vector<vector<int>> rc, vector<string> operations) {
    vector<vector<int>> answer;
    
    deque<int> dq;
    for (auto x : rc) {
        dq.clear();
        for (int i = 0; i < x.size(); i++) {
            if (i == 0)
                col1.push_back(x[i]);
            else if (i == x.size() - 1)
                col2.push_back(x[i]);
            else
                dq.push_back(x[i]);
        }
        row.push_back(dq);
    }
    
//     for (auto x : row) {
//         for (auto y : x) {
//             cout << y << " ";
//         }
//         cout << "\n";
//     }
    
//     for (auto x : col1) {
//         cout << x << " ";
//     }
//     cout << "\n";
        
//     for (auto x : col2) {
//         cout << x << " ";
//     }
//     cout << "\n";
        

    int top = 0; // 맨 위 row를 가리키는 인덱스
    int bottom = row.size() - 1;
    for (auto o : operations) {
        if (o == "ShiftRow") {
            col1.push_front(col1.back());
            col1.pop_back();
            col2.push_front(col2.back());
            col2.pop_back();
            top = (top == 0) ? (row.size() - 1) : (top - 1);
            bottom = (bottom == 0) ? (row.size() - 1) : (bottom - 1);
            // int idx = top;
            // cout << "ShiftRow\n";
            // for (int i = 0; i < row.size(); i++) {
            //     cout << col1[i] << " ";
            //     for (auto x : row[idx]) {
            //         cout << x << " ";
            //     }
            //     cout << col2[i] << "\n";
            //     idx = (idx + 1) % row.size();
            // }
        }
        else {
            row[top].push_front(col1.front());
            col1.pop_front();
            
            col2.push_front(row[top].back());
            row[top].pop_back();
            
            row[bottom].push_back(col2.back());
            col2.pop_back();
            
            col1.push_back(row[bottom].front());
            row[bottom].pop_front();
            // int idx = top;
            // cout << "Rotate\n";
            // for (int i = 0; i < row.size(); i++) {
            //     cout << col1[i] << " ";
            //     for (auto x : row[idx]) {
            //         cout << x << " ";
            //     }
            //     cout << col2[i] << "\n";
            //     idx = (idx + 1) % row.size();
            // }
        }
    }
    
    int idx = top;
    vector<int> v;
    for (int i = 0; i < row.size(); i++) {
        v.clear();
        v.push_back(col1[i]);
        for (auto x : row[idx]) {
            v.push_back(x);
        }
        v.push_back(col2[i]);
        idx = (idx + 1) % row.size();
        answer.push_back(v);
    }
    
    return answer;
}
