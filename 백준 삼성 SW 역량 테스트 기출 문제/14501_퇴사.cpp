#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, t, p;
vector<pair<int, int>> schedule;
int dp[16] = { 0 };
vector<int> result;

void DP(int n) {
	if (n == N + 1)
		return;
	int max_value = *max_element(dp, dp + n);
	// cout << n << " " << max_value << "\n";

	if (n + schedule[n].first - 1 <= N) {
		dp[n + schedule[n].first - 1] = max(schedule[n].second + max_value, dp[n + schedule[n].first - 1]);
	}
	/*
	for (auto x : dp)
		cout << x << " ";
	cout << "\n";
	*/
	DP(n + 1);
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	schedule.push_back({ 0,0 }); // 인덱싱을 1부터하기 위함
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> t >> p;
		schedule.push_back({ t,p });
	}

	DP(1);

	cout << *max_element(dp, dp + N + 1) << "\n";

	return 0;
}
