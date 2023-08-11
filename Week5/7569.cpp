#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int M, N, H;
int visited[1000000] = { 0 };

void dequeue(vector<int>& Q) {
	int idx = Q[0];
	if (idx - N * M >= 0 && visited[idx - N * M] == 0) {
		Q.push_back(idx - N * M); // 위
		visited[idx - N * M] = 1;
	}

	if (idx + N * M < N * M * H && visited[idx + N * M] == 0) {
		Q.push_back(idx + N * M); // 아래
		visited[idx + N * M] = 1;
	}

	if (idx - 1 >= 0 && (idx - 1) / M == idx / M && visited[idx - 1] == 0) {
		Q.push_back(idx - 1); // 왼쪽
		visited[idx - 1] = 1;
	}

	if (idx + 1 < N * M * H && (idx + 1) / M == idx / M && visited[idx + 1] == 0) {
		Q.push_back(idx + 1); // 오른쪽
		visited[idx + 1] = 1;
	}

	if (idx - M >= 0 && (idx - M) / (M * N) == idx / (M * N) && visited[idx - M] == 0) {
		Q.push_back(idx - M); // 뒤쪽
		visited[idx - M] = 1;
	}

	if (idx + M < N * M * H && (idx + M) / (M * N) == idx / (M * N) && visited[idx + M] == 0) {
		Q.push_back(idx + M); // 앞쪽
		visited[idx + M] = 1;
	}

	Q.erase(Q.begin(), Q.begin() + 1);
	return;
}

int bfs(vector<int> V) {
	vector<int> queue = V;
	int day = 0;
	int size = V.size();

	while (true) {
		for (int i = 0; i < size; i++) {
			dequeue(queue);
		}
		if (queue.size() != 0) {
			size = queue.size();
			day++;
		}
		else
			break;
	}
	return day;
}

int main()
{
	ios::sync_with_stdio;
	cin.tie(0);

	int tmp, isRipe = 0, isNoRipe = 0;
	cin >> M >> N >> H;

	vector<int> ripeTomato;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < M; k++) {
				cin >> tmp;
				int idx = i * M * N + j * M + k; // 1차원 인덱스로 바꿔줌
				if (tmp == -1)
					visited[idx] = 1;
				else if (tmp == 1) {
					visited[idx] = 1;
					ripeTomato.push_back(idx);
					isRipe = 1;
				}
				else if (tmp == 0)
					isNoRipe = 1;
			}
		}
	}

	if (isRipe == 0)
		cout << "-1\n";

	else if (isRipe == 1 && isNoRipe == 0)
		cout << "0\n";

	else {
		int day = bfs(ripeTomato);
		if (accumulate(begin(visited), begin(visited) + M * N * H, 0) == M * N * H)
			cout << day << "\n";
		else
			cout << "-1\n";
	}
	return 0;
}