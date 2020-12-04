#include <iomanip>
#include <iostream>

using namespace std;

int main() {
    int n, va, vb, l;
    cin >> n >> va >> vb >> l;

    double p = 0, q = l;
    for (int i = 0; i < n; i++) {
        double r = q;
        q += (q - p) / va * vb;
        p = r;
    }

    cout << setprecision(12) << fixed << q - p << endl;
}
