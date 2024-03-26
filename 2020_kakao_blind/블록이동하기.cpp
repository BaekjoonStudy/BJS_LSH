#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <iostream>

using namespace std;

vector<vector<int>> B;
int visit[102][102][2];

bool is_bool(int row, int col) { // 보드를 벗어나는지 확인
    if (row >= 0 && row < B.size() && col >= 0 && col < B.size())
        return true;
    return false;
}

bool move_up(int shape, int row, int col) {
    if (shape == 0) { // - 꼴
        if (is_bool(row-1, col-1) && is_bool(row-1, col)) {
            if (B[row-1][col-1] == 0 && B[row-1][col] == 0) // 위 두칸 확인
                return true;
        }
    }
    else { // | 꼴
        if (is_bool(row-2, col)) {
            if (B[row-2][col] == 0) // 위 한칸 확인
                return true;
        }
    }
    return false;
}

bool move_down(int shape, int row, int col) {
    if (shape == 0) { // - 꼴
        if (is_bool(row+1, col-1) && is_bool(row+1, col)) {
            if (B[row+1][col-1] == 0 && B[row+1][col] == 0) // 아래 두칸 확인
                return true;
        }
    }
    else { // | 꼴
        if (is_bool(row+1, col)) {
            if (B[row+1][col] == 0) // 아래 한칸 확인
                return true;
        }
    }
    return false;
}

bool move_left(int shape, int row, int col) {
    if (shape == 0) { // - 꼴
        if (is_bool(row, col-2)) {
            if (B[row][col-2] == 0) // 왼쪽 한칸 확인
                return true;
        }
    }
    else { // | 꼴
        if (is_bool(row-1, col-1) && is_bool(row, col-1)) {
            if (B[row-1][col-1] == 0 && B[row][col-1] == 0) // 왼쪽 두칸 확인
                return true;
        }
    }
    return false;
}

bool move_right(int shape, int row, int col) {
    if (shape == 0) { // - 꼴
        if (is_bool(row, col+1)) {
            if (B[row][col+1] == 0) // 오른쪽 한칸 확인
                return true;
        }
    }
    else { // | 꼴
        if (is_bool(row-1, col+1) && is_bool(row, col+1)) {
            if (B[row-1][col+1] == 0 && B[row][col+1] == 0) // 오른쪽 두칸 확인
                return true;
        }
    }
    return false;
}


