#include <iostream>
#include <string>

using namespace std;

int main() {
    int a, b;
    string op;
    cin >> a >> op >> b;
    cout << (op == "+" ? a + b : a - b) << endl;
}
