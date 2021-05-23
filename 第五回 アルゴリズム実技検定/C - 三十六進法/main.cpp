#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> v(0);
    for (int i = n; i > 0; i /= 36) {
        v.push_back(i % 36);
    }

    if (v.size() == 0) {
        v.push_back(0);
    }

    int p = v.size() - 1;
    for (; p > 0 && v[p] == 0; p--) {
    }

    for (; p >= 0; p--) {
        cout << static_cast<char>(0 <= v[p] && v[p] <= 9 ? '0' + v[p] : 'A' + v[p] - 10);
    }
    cout << endl;
}
