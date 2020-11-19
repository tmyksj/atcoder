#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    map<int, int> m;
    m['O'] = '0';
    m['D'] = '0';
    m['I'] = '1';
    m['Z'] = '2';
    m['S'] = '5';
    m['B'] = '8';

    string s;
    cin >> s;

    for (int i = 0; i < static_cast<int>(s.size()); i++) {
        if (m.find(s[i]) != m.end()) {
            s[i] = m[s[i]];
        }
    }

    cout << s << endl;
}
