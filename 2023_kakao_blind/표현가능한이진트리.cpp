#include <string>
#include <vector>

using namespace std;

string binary(long long number) {
	string str = "";
	while (true) {
		if (number == 1) {
			str.insert(0,"1");
			break;
		}
		str.insert(0, to_string(number % 2));
		number /= 2;		
	}
	int tmp = 1, sum = 1;
	while (true) {
		if (str.length() <= sum) { // 이진수가 1,1+2,1+2+4,1+2+4+8,... 자릿수를 가져야 포화이진트리 만들 수 있음
			tmp = sum - str.length();
			while(tmp--)
				str.insert(0, "0");
			break;
		}
		else {
			tmp *= 2;
			sum += tmp;
		}
	}
	
	return str;
}

bool isZero(string str) {
	for (auto x : str) {
		if (x != '0')
			return false;
	}
	return true;
}

int func(string str) {
	if (str.length() == 1)
		return str[0] -'0';

	int mid = str.length() / 2;
	if (str[mid] == '0') // parent node가 0이면 return 0
		return 0;
	else if (isZero(str.substr(0, mid)) == false && isZero(str.substr(mid + 1, str.length())) == false) // 1 0 0 1 0 1 0 이런 경우
		return min(func(str.substr(0, mid)), func(str.substr(mid + 1, str.length())));
	else if (isZero(str.substr(0, mid)) == true && isZero(str.substr(mid + 1, str.length())) == false) // 0 0 0 1 0 1 0 이런 경우
		return func(str.substr(mid + 1, str.length()));
	else if (isZero(str.substr(0, mid)) == false && isZero(str.substr(mid + 1, str.length())) == true) // 1 0 0 1 0 0 0 이런 경우
		return func(str.substr(0, mid));
	else // 0 0 1 0 0 이런 경우
		return 1; 
}

vector<int> solution(vector<long long> numbers) {
	vector<int> answer;
	for (auto x : numbers) {
		string str = binary(x);
		answer.push_back(func(str));
	}
	return answer;
}
