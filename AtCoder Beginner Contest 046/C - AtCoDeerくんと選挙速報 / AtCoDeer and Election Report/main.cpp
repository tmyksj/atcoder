#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    long long t = 1, a = 1;
    for (int i = 0; i < n; i++) {
        long long ti, ai;
        cin >> ti >> ai;

        long long n = max((t + ti - 1) / ti, (a + ai - 1) / ai);
        t = n * ti;
        a = n * ai;
    }

    cout << t + a << endl;
}
