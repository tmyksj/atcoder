#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<string> w(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }

    set<string> st;

    int r = 0;
    for (; r < n; r++) {
        if ((r == 0 || (r > 0 && w[r][0] == w[r - 1][w[r - 1].size() - 1])) && st.find(w[r]) == st.end()) {
            st.insert(w[r]);
        } else {
            break;
        }
    }

    cout << (r == n ? "DRAW" : (r % 2 == 0 ? "LOSE" : "WIN")) << endl;
}
