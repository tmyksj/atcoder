#include <iostream>
#include <string>

using namespace std;

int main() {
    int n, x;
    string s;
    cin >> n >> x >> s;

    for (int i = 0; i < n; i++) {
        if (s[i] == 'o') {
            x++;
        } else if (x > 0) {
            x--;
        }
    }

    cout << x << endl;
}
