#include <bits/stdc++.h>

using namespace std;

int main () {
    string a, b, c, d;
    cin >> a >> b >> c >> d;
    string e;
    d.pop_back();
    d.pop_back();
    while (d.back() != '(') {
            e.push_back(d.back());
            d.pop_back();
    }
    reverse(e.begin(), e.end());
    cout << "for (int " << b << " = 0; " << b << " < " << e << "; ++" << b << ") {";
    return 0;
}
