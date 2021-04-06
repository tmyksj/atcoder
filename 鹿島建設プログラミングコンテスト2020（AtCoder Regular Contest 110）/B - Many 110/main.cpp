#include <iostream>
#include <string>

using namespace std;

int main() {
    int n;
    string t;
    cin >> n >> t;

    if (n == 1) {
        if (t == "0") {
            cout << "10000000000" << endl;
        } else {
            cout << "20000000000" << endl;
        }
    } else if (n == 2) {
        if (t == "00") {
            cout << "0" << endl;
        } else if (t == "01") {
            cout << "9999999999" << endl;
        } else {
            cout << "10000000000" << endl;
        }
    } else {
        if (t[0] == '1' && t[1] == '1' && t[2] == '0') {
            bool v = true;
            for (int i = 0; i < n; i++) {
                v = v && ((i % 3 == 0 && t[i] == '1') || (i % 3 == 1 && t[i] == '1') || (i % 3 == 2 && t[i] == '0'));
            }

            if (v) {
                cout << 10000000000LL - (n - 1) / 3 << endl;
            } else {
                cout << "0" << endl;
            }
        } else if (t[0] == '1' && t[1] == '0' && t[2] == '1') {
            bool v = true;
            for (int i = 0; i < n; i++) {
                v = v && ((i % 3 == 0 && t[i] == '1') || (i % 3 == 1 && t[i] == '0') || (i % 3 == 2 && t[i] == '1'));
            }

            if (v) {
                cout << 10000000000LL - n / 3 << endl;
            } else {
                cout << "0" << endl;
            }
        } else if (t[0] == '0' && t[1] == '1' && t[2] == '1') {
            bool v = true;
            for (int i = 0; i < n; i++) {
                v = v && ((i % 3 == 0 && t[i] == '0') || (i % 3 == 1 && t[i] == '1') || (i % 3 == 2 && t[i] == '1'));
            }

            if (v) {
                cout << 10000000000LL - (n + 1) / 3 << endl;
            } else {
                cout << "0" << endl;
            }
        } else {
            cout << "0" << endl;
        }
    }
}
