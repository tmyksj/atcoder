#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

int main() {
    const double pi = 3.14159265358979323846264338327950288;

    int n;
    double x0, y0, x2, y2;
    cin >> n >> x0 >> y0 >> x2 >> y2;

    double xc = (x0 + x2) / 2;
    double yc = (y0 + y2) / 2;

    double t0 = atan((yc - y0) / (xc - x0)) - pi * (n - 2) / (2 * n);
    double a0 = sin(t0) / cos(t0);
    double b0 = y0 - a0 * x0;

    double tc = atan((yc - y0) / (xc - x0)) + 2 * pi / n - pi;
    double ac = sin(tc) / cos(tc);
    double bc = yc - ac * xc;

    double x1 = (bc - b0) / (a0 - ac);
    double y1 = a0 * x1 + b0;

    cout << setprecision(12) << fixed << x1 << " " << y1 << endl;
}
