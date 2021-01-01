#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    bool res = false;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                if (x[i] == x[j]) {
                    res = res || x[i] == x[k];
                } else {
                    res = res || (y[i] - y[j]) * (x[i] - x[k]) == (y[i] - y[k]) * (x[i] - x[j]);
                }
            }
        }
    }

    cout << (res ? "Yes" : "No") << endl;
}
