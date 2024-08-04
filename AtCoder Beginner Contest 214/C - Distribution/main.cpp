#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    vector<int> t(n);
    for (int i = 0; i < n; i++) {
        cin >> t[i];
    }

    priority_queue<tuple<int, int>,
            vector<tuple<int, int>>,
            greater<tuple<int, int>>> que;
    for (int i = 0; i < n; i++) {
        que.push(make_tuple(t[i], i));
    }

    vector<int> res(n, 1000000000);
    while (!que.empty()) {
        tuple<int, int> q = que.top();
        que.pop();

        if (res[get<1>(q)] > get<0>(q)) {
            res[get<1>(q)] = get<0>(q);
            que.push(make_tuple(get<0>(q) + s[get<1>(q)], (get<1>(q) + 1) % n));
        }
    }

    for (int i = 0; i < n; i++) {
        cout << res[i] << endl;
    }
}
