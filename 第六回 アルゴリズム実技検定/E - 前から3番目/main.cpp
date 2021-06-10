#include <iostream>
#include <list>
#include <string>

using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;

    list<int> t;
    for (int i = 0; i < n; i++) {
        switch (s[i]) {
            case 'L':
                t.push_front(i + 1);
                break;
            case 'R':
                t.push_back(i + 1);
                break;
            case 'A':
                if (t.size() == 0) {
                    cout << "ERROR" << endl;
                } else {
                    cout << *t.begin() << endl;
                    t.pop_front();
                }
                break;
            case 'B':
                if (t.size() <= 1) {
                    cout << "ERROR" << endl;
                } else {
                    list<int>::iterator j = t.begin(); j++;
                    cout << *j << endl;
                    t.erase(j);
                }
                break;
            case 'C':
                if (t.size() <= 2) {
                    cout << "ERROR" << endl;
                } else {
                    list<int>::iterator j = t.begin(); j++; j++;
                    cout << *j << endl;
                    t.erase(j);
                }
                break;
            case 'D':
                if (t.size() == 0) {
                    cout << "ERROR" << endl;
                } else {
                    cout << *t.rbegin() << endl;
                    t.pop_back();
                }
                break;
            case 'E':
                if (t.size() <= 1) {
                    cout << "ERROR" << endl;
                } else {
                    list<int>::iterator j = t.end(); j--; j--;
                    cout << *j << endl;
                    t.erase(j);
                }
                break;
            case 'F':
                if (t.size() <= 2) {
                    cout << "ERROR" << endl;
                } else {
                    list<int>::iterator j = t.end(); j--; j--; j--;
                    cout << *j << endl;
                    t.erase(j);
                }
                break;
        }
    }
}
