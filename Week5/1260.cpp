#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int visited[1001] = { 0 };

bool comp(int x, int y) { // ������������
	return x > y;
}

void dfs(vector<int> V, vector<int>* E, int R) {
	vector<int> stack;
	for (auto v : V) 
		visited[v] = 0;	// visited �迭 �ʱ�ȭ

	cout << R << " ";
	visited[R] = 1;
	sort(E[R].begin(), E[R].end(), comp); // stack�� ���� �������� ���� ���Һ��� ������ ������ ������������ ����
	stack.insert(stack.end(), E[R].begin(), E[R].end()); 
	
	while (stack.size() != 0) {
		int u = stack[stack.size() - 1];
		stack.pop_back();
		if (visited[u] == 0) {
			cout << u << " ";
			visited[u] = 1;
			sort(E[u].begin(), E[u].end(), comp);
			stack.insert(stack.end(), E[u].begin(), E[u].end());
		}
	}
	cout << "\n";
}

int dequeue(vector<int>& Q) {
	int x = Q[0];
	if (visited[x] == 0) {
		cout << x << " ";
		visited[x] = 1;
	}
	Q.erase(Q.begin(), Q.begin() + 1);
	return x;
}

void bfs(vector<int> V, vector<int>* E, int R) {
	vector<int> queue;
	for (auto v : V)
		visited[v] = 0;

	queue.push_back(R);
	while (queue.size() != 0) {
		int u = dequeue(queue);
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

	vector<int> V; // ������
	while (N) {
		V.push_back(N);
		N--;
	}
	vector<int> E[1001]; // ������ ǥ���� �迭 ex) E[1] = [3,5]��� �Ѵٸ� 1�� ������ 3��, 5�� ������ �̾�������.
	while (M--) {
		cin >> tmp1 >> tmp2;
		E[tmp1].push_back(tmp2); 
		E[tmp2].push_back(tmp1);
	}
	
	dfs(V, E, S);
	bfs(V, E, S);

	return 0;
}