#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    int res = -n;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        res += a;
    }

    cout << res << endl;
}
