#include <iostream>
#include <set>

using namespace std;

int main() {
    long long n;
    cin >> n;

    set<long long> s;
    for (long long i = 2; i * i <= n - 1; i++) {
        if ((n - 1) % i == 0) {
            s.insert(i);
            s.insert((n - 1) / i);
        }
    }

    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            long long j = n;
            while (j % i == 0) {
                j /= i;
            }
            if (j % i == 1) {
                s.insert(i);
            }

            long long k = n;
            while (k % (n / i) == 0) {
                k /= (n / i);
            }
            if (k % (n / i) == 1) {
                s.insert(n / i);
            }
        }
    }

    if (n > 2) {
        s.insert(n - 1);
    }

    s.insert(n);

    cout << s.size() << endl;
}
