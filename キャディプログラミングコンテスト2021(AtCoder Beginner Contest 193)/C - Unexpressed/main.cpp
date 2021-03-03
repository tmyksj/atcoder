#include <iostream>
#include <set>

using namespace std;

int main() {
    long long n;
    cin >> n;

    set<long long> s;
    for (long long i = 2; i * i <= n; i++) {
        for (long long j = i * i; j <= n; j *= i) {
            s.insert(j);
        }
    }

    cout << n - s.size() << endl;
}
