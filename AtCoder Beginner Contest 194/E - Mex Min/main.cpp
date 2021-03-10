#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    set<int> st;
    for (int i = 0; i <= n; i++) {
        st.insert(i);
    }

    map<int, int> mp;
    for (int i = 0; i < m; i++) {
        st.erase(a[i]);
        mp[a[i]]++;
    }

    int res = *st.begin();
    for (int i = m; i < n; i++) {
        mp[a[i - m]]--;
        if (mp[a[i - m]] == 0) {
            st.insert(a[i - m]);
        }

        st.erase(a[i]);
        mp[a[i]]++;

        res = min(res, *st.begin());
    }

    cout << res << endl;
}
