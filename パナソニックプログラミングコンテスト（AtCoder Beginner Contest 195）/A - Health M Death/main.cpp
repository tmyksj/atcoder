#include <iostream>

using namespace std;

int main() {
    int m, h;
    cin >> m >> h;
    cout << (h % m == 0 ? "Yes" : "No") << endl;
}
