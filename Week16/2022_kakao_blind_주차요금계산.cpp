#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

int time_calc(string t) {
    int hour = stoi(t.substr(0,2));
    int min = stoi(t.substr(3,2));
    return hour * 60 + min;
}

int fee_calc(int time, vector<int> fees) {
    if (time <= fees[0]) // 기본 시간 이하
        return fees[1]; // 기본 요금 청구
    else { // 기본 시간 초과
        int extra = time - fees[0];
        if (extra % fees[2] == 0) // 단위시간으로 나누어 떨어지면
            return fees[1] + fees[3] * (extra / fees[2]);
        else // 나누어 떨어지지 않으면
            return fees[1] + fees[3] * ((extra / fees[2]) + 1);
    }
}

vector<int> solution(vector<int> fees, vector<string> records) {
    vector<int> answer;
    map<string,int> in; // 입차 시간 저장
    map<string,int> out; // 출차 여부 저장 (0: 안나감, 1: 나감)
    map<string,int> record; // 총 주차 기록
    int time; string car_num;
    for (auto r : records) {
        time = time_calc(r.substr(0,5));
        car_num = r.substr(6,4);
        if (r.substr(11,-1) == "IN") { // 입차
            in[car_num] = time;
            out[car_num] = 0;
            record.insert({car_num,0}); // 이미 차 기록이 있다면 아무동작안함
        }
        else { // 출차
            record[car_num] += (time - in[car_num]);
            out[car_num] = 1;
        }
    }
    vector<pair<string,int>> o(out.begin(), out.end());

    for (auto x : o) {
        car_num =  x.first;
        if (x.second == 0) { // 아직 출차를 하지 않음
            time = in[car_num];
            record[car_num] += ((23*60+59) - time);
        }
        
        int fee = fee_calc(record[car_num], fees);
        answer.push_back(fee);
    }
    
    return answer;
}
