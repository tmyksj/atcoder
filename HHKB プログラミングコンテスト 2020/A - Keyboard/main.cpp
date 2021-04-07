#include <iostream>
#include <string>

using namespace std;

int main() {
    string s, t;
    cin >> s >> t;
    cout << static_cast<char>(s == "Y" ? t[0] + 'A' - 'a' : t[0]) << endl;
}
