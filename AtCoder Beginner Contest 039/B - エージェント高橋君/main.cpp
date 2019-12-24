#include <iostream>

using namespace std;

int main() {
    int x;
    cin >> x;

    int n = 1;
    for (; n * n * n * n < x; n++) {
    }

    cout << n << endl;
}
