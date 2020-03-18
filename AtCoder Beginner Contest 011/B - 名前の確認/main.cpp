#include <iostream>
#include <locale>
#include <string>

using namespace std;

int main() {
    string s;
    cin >> s;

    s[0] = toupper(s[0]);
    for (int i = 1; i < static_cast<int>(s.size()); i++) {
        s[i] = tolower(s[i]);
    }

    cout << s << endl;
}
