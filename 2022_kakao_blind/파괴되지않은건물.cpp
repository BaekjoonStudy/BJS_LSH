#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(vector<vector<int>> board, vector<vector<int>> skill) {
    int answer = 0;
    vector<vector<int>> cumsum(board.size()+1, vector<int>(board[0].size()+1, 0));
    
    for (auto s : skill) {
        int type = s[0], r1 = s[1], c1 = s[2], r2 = s[3], c2 = s[4], degree = s[5];
        if (type == 1) // 공격
            degree *= -1;

        cumsum[r1][c1] += degree;
        cumsum[r2+1][c2+1] += degree;
        cumsum[r1][c2+1] -= degree;
        cumsum[r2+1][c1] -= degree;
    }
    
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            cumsum[i][j + 1] += cumsum[i][j];
        }
    }

    for (int j = 0; j < board[0].size(); j++) {
        for (int i = 0; i < board.size(); i++) {
            cumsum[i + 1][j] += cumsum[i][j];
        }
    }
    
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            if (board[i][j] + cumsum[i][j] > 0) // 안무너짐
                answer++;
        }
    }
    
    return answer;
}
