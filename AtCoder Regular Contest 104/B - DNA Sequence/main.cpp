#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;

    vector<map<int, int>> v(n + 1);
    for (int i = 0; i < n; i++) {
        v[i + 1]['A'] += v[i]['A'];
        v[i + 1]['T'] += v[i]['T'];
        v[i + 1]['C'] += v[i]['C'];
        v[i + 1]['G'] += v[i]['G'];
        v[i + 1][s[i]]++;
    }

    int res = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (v[j]['A'] - v[i - 1]['A'] == v[j]['T'] - v[i - 1]['T']
                    && v[j]['C'] - v[i - 1]['C'] == v[j]['G'] - v[i - 1]['G']) {
                res++;
            }
        }
    }

    cout << res << endl;
}
