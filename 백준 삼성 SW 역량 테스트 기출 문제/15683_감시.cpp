#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M, map[8][8];
vector<int> result;
vector<pair<int, int>> cctv, cctv5;

void CCTV(int y, int x, int dir) {
    while (true) {
        if (dir == 0) { // 상
            if (y - 1 >= 0) { // 지도를 벗어나지 않으면
                if (map[y - 1][x] == 0) // 빈 칸이면
                    map[--y][x] = 7;
                else if (map[y - 1][x] == 6) // 벽이면
                    return;
                else // 이미 감시 가능하다고 체크한 칸이거나 cctv가 있는 칸인 경우
                    y--;
            }
            else // 지도를 벗어나면
                return;
        }
        else if (dir == 1) { // 우
            if (x + 1 < M) { // 지도를 벗어나지 않으면
                if (map[y][x + 1] == 0) // 빈 칸이면
                    map[y][++x] = 7;
                else if (map[y][x + 1] == 6) // 벽이면
                    return;
                else // 이미 감시 가능하다고 체크한 칸이거나 cctv가 있는 칸인 경우
                    x++;
            }
            else // 지도를 벗어나면
                return;
        }
        else if (dir == 2) { // 하
            if (y + 1 < N) { // 지도를 벗어나지 않으면
                if (map[y + 1][x] == 0) // 빈 칸이면
                    map[++y][x] = 7;
                else if (map[y + 1][x] == 6) // 벽이면
                    return;
                else // 이미 감시 가능하다고 체크한 칸이거나 cctv가 있는 칸인 경우
                    y++;
            }
            else // 지도를 벗어나면
                return;
        }
        else if (dir == 3) { // 좌
            if (x - 1 >= 0) { // 지도를 벗어나지 않으면
                if (map[y][x - 1] == 0) // 빈 칸이면
                    map[y][--x] = 7;
                else if (map[y][x - 1] == 6) // 벽이면
                    return;
                else // 이미 감시 가능하다고 체크한 칸이거나 cctv가 있는 칸인 경우
                    x--;
            }
            else // 지도를 벗어나면
                return;
        }
    }
}

void copy(int a[8][8], int b[8][8]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            a[i][j] = b[i][j];
    }
}

void func(int k) {
    if (k == cctv.size()) {
        int cnt = 0;
        // cout << "\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                // cout << map[i][j] << " ";
                if (map[i][j] == 0)
                    cnt++;
            }
            // cout << "\n";
        }
        result.push_back(cnt);
        return;
    }

    int map_tmp[8][8];
    int y = cctv[k].first;
    int x = cctv[k].second;
    if (map[y][x] == 1) {
        for (int i = 0; i < 4; i++) { // 상우하좌
            copy(map_tmp, map);
            CCTV(y, x, i);
            func(k + 1);
            copy(map, map_tmp);
        }
    }
    else if (map[y][x] == 2) {
        for (int i = 0; i < 2; i++) { // 수평 수직
            copy(map_tmp, map);
            if (i == 0) { // 수평 
                CCTV(y, x, 1); // 우
                CCTV(y, x, 3); // 좌
            }
            else { // 수직
                CCTV(y, x, 0); // 상
                CCTV(y, x, 2); // 하
            }
            func(k + 1);
            copy(map, map_tmp);
        }
    }
    else if (map[y][x] == 3) {
        for (int i = 0; i < 4; i++) {
            copy(map_tmp, map);
            CCTV(y, x, i);
            CCTV(y, x, i == 3 ? 0 : i + 1);
            func(k + 1);
            copy(map, map_tmp);
        }
    }
    else if (map[y][x] == 4) {
        for (int i = 0; i < 4; i++) {
            copy(map_tmp, map);
            CCTV(y, x, i);
            CCTV(y, x, i == 3 ? 0 : i + 1);
            CCTV(y, x, i >= 2 ? i - 2 : i + 2);
            func(k + 1);
            copy(map, map_tmp);
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
            if (map[i][j] == 5)
                cctv5.push_back({ i,j });
            else if (map[i][j] != 6 && map[i][j] != 0)
                cctv.push_back({ i,j });
        }
    }

    for (int i = 0; i < cctv5.size(); i++) {
        for (int j = 0; j < 4; j++)
            CCTV(cctv5[i].first, cctv5[i].second, j);
    }

    func(0);
    cout << *min_element(result.begin(), result.end()) << "\n";

    return 0;
}
