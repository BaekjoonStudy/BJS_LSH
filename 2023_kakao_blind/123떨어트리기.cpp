#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

struct TreeNode {
    int idx = 0;
    vector<int> child;
};

TreeNode tree[102];
vector<int> Target;
vector<vector<int>> target_boundary;
vector<int> cnt;
int l = 0;

void find_leaf() { // 리프노드찾기
    queue<int> q;
    q.push(1);

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        if (tree[cur].child.size() == 0) {
            if (Target[cur-1] != 0)
                l++;
            continue;
        }

        for (auto next : tree[cur].child) {
            q.push(next);
        }
    }
}

void boundary() { // 각 리프노드별 target을 만족하기 위한 최소접근횟수와 최대접근횟수 구하기
    vector<int> tmp;
    for (auto t : Target) {
        tmp.clear();
        int min_ = (t % 3 == 0) ? (t / 3) : (t / 3) + 1;
        tmp.push_back(min_);
        tmp.push_back(t);
        target_boundary.push_back(tmp);
    }
}

vector<int> func() {
    vector<int> ret;
    cnt.resize(Target.size() + 1);
    int cur = 1, before;

    while (l) {
        if (tree[cur].child.size() == 0) { // 리프노드
            int min_ = target_boundary[cur-1][0]; int max_ = target_boundary[cur-1][1];
            cnt[cur]++;
            ret.push_back(cur);
            if (cnt[cur] > max_) {
                ret.pop_back();
                if (l > 0) { // 아직 카드가 부족한 노드가 있다면
                    ret.clear();
                }
                break;
            }

            if (cnt[cur] == min_) {
                l--;
            }
            cur = 1;
        }
        
        before = cur;
        cur = tree[before].child[tree[before].idx];
        tree[before].idx = (tree[before].idx + 1) % tree[before].child.size();
        
    }

    return ret;
}

vector<int> solution(vector<vector<int>> edges, vector<int> target) {
    vector<int> answer;
    Target = target;

    for (auto e : edges) {
        tree[e[0]].child.push_back(e[1]);
    }
    for (int i = 1; i <= target.size(); i++) {
        sort(tree[i].child.begin(), tree[i].child.end());
    }
    find_leaf();
    boundary();
    vector<int> arr = func();
    // cout << arr.size() << "\n";
    if (arr.size() == 0) {
        answer.push_back(-1);
    }
    else {
        answer.resize(arr.size());
        // for (auto a : arr) {
        //     cout << a << " ";
        // }
        // cout << "\n";
        for (int i = arr.size() - 1; i > -1; i--) {
            int cur = arr[i];
            if (cnt[cur] == 1)
                answer[i] = target[cur-1];
            else if (cnt[cur] > 1) {
                if (target[cur-1] > cnt[cur]+1)
                    answer[i] = 3;
                else if (target[cur-1] == cnt[cur]+1)
                    answer[i] = 2;
                else
                    answer[i] = 1;
            }
            target[cur-1] -= answer[i];
            cnt[cur]--;
        }
    }

    return answer;
}
