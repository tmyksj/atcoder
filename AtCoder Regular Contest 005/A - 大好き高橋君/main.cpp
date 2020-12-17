#include <iostream>
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

    int res = 0;
    for (int i = 0; i < n; i++) {
        if (w[i] == "TAKAHASHIKUN"
                || w[i] == "Takahashikun"
                || w[i] == "takahashikun"
                || w[i] == "TAKAHASHIKUN."
                || w[i] == "Takahashikun."
                || w[i] == "takahashikun.") {
            res++;
        }
    }

    cout << res << endl;
}
