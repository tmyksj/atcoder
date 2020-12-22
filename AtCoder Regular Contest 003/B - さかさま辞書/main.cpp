#include <algorithm>
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

    for (int i = 0; i < n; i++) {
        reverse(s[i].begin(), s[i].end());
    }

    sort(s.begin(), s.end());

    for (int i = 0; i < n; i++) {
        reverse(s[i].begin(), s[i].end());
    }

    for (int i = 0; i < n; i++) {
        cout << s[i] << endl;
    }
}
