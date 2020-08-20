#include <iostream>

using namespace std;

int main() {
    int h, w;
    cin >> h >> w;
    cout << h * (w - 1) + (h - 1) * w << endl;
}
