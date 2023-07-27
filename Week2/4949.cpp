#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

bool valance(string str) {
	vector<char> s;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '(' || str[i] == '[' || str[i] == ')' || str[i] == ']')
			s.push_back(str[i]);
	}

	int i = 0;
	while (s.size() != 0 && i < s.size()) { // vector가 비어있다면 종료
		if (s[i] == ')') {
			if (i != 0 && s[i - 1] == '(') {
				s.erase(s.begin() + i - 1, s.begin() + i + 1);
				i -= 2;
			}
				
			else 
				return false;
		}

		else if (s[i] == ']') {
			if (i != 0 && s[i - 1] == '[') {
				s.erase(s.begin() + i - 1, s.begin() + i + 1);
				i -= 2;
			}
			else
				return false;
		}
		i++;
		// s는 ( [ ] )라고 가정하자
		// i가 2일 때 else if 문을 만족하여 i와 i-1 인덱스 원소를 제거하게됨
		// 따라서 ( ) 만 남게 될 것이고 i는 1이 되어 while문을 반복해야함
		// 때문에 원소를 제거해줬을 때 i -= 2를 해주고 마지막에 i++를 해줌
	}
	if (s.size() != 0)
		return false;
	else
		return true;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	string str, temp;
	vector<string> S;
	while (true) {
		getline(cin, str); // 공백도 입력받기 위함
		if (temp.length() == 0 && str == ".") // 종료조건
			break;
		else {
			temp += str;
			if (str[str.length() - 1] == '.'){ // 줄 구분을 온점으로 하기 위함
				S.push_back(temp);
				temp = "";
			}
		}
	}
	
	for(int i = 0; i < S.size(); i++) 
		cout << ((valance(S[i])) ? "yes" : "no") << "\n";

	return 0;
}
