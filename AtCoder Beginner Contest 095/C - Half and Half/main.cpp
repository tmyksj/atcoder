#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    int a, b, c, x, y;
    cin >> a >> b >> c >> x >> y;
    cout << min(a * x + b * y,
            min(2 * (x < y ? x : y) * c + (x < y ? y - x : x - y) * (x < y ? b : a),
                    2 * (x < y ? y : x) * c)) << endl;
}
