#include <iostream>
#include <string>

using namespace std;

int main() {
    string n;
    cin >> n;
    cout << (n.find("7") != string::npos ? "Yes" : "No") << endl;
}
