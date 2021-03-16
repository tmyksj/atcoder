#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<int> w(n), v(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> v[i];
    }

    vector<int> x(m);
    for (int i = 0; i < m; i++) {
        cin >> x[i];
    }

    vector<int> l(q), r(q);
    for (int i = 0; i < q; i++) {
        cin >> l[i] >> r[i];
    }

    for (int i = 0; i < q; i++) {
        priority_queue<tuple<int, int>, vector<tuple<int, int>>, greater<tuple<int, int>>> wv;
        priority_queue<tuple<int, int>> vw;
        for (int j = 0; j < n; j++) {
            wv.push(make_tuple(w[j], v[j]));
        }

        vector<int> y(0);
        for (int j = 0; j < l[i] - 1; j++) {
            y.push_back(x[j]);
        }
        for (int j = r[i]; j < m; j++) {
            y.push_back(x[j]);
        }

        sort(y.begin(), y.end());

        int res = 0;
        for (int j = 0; j < static_cast<int>(y.size()); j++) {
            while (!wv.empty()) {
                tuple<int, int> q = wv.top();
                if (get<0>(q) > y[j]) {
                    break;
                }

                wv.pop();
                vw.push(make_tuple(get<1>(q), get<0>(q)));
            }

            if (!vw.empty()) {
                tuple<int, int> q = vw.top();
                vw.pop();

                res += get<0>(q);
            }
        }

        cout << res << endl;
    }
}
