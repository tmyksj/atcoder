#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> k(n);
    vector<set<int>> a(n, set<int>());
    for (int i = 0; i < n; i++) {
        cin >> k[i];
        for (int j = 0; j < k[i]; j++) {
            int aij;
            cin >> aij;
            a[i].insert(aij);
        }
    }

    int p, q;
    cin >> p >> q;

    vector<int> b(p);
    for (int i = 0; i < p; i++) {
        cin >> b[i];
    }

    int res = 0;
    for (int i = 0; i < n; i++) {
        int c = 0;
        for (int j = 0; j < p; j++) {
            if (a[i].find(b[j]) != a[i].end()) {
                c++;
            }
        }

        if (c >= q) {
            res++;
        }
    }

    cout << res << endl;
}
