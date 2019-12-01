#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

int main() {
    long long h, w, n;
    cin >> h >> w >> n;

    map<int, set<int>> cell, cell_n;
    for (int i = 0; i < n; i++) {
        long long a, b;
        cin >> a >> b;
        cell[a].insert(b);

        for (int j = max(1LL, a - 2); j <= min(a, h - 2); j++) {
            for (int k = max(1LL, b - 2); k <= min(b, w - 2); k++) {
                cell_n[j].insert(k);
            }
        }
    }

    vector<long long> res(10, 0);
    res[0] = (h - 2) * (w - 2);

    for (map<int, set<int>>::iterator i = cell_n.begin(); i != cell_n.end(); i++) {
        for (set<int>::iterator j = i->second.begin(); j != i->second.end(); j++) {
            int cnt = 0;
            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    if (cell.find(i->first + k) != cell.end()
                            && cell[i->first + k].find(*j + l) != cell[i->first + k].end()) {
                        cnt++;
                    }
                }
            }

            res[0]--;
            res[cnt]++;
        }
    }

    for (int i = 0; i < 10; i++) {
        cout << res[i] << endl;
    }
}
