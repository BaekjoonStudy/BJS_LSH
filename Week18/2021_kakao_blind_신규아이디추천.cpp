#include <string>
#include <vector>
#include <iostream>

using namespace std;

bool isCheck(char w) {
    if (w >= 'a' && w <= 'z')
        return true;
    if (w >= '0' && w <= '9')
        return true;
    if (w == '-' || w == '_' || w == '.')
        return true;
    return false;
}

string first_step(string id) {
    for (int i = 0; i < id.size(); i++) {
        if (id[i] >= 'A' && id[i] <= 'Z')
            id[i] += ('a'-'A');
    }
    return id;
}

string second_step(string id) {
    for (int i = 0; i < id.size(); i++) {
        if (isCheck(id[i]) == false) {
            string tmp = id.substr(0,i) + id.substr(i+1, -1);
            id = tmp;
            i--;
        }
    }
    return id;
}
    
string third_step(string id) {
    for (int i = id.size()-1; i > 0; i--) {
        if (id[i] == '.' && id[i-1] == '.') {
            string tmp = id.substr(0,i-1) + id.substr(i,-1);
            id = tmp;
        }
    }
    return id;
}

string fourth_step(string id) {
    if (id[0] == '.') 
        id = id.substr(1,-1);
    if (id[id.size()-1] == '.')
        id = id.substr(0,id.size()-1);
    return id;
}

string fifth_step(string id) {
    if (id == "")
        return "a";
    return id;
}

string sixth_step(string id) {
    id = id.substr(0,15);
    if (id[id.size()-1] == '.')
        id = id.substr(0,14);
    return id;
}
    
string seventh_step(string id) {
    if (id.size() <= 2) {
        for (int i = id.size(); i < 3; i++)
            id += id[id.size()-1];
    }
    return id;
}

string solution(string new_id) {
    string answer = "";
    
    answer = first_step(new_id);
    // cout << "1단계 : " << answer << "\n";
    answer = second_step(answer);
    // cout << "2단계 : " << answer << "\n";
    answer = third_step(answer);
    // cout << "3단계 : " << answer << "\n";
    answer = fourth_step(answer);
    // cout << "4단계 : " << answer << "\n";
    answer = fifth_step(answer);
    // cout << "5단계 : " << answer << "\n";
    answer = sixth_step(answer);
    // cout << "6단계 : " << answer << "\n";
    answer = seventh_step(answer);
    // cout << "7단계 : " << answer << "\n";

    return answer;
}
