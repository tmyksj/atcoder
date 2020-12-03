#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    string day;
    cin >> day;

    map<string, int> m;
    m["Sunday"] = 0;
    m["Monday"] = 5;
    m["Tuesday"] = 4;
    m["Wednesday"] = 3;
    m["Thursday"] = 2;
    m["Friday"] = 1;
    m["Saturday"] = 0;

    cout << m[day] << endl;
}
