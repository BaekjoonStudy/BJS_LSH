#include <iostream>
#include <map>
#include <string>
using namespace std;

map<string, int> name;
int parent[200000], count_network[200000];

int find_parent(int idx) {
	if (parent[idx] == idx)
		return idx;
	else
		return parent[idx] = find_parent(parent[idx]);
}

void insert(string str1, string str2) {
	int isbool1 = false, isbool2 = false;
	int size = name.size();
	name.insert({ str1,size });
	if (name.size() == size + 1) {
		size++;
		isbool1 = true;
	}
	name.insert({ str2,size });
	if (name.size() == size + 1) {
		size++;
		isbool2 = true;
	}

	int parent_idx, child_idx;
	if (isbool1 == true && isbool2 == true) { // 둘 다 처음 입력됨
		// str1을 parent로
		parent_idx = name.find(str1)->second;
		child_idx = name.find(str2)->second;
		count_network[parent_idx] = 2;
		parent[parent_idx] = parent_idx; // str1의 parent를 str1으로
		parent[child_idx] = parent_idx; // str2의 parent를 str1으로
	}
	else if (isbool1 == true && isbool2 == false) { // str1만 처음 입력됨
		// str2의 parent를 str1의 parent로
		parent_idx = find_parent(name.find(str2)->second);
		child_idx = name.find(str1)->second;
		parent[child_idx] = parent_idx;
		count_network[parent_idx]++;
	}
	else if (isbool1 == false && isbool2 == true) { // str2만 처음 입력됨
		// str1의 parent를 str2의 parent로
		parent_idx = find_parent(name.find(str1)->second);
		child_idx = name.find(str2)->second;
		parent[child_idx] = parent_idx;
		count_network[parent_idx]++;
	}
	else { // 둘 다 이미 입력됨
		parent_idx = find_parent(name.find(str1)->second);
		child_idx = find_parent(name.find(str2)->second);
		if (parent_idx != child_idx) { // parent가 서로 다르다면 두 트리를 합침
			parent[child_idx] = parent_idx;
			count_network[parent_idx] += count_network[child_idx];
		}
	}
	cout << count_network[parent_idx] << "\n";
}



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int T, F;

	cin >> T;
	while (T--) {
		cin >> F;

		name.clear();
		for (auto x : count_network)
			x = 0;
		for (auto x : parent)
			x = 0;

		while (F--) {
			string str1, str2;
			cin >> str1 >> str2;

			insert(str1, str2);
		}
	}

	return 0;
}
