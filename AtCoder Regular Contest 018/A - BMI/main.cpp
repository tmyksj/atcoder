#include <iomanip>
#include <iostream>

using namespace std;

int main() {
    double height, bmi;
    cin >> height >> bmi;
    cout << setprecision(12) << fixed << height * height * bmi / 10000 << endl;
}
