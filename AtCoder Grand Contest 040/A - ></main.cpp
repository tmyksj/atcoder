#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string s;
    cin >> s;

    int n = s.size() + 1;
    vector<int> a(n, 0);
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == '<') {
            a[i + 1] = a[i] + 1;
        } else {
            while (i + 1 < n - 1 && s[i + 1] != '<') {
                i++;
            }

            for (int j = i; j >= 0 && s[j] != '<'; j--) {
                a[j] = max(a[j], i - j + 1);
            }
        }
    }

    long long res = 0;
    for (int i = 0; i < n; i++) {
        res += a[i];
    }

    cout << res << endl;
}
