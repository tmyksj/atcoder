#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    string w;
    cin >> w;

    map<int, int> m;
    for (int i = 0; i < static_cast<int>(w.size()); i++) {
        m[w[i]]++;
    }

    bool res = true;
    for (map<int, int>::iterator i = m.begin(); i != m.end(); i++) {
        res = res && (i->second % 2 == 0);
    }

    cout << (res ? "Yes" : "No") << endl;
}
