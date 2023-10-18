#include <string>
#include <vector>
#include <numeric>

using namespace std;

int solution(vector<int> queue1, vector<int> queue2) {
    int answer = 0;
    int idx1 = 0, idx2 = 0, size = queue1.size();
    long long sum1 = accumulate(queue1.begin(), queue1.end(), 0);
    long long sum2 = accumulate(queue2.begin(), queue2.end(), 0);
    long long sum = (sum1 + sum2) / 2;
    
    while (idx1 < size * 2 && idx2 < size * 2) {
        if (sum1 == sum)
            break;
        else if (sum1 > sum) { // queue1을 pop 한 후 queue2에 insert
            sum1 -= queue1[idx1];
            queue2.push_back(queue1[idx1++]);
        }
        else if (sum1 < sum) { // queue2를 pop 한 후 queue1에 insert
            sum1 += queue2[idx2];
            queue1.push_back(queue2[idx2++]);
        }
        answer++;
    }
    // queue1 : [1,2,3] -> [1,2,3,4,5,6,1,2,3,...]
    // queue2 : [4,5,6] -> [4,5,6,1,2,3,4,5,6,...]
    // size * 2 번째부터 확실히 중복됨
    if (idx1 == size * 2 || idx2 == size * 2)
        answer = -1;
    
    return answer;
}
