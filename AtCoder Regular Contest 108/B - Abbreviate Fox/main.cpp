#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;

    int res = n;

    vector<int> t(0);
    for (int i = 0; i < n; i++) {
        t.push_back(s[i]);

        int m = t.size();
        if (m > 2 && t[m - 3] == 'f' && t[m - 2] == 'o' && t[m - 1] == 'x') {
            t.pop_back();
            t.pop_back();
            t.pop_back();
            res -= 3;
        }
    }

    cout << res << endl;
}
