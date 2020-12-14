#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> disk(m);
    for (int i = 0; i < m; i++) {
        cin >> disk[i];
    }

    vector<int> res(n + 1);
    for (int i = 0; i <= n; i++) {
        res[i] = i;
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j <= n; j++) {
            if (res[j] == disk[i]) {
                swap(res[0], res[j]);
                break;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << res[i] << endl;
    }
}
