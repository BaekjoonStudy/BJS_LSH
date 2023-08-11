#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int visited[1001] = { 0 };

bool comp(int x, int y) { // 내림차순정렬
	return x > y;
}

void dfs(vector<int> V, vector<int>* E, int R) {
	vector<int> stack;
	for (auto v : V) 
		visited[v] = 0;	// visited 배열 초기화

	cout << R << " ";
	visited[R] = 1;
	sort(E[R].begin(), E[R].end(), comp); // stack은 가장 마지막에 들어온 원소부터 나가기 때문에 내림차순으로 정렬
	stack.insert(stack.end(), E[R].begin(), E[R].end()); 
	
	while (stack.size() != 0) {
		int u = stack[stack.size() - 1];
		stack.pop_back();
		if (visited[u] == 0) {
			cout << u << " ";
			visited[u] = 1;
			sort(E[u].begin(), E[u].end(), comp);
			for (auto w : E[u]) {
				if (visited[w] == 0) {
					stack.push_back(w);
				}
			}
		}
	}
	cout << "\n";
}

void bfs(vector<int> V, vector<int>* E, int R) {
	vector<int> queue;
	for (auto v : V)
		visited[v] = 0;

	queue.push_back(R);
	while (queue.size() != 0) {
		int u = queue[0];
		if (visited[u] == 0) {
			cout << u << " ";
			visited[u] = 1;
		}
		queue.erase(queue.begin(), queue.begin() + 1);
		sort(E[u].begin(), E[u].end());
		for (auto w : E[u]) {
			if (visited[w] == 0) {
				queue.push_back(w);
			}
		}
	}	
	cout << "\n";
}

int main()
{
	ios::sync_with_stdio;
	cin.tie(0);

	int N, M, S, tmp1, tmp2;
	cin >> N >> M >> S;

	vector<int> V; // 정점들
	while (N) {
		V.push_back(N);
		N--;
	}
	vector<int> E[1001]; // 간선을 표현할 배열 ex) E[1] = [3,5]라고 한다면 1번 정점은 3번, 5번 정점과 이어져있음.
	while (M--) {
		cin >> tmp1 >> tmp2;
		E[tmp1].push_back(tmp2); 
		E[tmp2].push_back(tmp1);
	}
	
	dfs(V, E, S);
	bfs(V, E, S);

	return 0;
}
