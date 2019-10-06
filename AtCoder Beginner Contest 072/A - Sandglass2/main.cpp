#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    int x, t;
    cin >> x >> t;
    cout << max(0, x - t) << endl;
}
