#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <iostream>

using namespace std;

pair<int,int> dir[4] = { {-1,0},{1,0},{0,-1},{0,1}};

bool isCheck(int r, int c) {
    if (r < 0 || c < 0 || r > 3 || c > 3)
        return false;
    return true;
}

pair<int,int> moveCtrl(vector<vector<int>> board, int r, int c, int d) {
    pair<int,int> p = {r,c};
    
    while (true) {
        int new_r = p.first + dir[d].first; int new_c = p.second + dir[d].second;
        if (isCheck(new_r, new_c) == false)
            break;
        p.first = new_r; p.second = new_c;
        if (board[p.first][p.second] != 0) // 카드
            break;
    }
    
    return p;
}

int bfs(vector<vector<int>> board, int r, int c, int x, int y) { // {r,c} -> {x,y} 까지 조작 횟수
    queue<tuple<int,int,int>> q;
    q.push({r,c,0});
    while (!q.empty()) {
        auto [cur_r, cur_c, ret] = q.front();
        q.pop();
        
        if (cur_r == x && cur_c == y)
            return ret;
        
        for (int i = 0; i < 4; i++) {
            pair<int,int> p = moveCtrl(board, cur_r, cur_c, i);
            if (p.first == cur_r && p.second == cur_c) // 좌표 변화 없음
                continue;
            q.push({p.first, p.second, ret+1});
        }
        
        for (int i = 0; i < 4; i++) {
            int new_r = cur_r + dir[i].first; int new_c = cur_c + dir[i].second;
            if (isCheck(new_r, new_c) == false)
                continue;
            q.push({new_r, new_c, ret+1});
        }
    }
    return 0;
}

int func(vector<vector<int>> board, int r, int c, int flipped) {
    int k = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            k += board[i][j];
    }
    if (k == 0)
        return 0;
    
    int ret = 1e9;
    if (flipped == 0) { // 이전에 뒤집은 카드가 없는 경우
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] == 0)
                    continue;
                int d = bfs(board, r, c, i, j);
                int tmp = board[i][j];
                board[i][j] = 0;
                ret = min(ret, d + 1 + func(board, i, j, tmp));
                board[i][j] = tmp;
            }
        }
        return ret;
    }
    
    else {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] != flipped)
                    continue;
                int d = bfs(board, r, c, i, j);
                board[i][j] = 0;
                return d + 1 + func(board, i, j, 0);
            }
        }
    }
}

int solution(vector<vector<int>> board, int r, int c) {
    int answer = 0;

    answer = func(board, r, c, 0);
    
    return answer;
}
