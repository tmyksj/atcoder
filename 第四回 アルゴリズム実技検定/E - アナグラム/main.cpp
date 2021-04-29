#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;

    string res = "None";

    string t = s;
    sort(t.begin(), t.end());

    do {
        string u = t;
        reverse(u.begin(), u.end());

        if (s != t && s != u) {
            res = t;
            break;
        }
    } while (next_permutation(t.begin(), t.end()));

    cout << res << endl;
}
