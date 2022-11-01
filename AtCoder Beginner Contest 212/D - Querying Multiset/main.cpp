#include <iostream>
#include <queue>

using namespace std;

int main() {
    int q;
    cin >> q;

    priority_queue<long long, vector<long long>, greater<long long>> que;
    long long b = 0;

    for (int i = 0; i < q; i++) {
        int p;
        cin >> p;

        if (p == 1) {
            long long x;
            cin >> x;
            que.push(x - b);
        } else if (p == 2) {
            long long x;
            cin >> x;
            b += x;
        } else {
            long long r = que.top();
            que.pop();
            cout << r + b << endl;
        }
    }
}
