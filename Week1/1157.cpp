#include <iostream>
using namespace std;

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
  
    char str[1000001];
    cin >> str;
    int count[26], index, max, max_index, equal = 0;

    for (int i = 0; i < 26; i++)
        count[i] = 0;

    for (int j = 0; str[j] != '\0'; j++) {
        index = (str[j] >= 'a' ? str[j] - ('a' - 'A') : str[j]) - 'A';
        count[index]++;
    }

    max_index = 0;
    max = count[0];
    for (int k = 1; k < 26; k++) {
        if (count[k] > max) {
            equal = 0;
            max = count[k];
            max_index = k;
        }
        else if (count[k] == max)
            equal = 1;
    }

    if (equal == 1)
        cout << "?\n";
    else
        cout << char(max_index+65) << endl;
}
