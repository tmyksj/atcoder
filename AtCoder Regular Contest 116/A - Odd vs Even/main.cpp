#include <iostream>

using namespace std;

int main() {
    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        long long n;
        cin >> n;

        if (n % 4 == 0) {
            cout << "Even" << endl;
        } else if (n % 2 == 0) {
            cout << "Same" << endl;
        } else {
            cout << "Odd" << endl;
        }
    }
}
