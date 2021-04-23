#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    long long t[2] = { 0 };
    for (int i = 0; i < n; i++) {
        int u = 0;
        for (int j = 0; j < m; j++) {
            if (s[i][j] == '0') {
                u++;
            }
        }

        t[u % 2]++;
    }

    cout << t[0] * t[1] << endl;
}
