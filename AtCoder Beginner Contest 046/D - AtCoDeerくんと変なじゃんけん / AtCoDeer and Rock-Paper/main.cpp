#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    cin >> s;

    int cnt = 0;
    for (int i = 0; i < static_cast<int>(s.size()); i++) {
        if (s[i] == 'p') {
            cnt++;
        }
    }

    cout << (s.size() / 2) - cnt << endl;
}
