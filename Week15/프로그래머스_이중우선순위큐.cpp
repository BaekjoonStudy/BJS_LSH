#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

vector<int> solution(vector<string> operations) {
    vector<int> answer;
    
    priority_queue<int, vector<int>, greater<int>> pq_min; // 오름차순 pq, 최솟값이 top
    priority_queue<int, vector<int>, less<int>> pq_max; // 내림차순 pq, 최댓값이 top
    
    int len = 0;
    for (auto o : operations) {
        if (o[0] == 'I') { // 삽입
            len++;
            int num = stoi(o.substr(2,-1));
            pq_min.push(num);
            pq_max.push(num);
        }
        else if (o[0] == 'D') { // 삭제
            if (len == 0) { // 큐가 이미 비어있다면 무시
                continue;
            }
            
            len--;
            if (len == 0) { // 삭제 후 길이가 0이라면 큐를 모두 초기화
                pq_min = priority_queue<int, vector<int>, greater<int>>();
                pq_max = priority_queue<int, vector<int>, less<int>>();
                continue;
            }
            
            if (o[2] == '-') // 최솟값 삭제
                pq_min.pop();
            else // 최댓값 삭제
                pq_max.pop();
        }
    }
    
    if (len == 0) {
        answer.push_back(0);
        answer.push_back(0);
    }
    else {
        answer.push_back(pq_max.top());
        answer.push_back(pq_min.top());
    }

    return answer;
}
