#include <iostream>
#include <string>

using namespace std;

int main() {
    string x;
    cin >> x;
    cout << x.substr(0, x.find(".")) << endl;
}
