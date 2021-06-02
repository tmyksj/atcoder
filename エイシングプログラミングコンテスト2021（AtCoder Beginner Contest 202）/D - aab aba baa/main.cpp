#include <iostream>
#include <vector>

using namespace std;

int main() {
    long long a, b, k;
    cin >> a >> b >> k;

    vector<vector<long long>> nck(a + b + 1, vector<long long>(a + b + 1, 0));
    nck[0][0] = 1;
    for (int i = 1; i <= a + b; i++) {
        nck[i][0] = nck[i][i] = 1;
        for (int j = 1; j < i; j++) {
            nck[i][j] = nck[i - 1][j - 1] + nck[i - 1][j];
        }
    }

    string res = "";
    for (long long ia = a, ib = b, ik = k; ia > 0 || ib > 0; ) {
        if (ia == 0) {
            ib--;
            res += "b";
        } else if (ib == 0) {
            ia--;
            res += "a";
        } else if (ik <= nck[ia + ib - 1][ia - 1]) {
            ia--;
            res += "a";
        } else {
            ik -= nck[ia + ib - 1][ia - 1];
            ib--;
            res += "b";
        }
    }

    cout << res << endl;
}
