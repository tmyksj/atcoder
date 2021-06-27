#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    long long res = 0;
    map<int, int> b;
    for (int i = 1; i < n; i++) {
        b[a[i - 1]]++;
        res += i - b[a[i]];
    }

    cout << res << endl;
}
