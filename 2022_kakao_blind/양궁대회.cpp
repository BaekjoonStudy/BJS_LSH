#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> answer(1, -1);
int max_diff = 0;

bool comp(vector<int> ryan) { // 가장 낮은 점수를 더 많이 맞힌 경우를 return하기 위함
    for(int i = 10; i >= 0; i--) {
        if(ryan[i] > answer[i]) return true;
        else if (ryan[i] < answer[i]) return false;
    }
}

void score(vector<int> ryan, vector<int> apeach) {
    int score_r = 0, score_a = 0, diff;
    for (int i = 0; i < 11; i++) {
        if (ryan[i] > apeach[i]) // 라이언 승
            score_r += (10-i);
        else if(apeach[i] > 0) // 어피치 승
            score_a += (10-i);
    }
    
    diff = score_r - score_a;
    if (diff > 0 && diff >= max_diff) {
        if (diff == max_diff && comp(ryan) == false) return;
        max_diff = diff;
        answer = ryan;
    }
}

void func(int k, int arrow, vector<int> ryan, vector<int> apeach) {
    if (k == 11 || arrow == 0) {
        ryan[10] = arrow;
        score(ryan, apeach);
        ryan[10] = 0;
        return;
    }
    
    if (apeach[k] < arrow) { // k점에 어피치가 맞춘 화살 수보다 라이언의 남은 화살 수가 더 많다면
        ryan[k] = apeach[k] + 1;
        func(k+1, arrow-apeach[k]-1, ryan, apeach);
        ryan[k] = 0;
    }
    func(k+1, arrow, ryan, apeach); // k점에 라이언이 화살을 안 쏜 경우
}

vector<int> solution(int n, vector<int> info) {
    vector<int> ryan(11, 0);
    
    func(0, n, ryan, info);
    
    return answer;
}
