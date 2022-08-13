#include <bits/stdc++.h>

using namespace std;

int kolvo(int t) {
    if (t == 0)
        return 0;
    return t % 2 + kolvo(t / 2);
}

int main() {
    int n, m;
    cin >> n >> m;
    set<int> s;
    for (int i = 0; i < m; ++i) {
        int numb = 0;
        int sz;
        cin >> sz;
        for (int i = 0; i < sz; ++i) {
            int tmp;
            cin >> tmp;
            numb |= (1 << (tmp - 1));
        }
        s.insert(numb);
    }
    if (s.size() == 0 || *s.begin() != 0) {
        cout << "NO\n";
        return 0;
    }
    for (auto x : s) {
        for (int j = x; j > 0; j = (j - 1) & x)
            if (s.find(j) == s.end()) {
                cout << "NO\n";
                return 0;
            }
    }
    for (auto x : s) {
        for (auto y : s) {
            if (kolvo(x) > kolvo(y)) {
                bool nashlos = 0;
                for (int kk = 0; kk < n; ++kk) {
                    if (((1 << kk) & x) && (!((1 << kk) & y)))
                        if (s.find(((1 << kk) | y)) != s.end())
                            nashlos = 1;
                }
                if (!nashlos) {
                    cout << "NO\n";
                    return 0;
                }
            }
        }
    }
    cout << "YES\n";
    return 0;
}
