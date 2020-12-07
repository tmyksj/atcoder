#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int n, m, a, b;
    cin >> n >> m >> a >> b;

    vector<int> c(m);
    for (int i = 0; i < m; i++) {
        cin >> c[i];
    }

    string res = "complete";

    for (int i = 0, j = n; i < m; i++) {
        if (j <= a) {
            j += b;
        }

        j -= c[i];

        if (j < 0) {
            res = to_string(i + 1);
            break;
        }
    }

    cout << res << endl;
}
