#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int_fast16_t> w(n);
    for (int i = 0; i < n; ++i) {
        cin >> w[i];
    }
    set<int> cycles;
    for (int i = 0; i < m; ++i) {
        int t;
        cin >> t;
        int CYS = 0;
        for (int j = 0; j < t; ++j) {
            int tmp;
            cin >> tmp;
            --tmp;
            CYS |= (1 << tmp);
        }
        cycles.insert(CYS);
    }
    int cnt = 0;
    while (cnt++ < 5) {
        bool fin = 0;
        for (auto x : cycles) {
            for (auto y : cycles) {
                if (((x ^ y) != 0) && ((x | y) != (x + y)) && ((x | y) != max(x, y)) && cycles.find(x ^ y) == cycles.end()) {
                    fin = 1;
                    cycles.insert(x ^ y);
                }
                if (fin)
                    break;
            }
            if (fin)
                break;
        }
        if (fin)
            continue;
        break;
    }
    vector<int> is_cycle((1 << n), 0);
    for (int mask = 0; mask < (1 << n); ++mask) {
        if (cycles.find(mask) != cycles.end()) {
            is_cycle[mask] = 1;
            continue;
        }
        for (int j = 0; j < n; ++j)
            if (mask & (1 << j))
                is_cycle[mask] |= is_cycle[mask - (1 << j)];
    }
    int ans = 0;
    for (int mask = (1 << n) - 1; mask >= 0; --mask) {
        if (is_cycle[mask])
            continue;
        int cur_w = 0;
        for (int j = 0; j < n; ++j)
            if (mask & (1 << j))
                cur_w += w[j];
        ans = max(ans, cur_w);
    }
    cout << ans << endl;
    return 0;
}
