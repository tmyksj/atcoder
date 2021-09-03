#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    cout << max(b - a + 1, 0) << endl;
}
