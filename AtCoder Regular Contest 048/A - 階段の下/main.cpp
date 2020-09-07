#include <iostream>

using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    cout << (a < 0 && 0 < b ? b - a - 1 : b - a) << endl;
}
