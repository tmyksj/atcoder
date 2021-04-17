#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main() {
    string s1, s2, s3;
    cin >> s1 >> s2 >> s3;

    string t = s1 + s2 + s3;
    sort(t.begin(), t.end());
    t.erase(unique(t.begin(), t.end()), t.end());

    map<int, int> c;
    for (int i = 0; i < static_cast<int>(t.size()); i++) {
        c[t[i]] = i;
    }

    long long n1 = -1, n2 = -1, n3 = -1;
    if (c.size() <= 10) {
        vector<int> p = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        do {
            if (p[c[s1[0]]] == 0 || p[c[s2[0]]] == 0 || p[c[s3[0]]] == 0) {
                continue;
            }

            long long m1 = 0;
            for (int i = 0; i < static_cast<int>(s1.size()); i++) {
                m1 = 10 * m1 + p[c[s1[i]]];
            }

            long long m2 = 0;
            for (int i = 0; i < static_cast<int>(s2.size()); i++) {
                m2 = 10 * m2 + p[c[s2[i]]];
            }

            long long m3 = 0;
            for (int i = 0; i < static_cast<int>(s3.size()); i++) {
                m3 = 10 * m3 + p[c[s3[i]]];
            }

            if (m1 + m2 == m3) {
                n1 = m1;
                n2 = m2;
                n3 = m3;
                break;
            }
        } while (next_permutation(p.begin(), p.end()));
    }

    if (n1 == -1) {
        cout << "UNSOLVABLE" << endl;
    } else {
        cout << n1 << endl;
        cout << n2 << endl;
        cout << n3 << endl;
    }
}
