#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int N;
vector<int> W, visit;
vector<vector<int>> D;


bool check() { // 모두 점검했는지 확인
    for (auto w : W) {
        if (visit[w] == 0)
            return false;
    }
    return true;
}

int exam(int start, int dist) { // 점검
    int idx = start;
    for (int i = 0; i <= dist; i++) {
        visit[idx] = 1;
        idx = (idx + 1) < N ? (idx+1) : 0;
    }
    idx = lower_bound(W.begin(), W.end(), idx) - W.begin(); // 다음 취약점 위치
    if (idx == W.size())
        idx = 0;
    return W[idx];
}

int solution(int n, vector<int> weak, vector<int> dist) {
    int answer = 1e9;
    
    do {
		D.push_back(dist);
	} while (next_permutation(dist.begin(), dist.end())); // 순열생성
    
    N = n; W = weak;
    visit.resize(n);
    
    int tmp, start;
    for (auto w : weak) {
        for (auto x : D) {
            // 초기화
            tmp = 0;
            start = w;
            visit.clear();
            visit.resize(n);
            
            for (auto y : x) {
                tmp++; // 투입인원 카운팅
                start = exam(start, y);
                if (check() == true) { // 모두 점검
                    answer = min(answer, tmp);
                    break;
                }
            }
        }
    }
    
    if (answer == 1e9)
        answer = -1;
    return answer;
}
