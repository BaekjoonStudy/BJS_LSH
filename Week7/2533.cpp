#include <iostream>
#include <vector>
using namespace std;

vector<int> E[1000001];
int dp[1000001][2] = { 0 };
int visited[1000001];

// dp 테이블에 저장되는 숫자는 필요한 얼리어답터의 수
// dp[x][0]에는 자신이 얼리어답터라면 필요한 얼리어답터의 수 저장
// dp[x][1]에는 자신이 일반인이라면 필요한 얼리어답터의 수 저장
// 자기 자신이 얼리어답터라면 자식은 얼리어답터, 일반인 둘다 가능. 따라서 dp[x][0] += min(dp[child][0], dp[child][1]) 을 통해 최적해를 더해줘야함
// 자기 자신이 일반인이라면 자식은 모두 얼리어답터여야함 ==> dp[x][1] += dp[child][0]
void find(int x) {
    visited[x] = 1;
    dp[x][0] = 1; // 자기 자신이 얼리어답터
    for (int i = 0; i < E[x].size(); i++) {
        int child = E[x][i];
        if (visited[child]) continue;
        find(child);
        dp[x][1] += dp[child][0];
        dp[x][0] += min(dp[child][1], dp[child][0]);
    }

}
int main(void) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;

    int u, v;
    for (int i = 0; i < N - 1; i++) {
        cin >> u >> v;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    find(1);

    cout << min(dp[1][0], dp[1][1]) << "\n";
}