int bfs() {
    queue<tuple<int, int, int, int>> q; // {시간, 형태, 좌표}
    q.push({0, 0, 0, 1});
    
    int ret = -1;
    int row_tmp, col_tmp;
    while (!q.empty()) {
        int t = get<0>(q.front()); int shape = get<1>(q.front());
        int row = get<2>(q.front()); int col = get<3>(q.front());
        q.pop();
        // cout << t << "<" << shape << "<" << row << "<" << col << "\n";
        // visit[row][col][shape] = 1;
        if (row == B.size()-1 && col == B[0].size()-1) { // 도착
            ret = t;
            break;
        }
        
        // 이동
        if (move_up(shape, row, col) == true) {
            if (visit[row-1][col][shape] == 0) {
                visit[row-1][col][shape] = 1;
                q.push({t+1, shape, row-1, col});
            }  
        }
        
        if (move_down(shape, row, col) == true) {
            if (visit[row+1][col][shape] == 0) {
                visit[row+1][col][shape] = 1;
                q.push({t+1, shape, row+1, col});
            }
        }
        
        if (move_left(shape, row, col) == true) {
            if (visit[row][col-1][shape] == 0) {
                visit[row][col-1][shape] = 1;
                q.push({t+1, shape, row, col-1});
            }   
        }
        
        if (move_right(shape, row, col) == true) {
            if (visit[row][col+1][shape] == 0) {
                visit[row][col+1][shape] = 1;
                q.push({t+1, shape, row, col+1});
            }  
        }
        
        // 회전
        int row_axis, col_axis;
        if (shape == 0) { // - 꼴
            // 왼쪽 축
            row_axis = row; col_axis = col - 1;
            if (is_bool(row_axis-1, col_axis) && is_bool(row_axis-1, col_axis+1)) { // 위로 회전
                if (visit[row_axis][col_axis][1] == 0 && B[row_axis-1][col_axis] == 0
                    && B[row_axis-1][col_axis+1] == 0) { // 방문 여부, 회전 가능한지 확인
                    visit[row_axis][col_axis][1] = 1;
                    q.push({t+1, 1, row_axis, col_axis});
                }
            }
            
            if (is_bool(row_axis+1, col_axis) && is_bool(row_axis+1, col_axis+1)) { // 아래로 회전
                if (visit[row_axis+1][col_axis][1] == 0 && B[row_axis+1][col_axis] == 0
                    && B[row_axis+1][col_axis+1] == 0) { // 방문 여부, 회전 가능한지 확인
                    visit[row_axis+1][col_axis][1] = 1;
                    q.push({t+1, 1, row_axis+1, col_axis});
                }
            }
            
            // 오른쪽 축
            row_axis = row; col_axis = col;
            if (is_bool(row_axis-1, col_axis-1) && is_bool(row_axis-1, col_axis)) { // 위로 회전
                if (visit[row_axis][col_axis][1] == 0 && B[row_axis-1][col_axis-1] == 0
                    && B[row_axis-1][col_axis] == 0) { // 방문 여부, 회전 가능한지 확인
                    visit[row_axis][col_axis][1] = 1;
                    q.push({t+1, 1, row_axis, col_axis});
                }
            }
            
            if (is_bool(row_axis+1, col_axis-1) && is_bool(row_axis+1, col_axis)) { // 아래로 회전
                if (visit[row_axis+1][col_axis][1] == 0 && B[row_axis+1][col_axis-1] == 0
                    && B[row_axis+1][col_axis] == 0) { // 방문 여부, 회전 가능한지 확인
                    visit[row_axis+1][col_axis][1] = 1;
                    q.push({t+1, 1, row_axis+1, col_axis});
                }
            }
        }
        
        else { // | 꼴
            // 위쪽 축
            row_axis = row-1; col_axis = col;
            if (is_bool(row_axis, col_axis-1) && is_bool(row_axis+1, col_axis-1)) { // 왼쪽으로 회전
                if (visit[row_axis][col_axis][0] == 0 && B[row_axis][col_axis-1] == 0
                    && B[row_axis+1][col_axis-1] == 0) { // 방문 여부, 회전 가능한지 확인
                    visit[row_axis][col_axis][0] = 1;
                    q.push({t+1, 0, row_axis, col_axis});
                }
            }
            
            if (is_bool(row_axis, col_axis+1) && is_bool(row_axis+1, col_axis+1)) { // 오른쪽으로 회전
                if (visit[row_axis][col_axis+1][0] == 0 && B[row_axis][col_axis+1] == 0
                    && B[row_axis+1][col_axis+1] == 0) { // 방문 여부, 회전 가능한지 확인
                    visit[row_axis][col_axis+1][0] = 1;
                    q.push({t+1, 0, row_axis, col_axis+1});
                }
            }
            
            // 아래쪽 축
            row_axis = row; col_axis = col;
            if (is_bool(row_axis-1, col_axis-1) && is_bool(row_axis, col_axis-1)) { // 왼쪽으로 회전
                if (visit[row_axis][col_axis][0] == 0 && B[row_axis-1][col_axis-1] == 0
                    && B[row_axis][col_axis-1] == 0) { // 방문 여부, 회전 가능한지 확인
                    visit[row_axis][col_axis][0] = 1;
                    q.push({t+1, 0, row_axis, col_axis});
                }
            }
            
            if (is_bool(row_axis-1, col_axis+1) && is_bool(row_axis, col_axis+1)) { // 오른쪽으로 회전
                if (visit[row_axis][col_axis+1][0] == 0 && B[row_axis-1][col_axis+1] == 0
                    && B[row_axis][col_axis+1] == 0) { // 방문 여부, 회전 가능한지 확인
                    visit[row_axis][col_axis+1][0] = 1;
                    q.push({t+1, 0, row_axis, col_axis+1});
                }
            }
        }
    }
    return ret;
}


int solution(vector<vector<int>> board) {
    int answer = 0;
    B = board;
    return bfs();
}
