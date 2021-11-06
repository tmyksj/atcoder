#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    int n, a, x, y;
    cin >> n >> a >> x >> y;
    cout << min(n, a) * x + max(n - a, 0) * y << endl;
}
