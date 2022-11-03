#include <iostream>
#include <string>

using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;

    string t = s;
    for (int i = 0; i < n - 2; i++) {
        if ((t[i] == 'a' && t[i + 1] == 'x' && t[i + 2] == 'a')
                || (t[i] == 'i' && t[i + 1] == 'x' && t[i + 2] == 'i')
                || (t[i] == 'u' && t[i + 1] == 'x' && t[i + 2] == 'u')
                || (t[i] == 'e' && t[i + 1] == 'x' && t[i + 2] == 'e')
                || (t[i] == 'o' && t[i + 1] == 'x' && t[i + 2] == 'o')) {
            t[i] = '.';
            t[i + 1] = '.';
            t[i + 2] = '.';
        }
    }

    cout << t << endl;
}
