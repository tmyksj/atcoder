#include <iostream>
#include <set>
#include <string>

using namespace std;

int main() {
    set<string> st;
    for (int i = 0; i < 4; i++) {
        string s;
        cin >> s;
        st.insert(s);
    }

    cout << (st.size() == 4 ? "Yes" : "No") << endl;
}
