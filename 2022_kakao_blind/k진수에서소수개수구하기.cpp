#include <string>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

string trans(int n, int k) { // k진수로 변환
    string ret = "";
    while (n >= k) {
        ret.insert(0, to_string(n % k));
        n /= k;
    }
    ret.insert(0, to_string(n));
    return ret;
}

vector<long long> split(string s) {
    vector<long long> ret;
    string tmp = "";
    bool isbool = false;
    for (auto w : s) {
        if (w == '0') {
            if (isbool == false) { // 그 전 숫자가 0이 아닌 경우
                ret.push_back(stol(tmp));
                tmp = "";
                isbool = true;
            }
        }
        else {
            tmp += w;
            isbool = false;
        }
    }
    if (tmp != "")
        ret.push_back(stol(tmp));
    return ret;
}

bool isPrime(long long num) {
    if (num < 2)
        return false;

    for (long long i = 2; i <= long(sqrt(num)); i++) {
        if (num % i == 0)
            return false;
    }
    return true;
}

int solution(int n, int k) {
    int answer = 0;
    string s = trans(n,k);
    vector<long long> v = split(s);
    for (auto num : v) {
        if (isPrime(num) == true)
            answer++;
    }
    return answer;
}
