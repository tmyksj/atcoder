#include <cstdlib>
#include <iostream>

using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    cout << (abs(a) < abs(b) ? "Ant" : (abs(a) == abs(b) ? "Draw" : "Bug")) << endl;
}
