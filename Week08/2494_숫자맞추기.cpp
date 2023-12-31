#include <iostream>
#include <vector>
using namespace std;

// 전체 회전횟수를 저장하지 않으면 이미 계산한 값을 또 계산하는 경우가 발생할 수 있어 시간초과남
typedef struct state {
	int total_turn = -1;	//전체 회전횟수
	int turn = 0;			//이번 나사에서의 회전
}State;

int N, sum = 0, movement = 0;
vector<int> init, dest;
State dp[10001][10];

int DP(int idx, int num, int left_move) { // idx : 나사 번호, num : 한자리 숫자, left_move : 윗 나사들에서의 왼쪽으로 이동한 횟수
	int left_cnt, right_cnt, left, right;
	left_cnt = (10 + (dest[idx - 1] - num)) % 10; // 현재 나사 위치에서 왼쪽으로 몇 번 돌려야하는지
	right_cnt = (10 + (num - dest[idx - 1])) % 10; // 현재 나사 위치에서 오른쪽으로 몇 번 돌려야하는지

	int& ret = dp[idx][num].total_turn;
	if (ret != -1)
		return ret;

	// left : 현재 나사를 왼쪽으로 돌리고 나머지 나사를 돌려 맞췄을 때 필요한 총 횟수
	// right : 현재 나사를 오른쪽으로 돌리고 나머지 나사를 돌려 맞췄을 때 필요한 총 횟수
	left = left_cnt; 
	right = right_cnt;
	if (idx != N) {
		left += DP(idx + 1, (init[idx] + left_cnt + left_move) % 10, left_move + left_cnt); // 왼쪽으로 돌려 맞춘 후 다음 나사로
		right += DP(idx + 1, (init[idx] + left_move) % 10, left_move); // 오른쪽으로 돌려 맞춘 후 다음 나사로
	}

	if (left < right) { 
		dp[idx][num].turn = left_cnt;
		ret = left;
	}
	else {
		dp[idx][num].turn = -right_cnt;
		ret = right;
	}
	return ret;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	char tmp;
	for (int i = 0; i < N; i++) {
		cin >> tmp;
		init.push_back(int(tmp - '0'));
	}
	for (int i = 0; i < N; i++) {
		cin >> tmp;
		dest.push_back(int(tmp - '0'));
	}

	int num = init[0], left_move = 0;
	cout << DP(1, num, left_move) << "\n";
	for (int i = 1; i <= N; i++) {
		num = (init[i - 1] + left_move) % 10;
		cout << i << " " << dp[i][num].turn << "\n";
		if (dp[i][num].turn > 0) // 왼쪽으로 돌린 횟수를 저장하여 나머지 나사들의 숫자를 업데이트
			left_move += dp[i][num].turn;
	}

	return 0;
}
