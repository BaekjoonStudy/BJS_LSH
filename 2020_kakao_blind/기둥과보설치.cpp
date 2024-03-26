#include <string>
#include <vector>
#include <iostream>

using namespace std;

int N;
pair<int,int> dir[9] = {{-1,-1},{0,-1},{1,-1},{-1,0},{0,0},{1,0},{-1,1},{0,1},{1,1}};
vector<vector<int>> board1, board2; // 각각 기둥과 보에 대한 정보를 저장

bool func1(int x, int y) { // 기둥 가능한지
    if (y != 0) { // 바닥이 아님
        if (y+1 > N) // 벽면을 벗어나는 경우
            return false;
        if (board1[x][y-1] != 1) { // 아래에 기둥이 없는 경우
            if (x == 0) {
                if (board2[x][y] != 1) // 아래에 보가 없는 경우
                    return false;
            }
            else {
                if (board2[x-1][y] != 1 && board2[x][y] != 1) // 아래에 보가 없는 경우
                    return false;
            }
        }
    }
    return true;
}

bool func2(int x, int y) { // 보 가능한지
    if (x+1 > N) // 벽면을 벗어나는 경우
        return false;
    if (board1[x][y-1] != 1 && board1[x+1][y-1] != 1) { // 아래에 기둥이 없는 경우
        if (x-1 >= 0 && x+1 < N) {
            if (board2[x-1][y] != 1 || board2[x+1][y] != 1) // 양쪽 동시에 보와 연결되지 않은 경우
                return false;
        }
        else // x-1이 0보다 작거나 x+1이 N보다 크거나 같다면 양쪽 동시에 보와 연결될 수 없음
            return false;
    }
    
    return true;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    vector<vector<int>> answer;
    
    N = n;
    board1.resize(n+1, vector<int>(n+1));
    board2.resize(n+1, vector<int>(n+1));
    vector<int> tmp;
    
    for (auto bf : build_frame) {
        int x = bf[0], y = bf[1], a = bf[2], b = bf[3];
        if (x < 0 || y < 0 || x > n || y > n) // 좌표가 벽면을 벗어나는 경우
            continue;
        if (b == 0) { // 삭제
            if (a == 0) { // 기둥
                board1[x][y] = 0;
                for (int i = 0; i < 9; i++) {
                    int new_x = x+dir[i].first; int new_y = y+dir[i].second;
                    if (new_x < 0 || new_y < 0 || new_x > n || new_y > n)
                        continue;
                    if (board1[new_x][new_y] == 1) { // 기둥
                        if (func1(new_x, new_y) == false) { 
                            board1[x][y] = 1;
                            continue;
                        }
                    }
                    if (board2[new_x][new_y] == 1) { // 보
                        if (func2(new_x, new_y) == false) { 
                            board1[x][y] = 1;
                            continue;
                        }
                    }
                }
            }
            else if (a == 1) { // 보
                board2[x][y] = 0;
                for (int i = 0; i < 9; i++) {
                    int new_x = x+dir[i].first; int new_y = y+dir[i].second;
                    if (new_x < 0 || new_y < 0 || new_x > n || new_y > n)
                        continue;
                    if (board1[new_x][new_y] == 1) { // 기둥
                        if (func1(new_x, new_y) == false) { 
                            board2[x][y] = 1;
                            continue;
                        }
                    }
                    if (board2[new_x][new_y] == 1) { // 보
                        if (func2(new_x, new_y) == false) { 
                            board2[x][y] = 1;
                            continue;
                        }
                    }
                }
            }
        }
        
        else if (b == 1) { // 설치
            if (a == 0) { // 기둥
                // cout << "기둥 : " << x << "," << y << "," << func1(x,y) << "\n";
                if (func1(x, y) == true)
                    board1[x][y] = 1;
            }
            
            else if (a == 1) { // 보
                // cout << "보 : " << x << "," << y << "," << func2(x,y) << "\n";
                if (func2(x, y) == true)
                    board2[x][y] = 1;
            }
        }
    }
    
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            tmp.clear();
            if (board1[i][j] == 1) {
                tmp.push_back(i);
                tmp.push_back(j);
                tmp.push_back(0);
                answer.push_back(tmp);
            }
            tmp.clear();
            if (board2[i][j] == 1) {
                tmp.push_back(i);
                tmp.push_back(j);
                tmp.push_back(1);
                answer.push_back(tmp);
            }
        }
    }
    
    return answer;
}
