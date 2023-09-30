#include <string>
#include <vector>

using namespace std;

int emoticon_plus = -1, emoticon_price = -1, disc[4] = { 10,20,30,40 };

void func(int k, vector<vector<int>> users, vector<int> emoticons, vector<int> discount) {
    if (k == emoticons.size()) { // 이모티콘의 할인율이 전부 설정이 되면
        vector<int> tmp; // 사용자가 구매한 이모티콘 가격을 저장할 임시 벡터
        for (int i = 0; i < users.size(); i++) { // 각 사용자들에 대한
            tmp.push_back(0);
            for (int j = 0; j < emoticons.size(); j++) {
                if (users[i][0] <= discount[j]) { // 구매 조건을 만족하면
                    tmp[i] += emoticons[j] * (100 - discount[j]) / 100;
                }
            }
        }
        int tmp1 = 0, tmp2 = 0;
        for (int i = 0; i < tmp.size(); i++) {
            if (tmp[i] >= users[i][1]) // 이모티콘 플러스 가입 조건을 만족하면
                tmp1++;
            else
                tmp2 += tmp[i];
        }

        if (emoticon_plus < tmp1) { // 이모티콘 플러스 가입자 수가 더 많아지면 업데이트
            emoticon_plus = tmp1;
            emoticon_price = tmp2;
        }
        else if (emoticon_plus == tmp1) { // 이모티콘 플러스 가입자 수가 동일하면
            emoticon_price = max(emoticon_price, tmp2); // 판매가격을 비교해서 더 큰 값으로 업데이트
        }
        return;
    }

    for (int i = 0; i < 4; i++) { // 네 가지 할인율에 대해서
        discount[k] = disc[i];
        func(k + 1, users, emoticons, discount);
    }
}

vector<int> solution(vector<vector<int>> users, vector<int> emoticons) {
    vector<int> answer;
    vector<int> discount;
    for (auto x : emoticons)
        discount.push_back(0);

    func(0, users, emoticons, discount);
    answer.push_back(emoticon_plus);
    answer.push_back(emoticon_price);
    return answer;
}
