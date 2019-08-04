#include <iostream>

using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    cout << (b + c <= a ? 0 : c - (a - b)) << endl;
}
