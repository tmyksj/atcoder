#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<string> x(n + 1, ".........");
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
    }

    int res = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 9; j++) {
            if (x[i][j] == 'x' || (x[i][j] == 'o' && x[i - 1][j] != 'o')) {
                res++;
            }
        }
    }

    cout << res << endl;
}
