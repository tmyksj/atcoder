#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    int r = 0, s = 0, t = 0, u = 0, v = 0, w = 0;
    for (int i = 0; i < n; i++) {
        double a, b;
        cin >> a >> b;

        if (35 <= a) {
            r++;
        }

        if (30 <= a && a < 35) {
            s++;
        }

        if (25 <= a && a < 30) {
            t++;
        }

        if (25 <= b) {
            u++;
        }

        if (b < 0 && 0 <= a) {
            v++;
        }

        if (a < 0) {
            w++;
        }
    }

    cout << r << " " << s << " " << t << " " << u << " " << v << " " << w << endl;
}
