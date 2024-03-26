#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int find(vector<pair<char, int>> term, char c) {
    for (auto x : term) {
        if (x.first == c)
            return x.second;
    }
}

bool func(int year, int month, int day, string today, int p) {
    year += p / 12; month += p % 12;
    if (month > 12) {
        year++;
        month -= 12;
    }

    if (year < stoi(today.substr(0, 4)))
        return true;
    else if (year > stoi(today.substr(0, 4)))
        return false;
    else {
        if (month < stoi(today.substr(5, 7)))
            return true;
        else if (month > stoi(today.substr(5, 7)))
            return false;
        else {
            if (day <= stoi(today.substr(8, 10)))
                return true;
            else
                return false;
        }
    }
}

vector<int> solution(string today, vector<string> terms, vector<string> privacies) {
    vector<int> answer;
    vector<pair<char, int>> term;
    for (auto str : terms) {
        term.push_back({ str[0], stoi(str.substr(2,-1)) });
    }

    for (int i = 0; i < privacies.size(); i++) {
        int year = stoi(privacies[i].substr(0, 4));
        int month = stoi(privacies[i].substr(5, 7));
        int day = stoi(privacies[i].substr(8, 10));
        char c = privacies[i][11];
        if (func(year, month, day, today, find(term, c)) == true)
            answer.push_back(i + 1);
    }

    return answer;
}
