#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    cout << (n / 10 == 9 || n % 10 == 9 ? "Yes" : "No") << endl;
}
