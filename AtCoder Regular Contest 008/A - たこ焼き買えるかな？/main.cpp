#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    cout << min(100 * (n / 10) + 15 * (n % 10), 100 * ((n + 9) / 10)) << endl;
}
