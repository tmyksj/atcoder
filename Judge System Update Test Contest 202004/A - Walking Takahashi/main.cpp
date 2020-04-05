#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    int s, l, r;
    cin >> s >> l >> r;
    cout << min(max(s, l), r) << endl;
}
