#include <iostream>

using namespace std;

int main() {
    int n, a, b;
    cin >> n >> a >> b;
    cout << ((n - 1) % (a + b) < a ? "Ant" : "Bug") << endl;
}
