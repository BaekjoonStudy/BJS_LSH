#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, map[20][20], visited[20][20] = { 0 }, result = 0;
int shark[4] = { 2, 0, 0, 0 }; // 크기, 먹은 물고기 수, x좌표, y좌표
vector<pair<int, pair<int, int>>> fish_distance;
pair<int, int> dir[4] = { {-1,0}, {1,0}, {0,-1}, {0,1} }; // 상하좌우

bool find_fish(int x, int y) { // 먹을 수 있는 물고기 위치 찾기
	queue<pair<int, pair<int, int>>> q;
	q.push({ 0,{ x, y } });
	visited[x][y] = 1;
	bool isfind = false;
	while (!q.empty()) {
		int dist = q.front().first, x = q.front().second.first, y = q.front().second.second;
		q.pop();
		dist++;
		if (isfind == true) { // 먹을 수 있는 물고기를 이미 발견했었다면
			if (fish_distance[fish_distance.size() - 1].first != dist) // 거리가 다르다면
				break;
		}
		// 거리가 같거나 먹을 수 있는 물고기를 처음 발견했다면 
		for (int i = 0; i < 4; i++) {
			int tx = x + dir[i].first, ty = y + dir[i].second;
			if (tx >= 0 && tx < N && ty >= 0 && ty < N) {
				if (map[tx][ty] > 0 && map[tx][ty] < shark[0]) { // 먹을 수 있는 물고기를 발견했다면
					fish_distance.push_back({ dist, {tx,ty} }); // 추가
					isfind = true;
					visited[tx][ty] = 1;
				}
				else if (map[tx][ty] > 0 && map[tx][ty] > shark[0]) // 먹을 수 없는 물고기를 발견했다면
					continue;
				else if (map[tx][ty] >= 0 && visited[tx][ty] == 0) { // 방문한 적 없는 빈 칸이나 크기가 같은 물고기를 발견했다면
					q.push({ dist,{ tx,ty } });
					visited[tx][ty] = 1;
				}
			}
		}
	}
	return isfind;
}

void move_shark() {
	result += fish_distance[0].first; // 거리만큼 시간을 업데이트
	int x = fish_distance[0].second.first, y = fish_distance[0].second.second;
	for (int i = 1; i < fish_distance.size(); i++) { // 거리가 같은 물고기가 여러마리라면
		if (x > fish_distance[i].second.first) { // 가장 위에 있는 물고기를 먹음
			x = fish_distance[i].second.first;
			y = fish_distance[i].second.second;
		}
		else if (x == fish_distance[i].second.first) { // 가장 위에 있는 물고기가 여러마리라면
			if (y > fish_distance[i].second.second) { // 가장 왼쪽에 있는 물고기를 먹음
				x = fish_distance[i].second.first;
				y = fish_distance[i].second.second;
			}
		}
	}
	map[x][y] = -1; map[shark[2]][shark[3]] = 0; // 물고기가 있었던 칸을 -1로, 상어가 있었던 칸을 0으로
	shark[1]++; shark[2] = x; shark[3] = y; // 상어가 먹은 물고기 수와 위치 업데이트
	if (shark[1] == shark[0]) { // 상어가 자신의 크기만큼 물고기를 먹었다면
		shark[0]++; // 상어의 크기를 하나 키우고
		shark[1] = 0; // 먹은 물고기 수를 0으로 초기화
	}
	// 이동이 끝났으면 초기화
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			visited[i][j] = 0;
		}
	}
	fish_distance.clear();
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 9) {
				map[i][j] = -1;
				shark[2] = i;
				shark[3] = j;
			}
		}
	}

	while (true) {
		if (find_fish(shark[2], shark[3]) == true) { // 먹을 수 있는 물고기를 찾았다면
			move_shark();
		}
		else { // 먹을 수 있는 물고기를 찾지 못했다면
			cout << result << "\n";
			break;
		}
	}

	return 0;
}
