#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main() {
    map<int, int> m;
    m['z'] = m['r'] = m['Z'] = m['R'] = '0';
    m['b'] = m['c'] = m['B'] = m['C'] = '1';
    m['d'] = m['w'] = m['D'] = m['W'] = '2';
    m['t'] = m['j'] = m['T'] = m['J'] = '3';
    m['f'] = m['q'] = m['F'] = m['Q'] = '4';
    m['l'] = m['v'] = m['L'] = m['V'] = '5';
    m['s'] = m['x'] = m['S'] = m['X'] = '6';
    m['p'] = m['m'] = m['P'] = m['M'] = '7';
    m['h'] = m['k'] = m['H'] = m['K'] = '8';
    m['n'] = m['g'] = m['N'] = m['G'] = '9';

    int n;
    cin >> n;

    vector<string> w(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }

    vector<string> res(0);
    for (int i = 0; i < n; i++) {
        string r = "";
        for (int j = 0; j < static_cast<int>(w[i].size()); j++) {
            map<int, int>::iterator k = m.find(w[i][j]);
            if (k != m.end()) {
                r += k->second;
            }
        }

        if (r != "") {
            res.push_back(r);
        }
    }

    for (int i = 0; i < static_cast<int>(res.size()); i++) {
        cout << (i == 0 ? "" : " ") << res[i];
    }
    cout << endl;
}
