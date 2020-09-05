#include <iostream>
#include <string>

using namespace std;

int main() {
    string a, b;
    cin >> a >> b;
    cout << (a[0] - 'A' == b[0] - 'a' ? "Yes" : "No") << endl;
}
