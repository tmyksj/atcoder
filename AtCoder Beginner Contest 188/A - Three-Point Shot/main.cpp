#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    int x, y;
    cin >> x >> y;
    cout << (max(x, y) - min(x, y) < 3 ? "Yes" : "No") << endl;
}
