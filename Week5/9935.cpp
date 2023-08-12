#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	string str1, str2;
	vector<char> result;

	cin >> str1;
	cin >> str2;


	int isFind = false;
	for (int i = 0; i < str1.length(); i++) {
		result.push_back(str1[i]); // 하나씩 넣어주면서
		if (result.size() >= str2.length()) { // 폭발 문자열보다 길어지면
			for (int j = 0; j < str2.length(); j++) { // 폭발 문자열이랑 비교
				// result = "abcd"이고 폭발문자열 길이가 2라면 이미 "ab","bc"는 for문을 돌면서 비교했으므로 "cd"만 비교하면됨
				if (result[result.size() - str2.length() + j] == str2[j]) { 
					isFind = true;
				}
				else {
					isFind = false;
					break;
				}
			}

			if (isFind) {
				result.erase(result.begin() + result.size() - str2.length(), result.end());
			}
		}
	}

	if (result.size() == 0)
		cout << "FRULA" << "\n";
	else {
		for (auto a : result)
			cout << a;
		cout << "\n";
	}

	return 0;
}
