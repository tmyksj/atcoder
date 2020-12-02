#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int c;
    cin >> c;

    vector<vector<int>> nml(c, vector<int>(3));
    for (int i = 0; i < c; i++) {
        cin >> nml[i][0] >> nml[i][1] >> nml[i][2];
    }

    for (int i = 0; i < c; i++) {
        sort(nml[i].begin(), nml[i].end());
    }

    int n = 0, m = 0, l = 0;
    for (int i = 0; i < c; i++) {
        n = max(n, nml[i][0]);
        m = max(m, nml[i][1]);
        l = max(l, nml[i][2]);
    }

    cout << n * m * l << endl;
}
