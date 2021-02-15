#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, s, d;
    cin >> n >> s >> d;

    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    bool res = false;
    for (int i = 0; i < n; i++) {
        res = res || (x[i] < s && y[i] > d);
    }

    cout << (res ? "Yes" : "No") << endl;
}
