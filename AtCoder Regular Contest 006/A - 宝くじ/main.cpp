#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> e(6);
    for (int i = 0; i < 6; i++) {
        cin >> e[i];
    }

    int b;
    cin >> b;

    vector<int> l(6);
    for (int i = 0; i < 6; i++) {
        cin >> l[i];
    }

    int c_e = 0, c_b = 0;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (l[i] == e[j]) {
                c_e++;
            }
        }

        if (l[i] == b) {
            c_b++;
        }
    }

    if (c_e == 6) {
        cout << "1" << endl;
    } else if (c_e == 5 && c_b == 1) {
        cout << "2" << endl;
    } else if (c_e == 5) {
        cout << "3" << endl;
    } else if (c_e == 4) {
        cout << "4" << endl;
    } else if (c_e == 3) {
        cout << "5" << endl;
    } else {
        cout << "0" << endl;
    }
}
