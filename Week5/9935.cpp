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


	int l1 = str1.length(), l2 = str2.length(), isFind = false;
	for (int i = 0; i < l1; i++) {
		result.push_back(str1[i]); // �ϳ��� �־��ָ鼭
		if (result.size() >= l2) { // ���� ���ڿ����� �������
			for (int j = 0; j < l2; j++) { // ���� ���ڿ��̶� ��
				// result = "abcd"�̰� ���߹��ڿ� ���̰� 2��� �̹� "ab","bc"�� for���� ���鼭 �������Ƿ� "cd"�� ���ϸ��
				if (result[result.size() - l2 + j] == str2[j]) { 
					isFind = true;
				}
				else {
					isFind = false;
					break;
				}
			}

			if (isFind) {
				result.erase(result.begin() + result.size() - l2, result.end());
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