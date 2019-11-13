#include <iostream>

using namespace std;

int main() {
    int k, s;
    cin >> k >> s;

    int res = 0;
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j <= k; j++) {
            if (0 <= s - i - j && s - i - j <= k) {
                res++;
            }
        }
    }

    cout << res << endl;
}
