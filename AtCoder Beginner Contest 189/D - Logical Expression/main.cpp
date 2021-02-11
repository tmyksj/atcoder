#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    long long res = 1;
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == "OR") {
            res += (1LL << (i + 1));
        }
    }

    cout << res << endl;
}
