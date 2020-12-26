#include <algorithm>
#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    int n;
    string c;
    cin >> n >> c;

    map<int, int> m;
    for (int i = 0; i < n; i++) {
        m[c[i]]++;
    }

    cout << max({ m['1'], m['2'], m['3'], m['4'] }) << " " << min({ m['1'], m['2'], m['3'], m['4'] }) << endl;
}
