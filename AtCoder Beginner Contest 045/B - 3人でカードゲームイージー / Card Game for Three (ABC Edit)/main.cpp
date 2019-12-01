#include <iostream>
#include <string>

using namespace std;

int main() {
    string sa, sb, sc;
    cin >> sa >> sb >> sc;

    sa += ".";
    sb += ".";
    sc += ".";

    string res = "";
    for (int ia = 0, ib = 0, ic = 0, t = 0;
            ia < static_cast<int>(sa.size())
                    && ib < static_cast<int>(sb.size())
                    && ic < static_cast<int>(sc.size()); ) {
        if (t == 0) {
            t = sa[ia++] - 'a';
            res = "A";
        } else if (t == 1) {
            t = sb[ib++] - 'a';
            res = "B";
        } else {
            t = sc[ic++] - 'a';
            res = "C";
        }
    }

    cout << res << endl;
}
