#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    cin >> s;
    cout << (s[0] != s[1] || s[1] != s[2] || s[2] != s[0] ? "Yes" : "No") << endl;
}
