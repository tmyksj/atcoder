#include <iostream>

using namespace std;

int main() {
    int sx, sy, tx, ty;
    cin >> sx >> sy >> tx >> ty;

    for (int i = sx; i < tx; i++) {
        cout << "R";
    }

    for (int i = sy; i < ty; i++) {
        cout << "U";
    }

    cout << "R";

    for (int i = ty; i > sy - 1; i--) {
        cout << "D";
    }

    for (int i = tx + 1; i > sx; i--) {
        cout << "L";
    }

    cout << "U";

    for (int i = sy; i < ty; i++) {
        cout << "U";
    }

    for (int i = sx; i < tx; i++) {
        cout << "R";
    }

    cout << "U";

    for (int i = tx; i > sx - 1; i--) {
        cout << "L";
    }

    for (int i = ty + 1; i > sy; i--) {
        cout << "D";
    }

    cout << "R" << endl;
}
