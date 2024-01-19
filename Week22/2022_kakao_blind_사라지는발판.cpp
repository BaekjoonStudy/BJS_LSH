#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<vector<int>> b;
pair<int,int> dir[4] = {{-1,0},{1,0},{0,-1},{0,1}};

bool check(int loc1, int loc2) {
    if (loc1 >= 0 && loc2 >= 0 && loc1 < b.size() && loc2 < b[0].size()) {
        if (b[loc1][loc2] == 1)
            return true;
    }
    return false;
}

int func(int aloc1, int aloc2, int bloc1, int bloc2) {
    if (b[aloc1][aloc2] == 0)
        return 0;
    
    int ret = 0;
    for (int i = 0; i < 4; i++) {
        int new_loc1 = aloc1 + dir[i].first;
        int new_loc2 = aloc2 + dir[i].second;
        if (check(new_loc1, new_loc2) == false)
            continue;
        b[aloc1][aloc2] = 0;
        int tmp = func(bloc1, bloc2, new_loc1, new_loc2) + 1;
        b[aloc1][aloc2] = 1;
        
        if (ret%2 == 0 && tmp%2 == 0) { // 그 전 결과들 전부 짐, i 방향으로 움직인 결과도 짐
            // 가능한 오래 버텨야함 => 최댓값으로 업데이트
            ret = max(tmp, ret);
        }
        else if (ret%2 == 0 && tmp%2 == 1) { // 그 전 결과들 전부 짐, i 방향으로 움직인 결과 이김
            // 이겼을 때의 움직인 횟수로 업데이트
            ret = tmp;
        }
        else if (ret%2 == 1 && tmp%2 == 1) { // 그 전 결과들 중 이긴 경우 존재함, i 방향으로 움직인 결과 이김
            // 가능한 빨리 끝내야함 => 최솟값으로 업데이트
            ret = min(tmp, ret);
        }
        // 그 전 결과들 중 이긴 경우 존재하는데 i 방향으로 움직여서 졌다면 업데이트 필요 없음
    }
    return ret;
}

int solution(vector<vector<int>> board, vector<int> aloc, vector<int> bloc) {
    int answer = -1;
    
    b = board;
    answer = func(aloc[0], aloc[1], bloc[0], bloc[1]);
    
    return answer;
}
