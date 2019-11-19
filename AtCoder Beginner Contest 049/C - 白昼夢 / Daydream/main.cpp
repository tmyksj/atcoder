#include <iostream>
#include <queue>
#include <string>

using namespace std;

bool match(int b, string s, string t) {
    for (int i = 0; i < static_cast<int>(t.size()); i++) {
        if (b + i >= static_cast<int>(s.size()) || s[b + i] != t[i]) {
            return false;
        }
    }

    return true;
}

int main() {
    string s;
    cin >> s;

    bool res = false;

    queue<int> que;
    que.push(0);
    while (!que.empty()) {
        int idx = que.front();
        que.pop();

        if (idx == static_cast<int>(s.size())) {
            res = true;
            break;
        }

        if (match(idx, s, "dream")) { que.push(idx + 5); }
        if (match(idx, s, "dreamer")) { que.push(idx + 7); }
        if (match(idx, s, "erase")) { que.push(idx + 5); }
        if (match(idx, s, "eraser")) { que.push(idx + 6); }
    }

    cout << (res ? "YES" : "NO") << endl;
}
