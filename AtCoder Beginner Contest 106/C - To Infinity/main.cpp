#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    long long k;
    cin >> s >> k;

    char res = s[0];
    for (int i = 1; i < static_cast<int>(s.size()) && i < k && res == '1'; i++) {
        res = s[i];
    }

    cout << res << endl;
}
