#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int n, k;
    string s;
    cin >> n >> k >> s;

    vector<vector<int>> c(26, vector<int>(0));
    for (int i = 0; i < n; i++) {
        c[s[i] - 'a'].push_back(i);
    }

    vector<int> c_idx(26, 0);
    vector<int> res(k);
    for (int i = 0, p = 0; i < k; i++) {
        for (int j = 0; j < 26; j++) {
            while (c_idx[j] < static_cast<int>(c[j].size()) && c[j][c_idx[j]] < p) {
                c_idx[j]++;
            }

            if (c_idx[j] < static_cast<int>(c[j].size()) && c[j][c_idx[j]] - i + k <= n) {
                p = c[j][c_idx[j]] + 1;
                res[i] = j + 'a';
                break;
            }
        }
    }

    for (int i = 0; i < k; i++) {
        cout << static_cast<char>(res[i]);
    }
    cout << endl;
}
