#include <iostream>
#include <vector>
using namespace std;

int visited[501];
vector<int> E[501];

bool isTree(int idx, int before) {
	visited[idx] = 1;

	for (int i = 0; i < E[idx].size(); i++) {
		int next = E[idx][i];
		if (next == before)  continue; // 바로 이전에 방문한 곳인 경우 pass
		if (visited[next]) return false; // 사이클 발생
		if (!isTree(next, idx)) return false; // 재귀를 통해 dfs
	}
	return true;
}

int main()
{
	ios::sync_with_stdio;
	cin.tie(0);

	int n, m, T = 1;
	
	while (true) {
		cin >> n >> m;

		// 초기화
		for (int i = 0; i < 502; i++) {
			visited[i] = 0;
			E[i].clear();
		}
		int tree = 0;

		if (n == 0 && m == 0)
			break;
		else {
			while (m--) {
				int tmp1, tmp2;
				cin >> tmp1 >> tmp2;
				E[tmp1].push_back(tmp2);
				E[tmp2].push_back(tmp1);
			}

			for (int i = 1; i <= n; i++) {
				if (visited[i] == 0) {
					if (isTree(i, 0))
						tree++;	
				}
			}
		}

		if (tree == 0)
			cout << "Case " << T << ": No trees.\n";
		else if (tree == 1)
			cout << "Case " << T << ": There is one tree.\n";
		else
			cout << "Case " << T << ": A forest of " << tree << " trees.\n";
		T++;
	}

	return 0;
}
