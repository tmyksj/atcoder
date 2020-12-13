#include <algorithm>
#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    int n, m;
    string name, kit;
    cin >> n >> m >> name >> kit;

    map<int, int> name_map;
    for (int i = 0; i < n; i++) {
        name_map[name[i]]++;
    }

    map<int, int> kit_map;
    for (int i = 0; i < m; i++) {
        kit_map[kit[i]]++;
    }

    int res = 0;
    for (map<int, int>::iterator i = name_map.begin(); i != name_map.end(); i++) {
        if (kit_map[i->first] == 0) {
            res = -1;
            break;
        }

        res = max(res, (i->second + kit_map[i->first] - 1) / kit_map[i->first]);
    }

    cout << res << endl;
}
