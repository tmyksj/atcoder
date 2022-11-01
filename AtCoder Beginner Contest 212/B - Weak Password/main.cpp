#include <iostream>
#include <string>

using namespace std;

int main() {
    string x;
    cin >> x;

    if ((x[0] == x[1] && x[1] == x[2] && x[2] == x[3])
            || ((x[0] - '0' + 1) % 10 == x[1] - '0'
            && (x[1] - '0' + 1) % 10 == x[2] - '0'
            && (x[2] - '0' + 1) % 10 == x[3] - '0')) {
        cout << "Weak" << endl;
    } else {
        cout << "Strong" << endl;
    }
}
