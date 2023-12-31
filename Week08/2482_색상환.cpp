#include<iostream>
using namespace std;

int N, K;
long long dp[1001][1001] = { 0 };

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	cin >> K;

	// dp[i][j] : i개의 색 중 j개를 선택하는 경우
	// dp[4][2] = 3 >> A,C / A,D / B,D
	// dp는 색상환이 아닌 일자로 나열된 형태
	// 색상환에서 A,D는 안되지만 일자로 나열된 형태에서는 A,D 가능
	for (int i = 1; i <= N; i++)
	{
		// i개의 색 중 하나도 선택을 하지 않는 경우, 즉 N번째 색만을 선택하는 경우
		dp[i][0] = 1;

		// i개의 색 중 1개를 선택하는 경우
		dp[i][1] = i;
	}

	for (int i = 2; i <= N; i++) {
		for (int j = 2; j <= K; j++) {
			// dp[i-2][j-1] : i번째 색을 선택하고 i번째와 
			// dp[i-1][j] : i번째 색을 선택하지 않고 i-1개의 색 중 j개를 선택하는 경우
			dp[i][j] = (dp[i - 2][j - 1] + dp[i - 1][j]) % 1000000003;
		}
	}

	// dp[N-3][K-1] : N번째 색을 선택하고 N번째 색과 그 색의 좌, 우를 제외한 N-3개의 색 중 K-1개의 색을 선택하는 경우
	// dp[N-1][K] : N번째 색을 선택하지 않고 N-1개의 색 중 K개를 선택하는 경우
	cout << (dp[N - 3][K - 1] + dp[N - 1][K]) % 1000000003 << "\n";
	return 0;
}
