#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    if (108 * n / 100 < 206) {
        cout << "Yay!" << endl;
    } else if (108 * n / 100 == 206) {
        cout << "so-so" << endl;
    } else {
        cout << ":(" << endl;
    }
}
