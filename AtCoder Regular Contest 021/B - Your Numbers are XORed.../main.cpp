#include <iostream>
#include <vector>

using namespace std;

int main() {
    int l;
    cin >> l;

    vector<int> b(l);
    for (int i = 0; i < l; i++) {
        cin >> b[i];
    }

    vector<int> a(l, 0);
    for (int i = 0; i < l - 1; i++) {
        a[i + 1] = (a[i] ^ b[i]);
    }

    if (a[0] == (a[l - 1] ^ b[l - 1])) {
        for (int i = 0; i < l; i++) {
            cout << a[i] << endl;
        }
    } else {
        cout << "-1" << endl;
    }
}
