#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string s;
    cin >> s;

    int res = 0;
    for (int i = 0; i < 10000; i++) {
        vector<int> c(10, 0);
        c[i % 10]++;
        c[i / 10 % 10]++;
        c[i / 100 % 10]++;
        c[i / 1000 % 10]++;

        bool r = true;
        for (int j = 0; j < 10; j++) {
            r = r && ((s[j] == 'o' && c[j] > 0) || (s[j] == 'x' && c[j] == 0) || s[j] == '?');
        }

        if (r) {
            res++;
        }
    }

    cout << res << endl;
}
