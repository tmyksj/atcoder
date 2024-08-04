#include <iostream>

using namespace std;

int main() {
    int s, t;
    cin >> s >> t;

    int res = 0;
    for (int a = 0; a <= s; a++) {
        for (int b = 0; a + b <= s; b++) {
            for (int c = 0; a + b + c <= s && a * b * c <= t; c++) {
                res++;
            }
        }
    }

    cout << res << endl;
}
