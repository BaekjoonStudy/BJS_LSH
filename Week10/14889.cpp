#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, min_diff;
int table[20][20];
vector<int> result;

void func(int k, vector<int> team, int res) {
	if (k == N / 2) { // 팀원이 N/2명이 되면
		result.push_back(res);
		return;
	}

	int before_res = 0;
	vector<int> before_team;
	for (int i = 0; i < N; i++) {
		if (k > 0) { // 팀원이 한 명 이상일 때
			if (i > team[team.size() - 1]) { // 0 2 1 이런 경우를 막기 위해, 막는 이유는 이미 이전에 0 1 2에 대해 계산하였으므로 중복됨
				before_res = res;
				before_team = team;
				for (int j = 0; j < team.size(); j++)
					res += table[team[j]][i] + table[i][team[j]];
				team.push_back(i);
				func(k + 1, team, res);
				res = before_res;
				team = before_team;
			}
		}
		else { // 팀원이 아직 없을 때
			team.push_back(i);
			func(k + 1, team, res);
			res = before_res;
			team = before_team;
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cin >> table[i][j];
	}
	vector<int> team;
	func(0, team, 0); // 만들어질 수 있는 모든 팀에 대해 능력치를 구함

	// team1 : {0,1,2}   team2 : {3,4,5}
	// result[0] : {0,1,2}의 능력치
	// result[result.size() - 1 - 0] : {3,4,5}의 능력치
	min_diff = abs(result[0] - result[result.size() - 1]);
	for (int i = 1; i < result.size() / 2; i++) {
		if (min_diff == 0)
			break;
		min_diff = min(min_diff, abs(result[i] - result[result.size() - 1 - i]));
	}
	
	cout << min_diff << "\n";


	return 0;
}
