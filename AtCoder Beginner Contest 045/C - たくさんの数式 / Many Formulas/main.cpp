#include <iostream>
#include <string>

using namespace std;

long long dfs(string s, int b, int e, long long c) {
    long long r = s[b] - '0';
    for (int i = b + 1; i < e; i++) {
        r *= 10;
        r += s[i] - '0';
    }

    return (static_cast<int>(s.size()) == e ? c + r : dfs(s, b, e + 1, c) + dfs(s, e, e + 1, c + r));
}

int main() {
    string s;
    cin >> s;
    cout << dfs(s, 0, 1, 0) << endl;
}
