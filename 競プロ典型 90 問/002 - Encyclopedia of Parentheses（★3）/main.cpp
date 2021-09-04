#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < (1 << n); i++) {
        int cur = 0;
        bool ret = true;
        for (int j = n - 1; j >= 0; j--) {
            if ((i & (1 << j)) == 0) {
                cur++;
            } else {
                cur--;
            }

            if (cur < 0) {
                ret = false;
            }
        }

        if (cur != 0) {
            ret = false;
        }

        if (ret) {
            for (int j = n - 1; j >= 0; j--) {
                cout << ((i & (1 << j)) == 0 ? "(" : ")");
            }
            cout << endl;
        }
    }
}
