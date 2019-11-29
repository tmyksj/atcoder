#include <iostream>
#include <set>

using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;

    set<int> s;
    s.insert(a);
    s.insert(b);
    s.insert(c);

    cout << s.size() << endl;
}
