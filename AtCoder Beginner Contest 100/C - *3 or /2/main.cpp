#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    int res = 0;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;

        while (a % 2 == 0) {
            a /= 2;
            res++;
        }
    }

    cout << res << endl;
}
