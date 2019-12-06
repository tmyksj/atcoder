#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string s;
    cin >> s;

    vector<char> res;
    for (int i = 0; i < static_cast<int>(s.size()); i++) {
        if (s[i] == 'B') {
            if (!res.empty()) {
                res.pop_back();
            }
        } else {
            res.push_back(s[i]);
        }
    }

    for (int i = 0; i < static_cast<int>(res.size()); i++) {
        cout << res[i];
    }
    cout << endl;
}
