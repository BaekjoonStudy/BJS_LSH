#include <string>
#include <vector>
#include <map>

using namespace std;

string solution(vector<string> survey, vector<int> choices) {
    string answer = "";
    map<char, int> score;
    
    for (int i = 0; i < survey.size(); i++) {
        string str = survey[i];
        int choice = choices[i];
        
        if (choice < 4)
            score[str[0]] += (4 - choice);
        else if (choice > 4)
            score[str[1]] += (choice - 4);
    }
    
    // 1번 지표
    if (score['R'] >= score['T'])
        answer += 'R';
    else
        answer += 'T';
    // 2번 지표
    if (score['C'] >= score['F'])
        answer += 'C';
    else
        answer += 'F';
    // 3번 지표
    if (score['J'] >= score['M'])
        answer += 'J';
    else
        answer += 'M';
    // 4번 지표
    if (score['A'] >= score['N'])
        answer += 'A';
    else
        answer += 'N';
    
    return answer;
}
