#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    const double pi = 3.14159265358979323846264338327950288;

    int n, x1, y1, x2, y2;
    cin >> n >> x1 >> y1 >> x2 >> y2;

    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }

    double cx = (x1 + x2) / 2.0;
    double cy = (y1 + y2) / 2.0;

    double t;
    if (cx == x2 && cy < y2) {
        t = pi / 2;
    } else if (cx == x2) {
        t = -pi / 2;
    } else if (cx < x2) {
        t = atan((y2 - cy) / (x2 - cx));
    } else {
        t = pi + atan((y2 - cy) / (x2 - cx));
    }

    for (int i = 0; i < n; i++) {
        cout << setprecision(12) << fixed
                << cos(-t) * (a[i] - cx) - sin(-t) * (b[i] - cy) << " "
                << sin(-t) * (a[i] - cx) + cos(-t) * (b[i] - cy) << endl;
    }
}
