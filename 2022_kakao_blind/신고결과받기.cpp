#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    vector<int> answer(id_list.size(), 0);
    vector<vector<int>> rep(id_list.size(), vector<int>(id_list.size(), 0));
    map<string,int> index;
    
    for (int i = 0; i < id_list.size(); i++)
        index[id_list[i]] = i;
    
    for (auto r : report) {
        string name1 = "", name2 = "", tmp = "";
        for (auto s : r) {
            if (s == ' ') {
                name1 = tmp;
                tmp = "";
            }
            else
                tmp += s;
        }
        name2 = tmp;
        int idx1 = index[name1], idx2 = index[name2];
        rep[idx2][idx1] = 1;
    }
    
    int sum = 0;
    vector<int> tmp_idx;
    for (int i = 0; i < id_list.size(); i++) {
        sum = 0;
        tmp_idx.clear();
        for (int j = 0; j < id_list.size(); j++) {
            if (rep[i][j] == 1)
                tmp_idx.push_back(j); // 신고한 유저 저장
            sum += rep[i][j]; // 신고당한 횟수 갱신
        }
        if (sum >= k) { // 정지
            for (auto idx : tmp_idx)
                answer[idx]++; // 처리 결과 메일 받은 횟수 갱신
        }
    }
    
    return answer;
}
