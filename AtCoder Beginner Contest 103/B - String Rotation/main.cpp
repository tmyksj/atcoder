#include <iostream>
#include <string>

using namespace std;

int main() {
    string s, t;
    cin >> s >> t;
    cout << ((s + s).find(t) != string::npos ? "Yes" : "No") << endl;
}
