#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    cin >> s;

    if (s.find("ooo") != string::npos) {
        cout << "o" << endl;
    } else if (s.find("xxx") != string::npos) {
        cout << "x" << endl;
    } else {
        cout << "draw" << endl;
    }
}
