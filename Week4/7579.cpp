#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int dp[101][10001] = { 0 };

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N, M, tmp, sum = 0;
	vector<int> memory, cost;
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		cin >> tmp;
		memory.push_back(tmp);
	}

	for (int i = 0; i < N; i++) {
		cin >> tmp;
		cost.push_back(tmp);
		sum += tmp;
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 0; j <= sum; j++) {
			if (j - cost[i - 1] >= 0)
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - cost[i - 1]] + memory[i - 1]);
			else
				dp[i][j] = dp[i - 1][j];
		}
	}

	for (int i = 0; i <= sum; i++) {
		if (dp[N][i] >= M) {
			cout << i << "\n";
			break;
		}
	}

	return 0;
}
