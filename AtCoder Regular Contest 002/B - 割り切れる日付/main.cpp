#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

int main() {
    string ymd;
    cin >> ymd;

    int y = 1000 * (ymd[0] - '0') + 100 * (ymd[1] - '0') + 10 * (ymd[2] - '0') + ymd[3] - '0';
    int m = 10 * (ymd[5] - '0') + ymd[6] - '0';
    int d = 10 * (ymd[8] - '0') + ymd[9] - '0';

    for (; ; y++, m = 1) {
        for (; m <= 12; m++, d = 1) {
            for (; d <= (!(y % 4 == 0 && (y % 100 != 0 || y % 400 == 0)) && m == 2
                    ? 28
                    : (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0)) && m == 2
                    ? 29
                    : m == 4 || m == 6 || m == 9 || m == 11
                    ? 30
                    : 31); d++) {
                if (y % m == 0 && y / m % d == 0) {
                    cout << setw(4) << setfill('0') << y << "/";
                    cout << setw(2) << setfill('0') << m << "/";
                    cout << setw(2) << setfill('0') << d << endl;
                    goto out;
                }
            }
        }
    }

out:
    ;
}
