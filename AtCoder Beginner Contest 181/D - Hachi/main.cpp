#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    string s;
    cin >> s;

    map<int, int> m;
    for (int i = 0; i < static_cast<int>(s.size()); i++) {
        m[s[i] - '0']++;
    }

    bool res = false;
    if (s.size() == 1) {
        res = s == "8";
    } else if (s.size() == 2) {
        res = (10 * (s[0] - '0') + s[1] - '0') % 8 == 0 || (10 * (s[1] - '0') + s[0] - '0') % 8 == 0;
    } else {
        for (int i = 104; i < 1000; i += 8) {
            map<int, int> n;
            n[i / 100 % 10]++;
            n[i / 10 % 10]++;
            n[i % 10]++;

            if (n[0] > 0) {
                continue;
            }

            res = true;
            for (map<int, int>::iterator j = n.begin(); j != n.end(); j++) {
                if (j->second > m[j->first]) {
                    res = false;
                }
            }

            if (res) {
                break;
            }
        }
    }

    cout << (res ? "Yes" : "No") << endl;
}
