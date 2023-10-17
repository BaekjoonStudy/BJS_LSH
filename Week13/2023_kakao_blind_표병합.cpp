#include <string>
#include <vector>

using namespace std;

string map[51][51] = { "" };
pair<int, int> group[51][51];

void merge(int r1, int c1, int r2, int c2) {
	pair<int, int> p1 = group[r1][c1];
	pair<int, int> p2 = group[r2][c2];
	for (int i = 1; i < 51; i++) {
		for (int j = 1; j < 51; j++) {
			if (group[i][j] == p2)
				group[i][j] = p1;
		}
	}
}

void unmerge(int r, int c) {
	pair<int, int> p = group[r][c];
	for (int i = 1; i < 51; i++) {
		for (int j = 1; j < 51; j++) {
			if (group[i][j] == p) {
				group[i][j] = { i,j };
				map[i][j] = "";
			}
		}
	}
}

void func(vector<string> command) {
	if (command[0] == "UPDATE") {
		if (command.size() == 4) {
			pair<int, int> p = group[stoi(command[1])][stoi(command[2])];
			map[p.first][p.second] = command[3];
		}
		else {
			for (int i = 1; i < 51; i++) {
				for (int j = 1; j < 51; j++) {
					pair<int, int> p = group[i][j];
					map[p.first][p.second] = (map[p.first][p.second] == command[1]) ? command[2] : map[p.first][p.second];
				}
			}
		}
	}

	else if (command[0] == "MERGE") {
		int r1 = stoi(command[1]);
		int c1 = stoi(command[2]);
		int r2 = stoi(command[3]);
		int c2 = stoi(command[4]);

		if (r1 == r2 && c1 == c2) // 선택한 두 위치의 셀이 같은 셀일 경우
			return; // 무시

		if (map[group[r1][c1].first][group[r1][c1].second] != "") // r1,c1의 parent가 비어있지 않을 경우
			merge(r1, c1, r2, c2);
		else
			merge(r2, c2, r1, c1);
	}

	else if (command[0] == "UNMERGE") {
		pair<int, int> p = group[stoi(command[1])][stoi(command[2])];
		string value = map[p.first][p.second];
		unmerge(p.first, p.second);
		map[stoi(command[1])][stoi(command[2])] = value;
	}
	return;
}

vector<string> solution(vector<string> commands) {
	vector<string> answer;

	for (int i = 1; i < 51; i++) {
		for (int j = 1; j < 51; j++) {
			group[i][j] = { i,j };
		}
	}

	vector<string> command;
	string tmp;
	for (auto x : commands) {
		tmp = "";
		command.clear();
		for (auto y : x) { // 공백을 기준으로 split
			if (y == ' ') {
				command.push_back(tmp);
				tmp = "";
			}
			else
				tmp += y;
		}
		command.push_back(tmp);

		if (command[0] == "PRINT") {
			pair<int, int> p = group[stoi(command[1])][stoi(command[2])];
			if (map[p.first][p.second] == "") // 비어있을 경우
				answer.push_back("EMPTY");
			else
				answer.push_back(map[p.first][p.second]);
		}
		else
			func(command);
	}

	return answer;
}
