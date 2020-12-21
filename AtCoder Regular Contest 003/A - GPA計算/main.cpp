#include <iomanip>
#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    map<int, int> m;
    m['A'] = 4;
    m['B'] = 3;
    m['C'] = 2;
    m['D'] = 1;

    int n;
    string r;
    cin >> n >> r;

    int s = 0;
    for (int i = 0; i < n; i++) {
        s += m[r[i]];
    }

    cout << setprecision(12) << fixed << s / static_cast<double>(n) << endl;
}
