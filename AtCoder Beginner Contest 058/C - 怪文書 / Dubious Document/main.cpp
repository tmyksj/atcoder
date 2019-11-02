#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> cnt(26, 50);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        vector<int> c(26, 0);
        for (int j = 0; j < static_cast<int>(s.size()); j++) {
            c[s[j] - 'a']++;
        }

        for (int j = 0; j < 26; j++) {
            cnt[j] = min(cnt[j], c[j]);
        }
    }

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < cnt[i]; j++) {
            cout << static_cast<char>(i + 'a');
        }
    }
    cout << endl;
}
