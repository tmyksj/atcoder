#include <cmath>
#include <iostream>

using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;

    if ((c % 2 == 0 && abs(a) < abs(b)) || (c % 2 == 1 && a < b)) {
        cout << "<" << endl;
    } else if ((c % 2 == 0 && abs(a) == abs(b)) || (c % 2 == 1 && a == b)) {
        cout << "=" << endl;
    } else {
        cout << ">" << endl;
    }
}
