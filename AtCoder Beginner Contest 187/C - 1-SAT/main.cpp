#include <iostream>
#include <set>
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

    string res = "satisfiable";

    set<string> a, b;
    for (int i = 0; i < n; i++) {
        string x = (s[i][0] == '!' ? s[i].substr(1) : s[i]);
        set<string>& y = (s[i][0] == '!' ? a : b);
        set<string>& z = (s[i][0] == '!' ? b : a);

        if (y.find(x) == y.end()) {
            z.insert(x);
        } else {
            res = x;
            break;
        }
    }

    cout << res << endl;
}
