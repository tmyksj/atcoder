#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }

    vector<bool> q(*max_element(p.begin(), p.end()) + 2, true);
    for (int i = 0, j = 0; i < n; i++) {
        for (q[p[i]] = false; !q[j]; j++) {}
        cout << j << endl;
    }
}
