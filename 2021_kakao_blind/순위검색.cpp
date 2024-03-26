#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> I[4][3][3][3]; // 언어, 직군, 경력, 소울푸드 순

vector<int> trans(vector<string> arr) {
    vector<int> ret;
    // 언어
    if (arr[0] == "cpp")
        ret.push_back(0);
    else if (arr[0] == "java")
        ret.push_back(1);
    else if (arr[0] == "python")
        ret.push_back(2);
    else if (arr[0] == "-")
        ret.push_back(3);
    // 직군
    if (arr[1] == "backend")
        ret.push_back(0);
    else if (arr[1] == "frontend")
        ret.push_back(1);
    else if (arr[1] == "-")
        ret.push_back(2);
    // 경력
    if (arr[2] == "junior")
        ret.push_back(0);
    else if (arr[2] == "senior")
        ret.push_back(1);
    else if (arr[2] == "-")
        ret.push_back(2);
    // 소울푸드
    if (arr[3] == "chicken")
        ret.push_back(0);
    else if (arr[3] == "pizza")
        ret.push_back(1);
    else if (arr[3] == "-")
        ret.push_back(2);
    // 점수
    ret.push_back(stoi(arr[4]));
    
    return ret;
}

void func(vector<int> arr) {
    int lan = arr[0]; int job = arr[1]; int career = arr[2]; int food = arr[3];int score = arr[4];
    
    // 0개 => 1가지 경우
    I[3][2][2][2].push_back(score);
    // 1개 => 4가지 경우
    I[lan][2][2][2].push_back(score);
    I[3][job][2][2].push_back(score);
    I[3][2][career][2].push_back(score);
    I[3][2][2][food].push_back(score);
    // 2개 => 6가지 경우
    I[lan][job][2][2].push_back(score);
    I[lan][2][career][2].push_back(score);
    I[lan][2][2][food].push_back(score);
    I[3][job][career][2].push_back(score);
    I[3][job][2][food].push_back(score);
    I[3][2][career][food].push_back(score);
    // 3개 => 4가지 경우
    I[lan][job][career][2].push_back(score);
    I[lan][job][2][food].push_back(score);
    I[lan][2][career][food].push_back(score);
    I[3][job][career][food].push_back(score);
    // 4개 => 1가지 경우
    I[lan][job][career][food].push_back(score);
}

void sort_info() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                for (int z = 0; z < 3; z++) {
                    sort(I[i][j][k][z].begin(), I[i][j][k][z].end());
                }
            }
        }
    }
}

vector<int> solution(vector<string> info, vector<string> query) {
    vector<int> answer;
    vector<string> arr;
    vector<int> trans_arr;
    for (auto i : info) {
        string tmp = "";
        arr.clear();
        trans_arr.clear();
        for (auto j : i) {
            if (j == ' ') {
                arr.push_back(tmp);
                tmp = "";
            }
            else {
                tmp += j;
            }
        }
        arr.push_back(tmp);
        trans_arr = trans(arr);
        func(trans_arr);
    }
    
    sort_info();
    
    for (int i = 0; i < query.size(); i++) {
        string tmp = "";
        arr.clear();
        trans_arr.clear();
        for (auto j : query[i]) {
            if (j == ' ') {
                if (tmp == "and") {
                    tmp = "";
                    continue;
                }
                arr.push_back(tmp);
                tmp = "";
            }
            else {
                tmp += j;
            }
        }
        arr.push_back(tmp);
        trans_arr = trans(arr);
        
        int cnt = 0;
        for (auto i : I[trans_arr[0]][trans_arr[1]][trans_arr[2]][trans_arr[3]]) {
            if (i >= trans_arr[4])
                cnt++;
        }
        answer.push_back(cnt);
    }
    
    return answer;
}
