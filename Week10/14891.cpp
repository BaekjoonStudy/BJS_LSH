#include <iostream>
#include <vector>
using namespace std;

// 12시 방향 인덱스 : 0
// 마주보는 인덱스 : 2 - 6
int gear[4][8], K, r[4], score = 0;
vector<pair<int, int>> command;

void func(int idx, int dir) {
    r[idx] = dir;
    if (idx == 0) {
        if (gear[idx][2] != gear[idx + 1][6]) {
            r[idx + 1] = dir * -1;
            if (gear[idx + 1][2] != gear[idx + 2][6]) {
                r[idx + 2] = dir;
                if (gear[idx + 2][2] != gear[idx + 3][6])
                    r[idx + 3] = dir * -1;
            }
        }
    }
    else if (idx == 1) {
        if (gear[idx][6] != gear[idx - 1][2])
            r[idx - 1] = dir * -1;
        if (gear[idx][2] != gear[idx + 1][6]) {
            r[idx + 1] = dir * -1;
            if (gear[idx + 1][2] != gear[idx + 2][6])
                r[idx + 2] = dir;
        }
    }
    else if (idx == 2) {
        if (gear[idx][2] != gear[idx + 1][6])
            r[idx + 1] = dir * -1;
        if (gear[idx][6] != gear[idx - 1][2]) {
            r[idx - 1] = dir * -1;
            if (gear[idx - 1][6] != gear[idx - 2][2])
                r[idx - 2] = dir;
        }
    }
    else if (idx == 3) {
        if (gear[idx][6] != gear[idx - 1][2]) {
            r[idx - 1] = dir * -1;
            if (gear[idx - 1][6] != gear[idx - 2][2]) {
                r[idx - 2] = dir;
                if (gear[idx - 2][6] != gear[idx - 3][2])
                    r[idx - 3] = dir * -1;
            }
        }
    }
}

void rotate() {
    for (int i = 0; i < 4; i++) {
        if (r[i] == 1) { // 시계방향 10101111  ->  11010111
            int tmp = gear[i][7];
            for (int j = 7; j > 0; j--)
                gear[i][j] = gear[i][j - 1];
            gear[i][0] = tmp;
        }
        else if (r[i] == -1) { // 반시계방향 10101111 -> 01011111
            int tmp = gear[i][0];
            for (int j = 0; j < 7; j++)
                gear[i][j] = gear[i][j + 1];
            gear[i][7] = tmp;
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            char c;
            cin >> c;
            gear[i][j] = c - '0';
        }
    }

    cin >> K;
    for (int i = 0; i < K; i++) {
        int n1, n2;
        cin >> n1 >> n2;
        command.push_back({ n1 - 1,n2 }); // 톱니바퀴 번호를 0~3으로 인덱싱
    }

    for (auto x : command) {
        for (int i = 0; i < 4; i++)
            r[i] = 0;
        func(x.first, x.second);
        rotate();
        /*
        for (int i = 0; i < 4; i++) {
            cout << r[i] << "\n";
            for (auto x : gear[i])
                cout << x << " ";
            cout << "\n";
        }
        */
    }

    if (gear[0][0] == 1)
        score += 1;
    if (gear[1][0] == 1)
        score += 2;
    if (gear[2][0] == 1)
        score += 4;
    if (gear[3][0] == 1)
        score += 8;

    cout << score << "\n";

    return 0;
}
