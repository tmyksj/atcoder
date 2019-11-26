#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    cin >> s;

    int res = 0;
    for (int i = 1; i < static_cast<int>(s.size()); i++) {
        if (s[i - 1] != s[i]) {
            res++;
        }
    }

    cout << res << endl;
}
