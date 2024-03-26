#include <string>
#include <vector>
#include <numeric>
#include <iostream>

using namespace std;

vector<int> time_table;

int time_to_sec(string time) {
    int hour = stoi(time.substr(0,2));
    int min = stoi(time.substr(3,2));
    int sec = stoi(time.substr(6,2));
    sec += (hour*3600+min*60);
    return sec;
}

string sec_to_time(int sec) {
    string time = "";
    int hour = sec / 3600;
    sec -= (hour * 3600);
    int min = sec / 60;
    sec -= (min * 60);
    
    time += to_string(hour);
    if (hour < 10)
        time.insert(0, 1, '0');
    time += ":";
        
    time += to_string(min);
    if (min < 10)
        time.insert(3, 1, '0');
    time += ":";
    
    time += to_string(sec);
    if (sec < 10)
        time.insert(6, 1, '0');

    return time;
}

string solution(string play_time, string adv_time, vector<string> logs) {
    string answer = "";
    
    int play_sec = time_to_sec(play_time);
    int adv_sec = time_to_sec(adv_time);
    
    time_table.resize(play_sec+1);
    
    for (auto l : logs) {
        int start = time_to_sec(l.substr(0,8));
        int end = time_to_sec(l.substr(9,8));
        time_table[start] += 1;
        time_table[end] -= 1;
    }
       
    for (int i = 1; i < time_table.size(); i++) {
        time_table[i] += time_table[i-1];
    }

    int ans = 0;
    long long max_sum = accumulate(&time_table[0], &time_table[0]+adv_sec, 0);
    long long tmp_sum = max_sum;
    for (int i = 0; i < time_table.size()-adv_sec; i++) {
        tmp_sum += (time_table[adv_sec+i] - time_table[i]);  
        if (tmp_sum > max_sum) {
            max_sum = tmp_sum;
            ans = i + 1;
        }
    }
    
    return sec_to_time(ans);
}
