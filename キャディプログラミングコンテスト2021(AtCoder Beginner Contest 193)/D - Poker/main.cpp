#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

int main() {
    int k;
    string s, t;
    cin >> k >> s >> t;

    double res = 0;
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            int pow10[] = { 1, 10, 100, 1000, 10000, 100000 };

            int c_s[10] = { 0 }, c_t[10] = { 0 };
            for (int k = 0; k < 4; k++) {
                c_s[s[k] - '0']++;
                c_t[t[k] - '0']++;
            }

            int p_s = 0, p_t = 0;
            for (int k = 1; k <= 9; k++) {
                p_s += k * pow10[c_s[k] + (i == k ? 1 : 0)];
                p_t += k * pow10[c_t[k] + (j == k ? 1 : 0)];
            }

            if (p_s > p_t) {
                res += (static_cast<double>(k - c_s[i] - c_t[i]) / (9 * k - 8))
                        * (static_cast<double>(k - c_s[j] - c_t[j] - (i == j ? 1 : 0)) / (9 * k - 9));
            }
        }
    }

    cout << setprecision(12) << fixed << res << endl;
}
