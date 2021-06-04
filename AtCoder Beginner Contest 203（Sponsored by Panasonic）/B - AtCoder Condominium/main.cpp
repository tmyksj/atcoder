#include <iostream>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    cout << 100 * n * (n + 1) * k / 2 + n * k * (k + 1) / 2 << endl;
}
