#include <bits/stdc++.h>

using namespace std;

int_fast16_t get(int_fast16_t v, vector<int_fast16_t> &pr) {
    if (pr[v] == v)
        return v;
    return pr[v] = get(pr[v], pr);
}

void unite(int_fast16_t a, int_fast16_t b, vector<int_fast16_t> &pr) {
    a = get(a, pr);
    b = get(b, pr);
    pr[a] = b;
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int_fast16_t n, m;
    cin >> n >> m;
    vector<int_fast16_t> A(m), B(m), C(m);
    bitset<5000> matroid;
    bitset<200> cnt;
    for (int_fast16_t i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a;
        --b;
        --c;
        A[i] = a;
        B[i] = b;
        C[i] = c;
    }
    for (int_fast16_t iter = 0; iter < m; ++iter) {
        vector<vector<int_fast16_t>> g(m);
        vector<int_fast16_t> pr(n);
        for (int_fast16_t i = 0; i < n; ++i)
            pr[i] = i;
        for (int_fast16_t i = 0; i < m; ++i)
            if (matroid[i])
                unite(A[i], B[i], pr);
        vector<int_fast16_t> S, T;
        for (int_fast16_t i = 0; i < m; ++i)
            if (!matroid[i])
                if (!cnt[C[i]])
                    S.push_back(i);
        if (S.size() == 0)
            break;
        for (int_fast16_t i = 0; i < m; ++i)
            if (!matroid[i])
                if (get(A[i], pr) != get(B[i], pr))
                    T.push_back(i);
        if (T.size() == 0)
            break;
        for (int_fast16_t pos_ban = 0; pos_ban < m; ++pos_ban) {
            if (!matroid[pos_ban])
                continue;
            for (int_fast16_t i = 0; i < n; ++i)
                pr[i] = i;
            for (int_fast16_t i = 0; i < m; ++i)
                if (matroid[i] && i != pos_ban)
                    unite(A[i], B[i], pr);
            for (int_fast16_t i = 0; i < m; ++i)
                if (!matroid[i])
                    if (get(A[i], pr) != get(B[i], pr))
                        g[i].push_back(pos_ban);
            cnt[C[pos_ban]] = false;
            for (int_fast16_t i = 0; i < m; ++i)
                if (!matroid[i])
                    if (!cnt[C[i]])
                        g[pos_ban].push_back(i);
            cnt[C[pos_ban]] = true;
        }
        vector<int_fast16_t> from(m), dust(m, m);
        queue<int_fast16_t> q;
        for (auto x : S) {
            from[x] = x;
            dust[x] = 0;
            q.push(x);
        }
        while (!q.empty()) {
            int_fast16_t v = q.front();
            q.pop();
            for (auto x : g[v])
                if (dust[x] == m) {
                    dust[x] = dust[v] + 1;
                    from[x] = v;
                    q.push(x);
                }
        }
        int_fast16_t cur = T[0];
        for (auto x : T)
            if (dust[x] < dust[cur])
                cur = x;
        if (dust[cur] == m)
            break;
        vector<int_fast16_t> way = {cur};
        while (from[cur] != cur) {
            cur = from[cur];
            way.push_back(cur);
        }
        for (int_fast16_t i = 1; i < way.size(); ++(++i)) {
            matroid[way[i]] = 0;
            cnt[C[way[i]]] = 0;
        }
        for (int_fast16_t i = 0; i < way.size(); ++(++i)) {
            matroid[way[i]] = 1;
            cnt[C[way[i]]] = 1;
        }
    }
    int_fast16_t ans = 0;
    for (int_fast16_t i = 0; i < m; ++i)
        if (matroid[i])
            ++ans;
    cout << ans << '\n';
    for (int_fast16_t i = 0; i < m; ++i)
        if (matroid[i])
            cout << i + 1 << ' ';
    cout << '\n';
    return 0;
}
