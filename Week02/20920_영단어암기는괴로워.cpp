#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

bool comp(pair<string, int> x, pair<string, int> y) {
	if (x.second == y.second) { // 횟수 같을 때
		if (x.first.length() == y.first.length()) // 길이 같을 때
			return x.first < y.first; // 사전 순 정렬
		else // 길이 다를 때
			return x.first.length() > y.first.length(); // 길이 내림차순
	}
	else
		return x.second > y.second; // 횟수 내림차순
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	int N, M, i1, i2, cnt = 1;
	string str;
	vector<int> count;
	vector<string> W1;
	vector<pair <string, int>> W2;
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		cin >> str;
		if (str.length() >= M)
			W1.push_back(str);
	}
	sort(W1.begin(), W1.end());

	for (int i = 0; i < W1.size(); i += cnt) {
		i1 = lower_bound(W1.begin(), W1.end(), W1[i]) - W1.begin();
		i2 = upper_bound(W1.begin(), W1.end(), W1[i]) - W1.begin();
		cnt = i2 - i1;
		count.push_back(cnt);
		// ex: W = [a,a,a,b,b,c] 이고 i = 0 일 때
		// i1 = 0, i2 = 3 따라서 cnt = 3, 즉 a는 3개 있다는 뜻
		// 그 다음 i = 3, count[0] = 3이 됨
	}
	W1.erase(unique(W1.begin(), W1.end()), W1.end());
	for (int i = 0; i < W1.size(); i++)
		W2.push_back({W1[i], count[i]});

	sort(W2.begin(), W2.end(), comp);
	for (int i = 0; i < W2.size(); i++)
		cout << W2[i].first << "\n";
	
	return 0;
}
