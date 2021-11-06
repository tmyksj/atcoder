#include <iostream>
#include <string>

using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;
    cout << (s.find("1") % 2 == 0 ? "Takahashi" : "Aoki") << endl;
}
