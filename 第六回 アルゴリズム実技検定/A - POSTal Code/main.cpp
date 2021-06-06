#include <iostream>
#include <regex>

using namespace std;

int main() {
    string s;
    cin >> s;

    regex re("^\\d{3}-\\d{4}$");
    cout << (regex_match(s, re) ? "Yes" : "No") << endl;
}
