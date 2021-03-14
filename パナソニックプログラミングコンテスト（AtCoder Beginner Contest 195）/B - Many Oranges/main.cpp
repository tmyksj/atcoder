#include <iostream>

using namespace std;

int main() {
    int a, b, w;
    cin >> a >> b >> w;

    int res_min = (b + 1000 * w - 1) / b;
    int res_max = 1000 * w / a;

    if (res_min <= res_max) {
        cout << res_min << " " << res_max << endl;
    } else {
        cout << "UNSATISFIABLE" << endl;
    }
}
