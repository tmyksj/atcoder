#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    set<int> s;
    for (int i = 0; i < n; i++) {
        s.insert(a[i]);
    }

    cout << (static_cast<int>(s.size()) == n ? "Yes" : "No") << endl;
}
