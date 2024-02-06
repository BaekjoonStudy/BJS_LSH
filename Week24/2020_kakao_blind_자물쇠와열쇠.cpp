#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<vector<int>> k[4]; // 회전시킨 키들을 저장

vector<vector<int>> rotate(vector<vector<int>> key) { // 시계방향으로 90도 회전
    vector<vector<int>> ret;
    ret.resize(key[0].size(), vector<int>(key.size()));
    for (int j = 0; j < key[0].size(); j++) {
        for (int i = 0; i < key.size(); i++) {
            ret[j][i] = key[key.size()-i-1][j];
        }
    }

    return ret;
}

bool func(vector<vector<int>> key, vector<vector<int>> lock) {
    vector<vector<int>> board;
    int m = (key.size() - 1) * 2 + lock.size(); int n = (key[0].size() - 1) * 2 + lock[0].size();
    board.resize(m, vector<int>(n));
    for (int i = 0; i < lock.size(); i++) {
        for (int j = 0; j < lock[0].size(); j++) {
            board[i+key.size()-1][j+key[0].size()-1] = lock[i][j];
        }
    }
    
    vector<vector<int>> tmp = board;
    bool isBool;
    
    for (int x = 0; x < board.size() - key.size() + 1; x++) {
        for (int y = 0; y < board[0].size() - key[0].size() + 1; y++) {
            tmp = board;
            for (int i = 0; i < key.size(); i++) {
                for (int j = 0; j < key[0].size(); j++) {
                    tmp[x+i][y+j] += key[i][j];
                }
            }
            
            isBool = true;
            for (int i = 0; i < lock.size(); i++) {
                for (int j = 0; j < lock[0].size(); j++) {
                    if (tmp[i+key.size()-1][j+key[0].size()-1] != 1) {
                        isBool = false;
                        break;
                    }
                }
                if (isBool == false)
                    break;
            }
            if (isBool == true)
                return true;
            
        }
    }
    
    return false;
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    bool answer = true;
    
    k[0] = key;
    k[1] = rotate(k[0]);
    k[2] = rotate(k[1]);
    k[3] = rotate(k[2]);
    
    for (int i = 0; i < 4; i++) {
        answer = func(k[i], lock);
        if (answer == true)
            break;
    }
    
    return answer;
}
