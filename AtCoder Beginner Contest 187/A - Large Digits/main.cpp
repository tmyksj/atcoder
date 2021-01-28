#include <algorithm>
#include <iostream>

using namespace std;

int s(int n) {
    return n > 0 ? s(n / 10) + n % 10 : 0;
}

int main() {
    int a, b;
    cin >> a >> b;
    cout << max(s(a), s(b)) << endl;
}
