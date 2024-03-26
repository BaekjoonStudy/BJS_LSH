#include <string>
#include <vector>
#include <iostream>

using namespace std;

int board[51][51];

string func(int down, int left, int right, int up, string answer) {
    while (down--) 
        answer += 'd';
    while (left--) 
        answer += 'l';
    while (right--) 
        answer += 'r';
    while (up--) 
        answer += 'u';
    return answer;
}

string solution(int n, int m, int x, int y, int r, int c, int k) {
    string answer = "";
    int down = 0, left = 0, right = 0, up = 0;
    int row = r - x;
    int col = c - y;
    if (row < 0)
        up = -row;
    else
        down = row;
    if (col < 0)
        left = -col;
    else
        right = col;
    
    if ((down + left + right + up) > k)
        return "impossible";
    else if ((down + left + right + up) == k) {
        return func(down, left, right, up, answer);
    }
    else {
        int extra_move = k - (down + left + right + up); // 목적지로 이동하는데 필요한 이동을 뺀 남은 이동 수
        if (extra_move % 2 != 0)
            return "impossible";
        else {
            // 아래
            x += down; // 현재 위치 갱신
            if ((extra_move / 2) < (n - x)) {
                down += (extra_move / 2);
                up += (extra_move / 2);
                extra_move = 0;
            }
            else {
                down += (n - x);
                up += (n - x);
                extra_move -= (2 * (n - x));
            }
            answer = func(down, 0, 0, 0, answer);
            
            // 왼
            y -= left; // 현재 위치 갱신
            if ((extra_move / 2) < (y - 1)) {
                left += (extra_move / 2);
                right += (extra_move / 2);
                extra_move = 0;
            }
            else {
                left += (y - 1);
                right += (y - 1);
                extra_move -= (2 * (y - 1));
            }
            answer = func(0, left, 0, 0, answer);
            
            // 남은 이동 처리
            // 사전 순 "rl" -> "ud"
            for (int i = 0; i < extra_move / 2; i++) {
                if (y < m) // 오른쪽으로 갈 수 있다면
                    answer += "rl";
                else if (x > 1) // 위로 갈 수 있다면
                    answer += "ud";
            }

            answer = func(0, 0, right, up, answer);
        }
    }
        
    return answer;
}
