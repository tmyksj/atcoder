#include <iostream>
#include <map>

using namespace std;

int main() {
    map<int, int> m;
    for (int i = 0; i < 3; i++) {
        int a;
        cin >> a;
        m[a]++;
    }

    cout << (m[5] == 2 && m[7] == 1 ? "YES" : "NO") << endl;
}
