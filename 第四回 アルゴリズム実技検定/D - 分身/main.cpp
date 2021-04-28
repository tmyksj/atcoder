#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;

    vector<int> v(1, 0);
    for (int i = 0; i < n; i++) {
        if (s[i] == '.') {
            v[v.size() - 1]++;
        } else {
            v.push_back(0);
        }
    }

    int x = v[0], y = v[v.size() - 1];
    x += max(*max_element(v.begin(), v.end()) - x - y, 0);

    cout << x << " " << y << endl;
}
