#include <iostream>

using namespace std;

int main() {
    long a, b, c;
    cin >> a >> b >> c;
    cout << a * b % 1000000007 * c % 1000000007 << endl;
}
