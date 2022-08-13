#include <bits/stdc++.h>

using namespace std;

int main () {
    //freopen("peep.in", "r", stdin);
    //freopen("peep.out", "w", stdout);
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];
    sort(v.rbegin(), v.rend());
    long long ans = 0;
    set<pair<int, pair<int>> s;
    for (int i = 0; i < v.size(); ++i)
        s.insert({v[i], i});
    while (!s.empty() && (*s.rbegin()).first != 0) {
        int it = (*s.rbegin()).first;
        int pos = (*s.rbegin()).second;
        ans += (long long)v[pos];
        s.erase(*s.rbegin());
        int eld_bit = -1;
        int it_copy = it;
        while (it_copy > 0) {
            it_copy /= 2;
            ++eld_bit;
        }
        set<pair<int, int>> S1;
        for (auto x : s)
            if (x.first >= (1<<eld_bit))
                S1.insert({x.first ^ it, pos});
            else
                S1.insert(x);
        swap(s, S1);
    }
    cout << ans << endl;
    return 0;
}
