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

    int res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((x[i] > x[j] && x[j] - x[i] <= y[i] - y[j] && y[i] - y[j] <= x[i] - x[j])
                    || (x[i] < x[j] && x[i] - x[j] <= y[j] - y[i] && y[j] - y[i] <= x[j] - x[i])) {
                res++;
            }
        }
    }

    cout << res << endl;
}
