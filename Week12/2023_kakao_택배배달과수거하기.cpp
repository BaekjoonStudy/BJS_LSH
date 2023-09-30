long long solution(int cap, int n, vector<int> deliveries, vector<int> pickups)
{
    long long answer = 0;

    int d = -1, p = -1, truck = 0;
    for (int i = deliveries.size() - 1; i >= 0; i--) {
        if (deliveries[i] != 0) {
            d = i;
            break;
        }
    }
    for (int i = pickups.size() - 1; i >= 0; i--) {
        if (pickups[i] != 0) {
            p = i;
            break;
        }
    }

    while (d > -1 || p > -1) {
        answer += max(d + 1, p + 1) * 2;
        
        truck = 0;
        while (d > -1) { // 배달
            //cout << d << " " << truck << "\n";
            if (deliveries[d] + truck <= cap) { // 다 배달한 경우
                truck += deliveries[d];
                d--;
            }
            else { // 일부만 배달한 경우
                deliveries[d] -= cap - truck;
                break;
            }
        }

        truck = 0;
        while (p > -1) { // 수거
            if (pickups[p] + truck <= cap) { // 다 수거한 경우
                truck += pickups[p];
                p--;
            }
            else { // 일부만 수거한 경우
                pickups[p] -= cap - truck;
                break;
            }
        }
    }

    return answer;
}
