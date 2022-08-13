#include <bits/stdc++.h>

using namespace std;


const int MAXM = 2400, MAXN = 1200;

bitset<MAXM> M;
bitset<MAXN> C;

int p[MAXN], R[MAXN], A[MAXM], B[MAXM], dust[MAXM], from[MAXM];

int get(int v) {
    if (p[v] == v)
        return v;
    return p[v] = get(p[v]);
}

void unite(int a, int b) {
    a = get(a);
    b = get(b);
    if (R[a] > R[b])
        swap(a, b);
    R[b] = max(R[b], R[a] + 1);
    p[a] = b;
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a,b;
        cin >> a >> b;
        M[i] = 0;
        M[i + m] = 0;
        C[i] = 0;
        --a;
        --b;
        A[i] = a;
        B[i] = b;
        A[i + m] = a + n;
        B[i + m] = b + n;
    }
    for (int iteration = 0; true; ++iteration) {
        vector<int> T;
        for (int i = 0; i < m + m; ++i)
            if (!M[i])
                if (!C[i % m])
                    T.push_back(i);
        if (T.size() == 0)
            break;
        vector<int> S1, S2;
        for (int i = 0; i < n + n; ++i) {
            p[i] = i;
            R[i] = 0;
        }
        for (int i = 0; i < m + m; ++i)
            if (M[i])
                unite(A[i], B[i]);
        for (int i = 0; i < m; ++i)
            if (!M[i])
                if (get(A[i]) != get(B[i]))
                    S1.push_back(i);
        for (int i = m; i < m + m; ++i)
            if (!M[i])
                if (get(A[i]) != get(B[i]))
                    S2.push_back(i);
        if (S1.size() + S2.size() == 0)
            break;
        vector<vector<int>> g(m + m);
        for (int pb = 0; pb < m + m; ++pb)
            if (M[pb]){
                if (pb < m) {
                    for (int i = 0; i < n; ++i) {
                        p[i] = i;
                        R[i] = 0;
                    }
                    for (int i = 0; i < m; ++i)
                        if (M[i] && (pb != i))
                            unite(A[i], B[i]);
                    for (int i = 0; i < m; ++i)
                        if (!M[i])
                            if (get(A[i]) != get(B[i]))
                                g[pb].push_back(i);
                } else {
                    for (int i = n; i < n + n; ++i) {
                        p[i] = i;
                        R[i] = 0;
                    }
                    for (int i = m; i < m + m; ++i)
                        if (M[i] && (pb != i))
                            unite(A[i], B[i]);
                    for (int i = m; i < m + m; ++i)
                        if (!M[i])
                            if (get(A[i]) != get(B[i]))
                                g[pb].push_back(i);
                }
            }
        for (int i = 0; i < m + m; ++i) {
            dust[i] = m + m + m + m + m;
            from[i] = -1;
        }
        queue<int> q;
        for (auto x : S1) {
            dust[x] = 0;
            from[x] = x;
            q.push(x);
        }
        for (auto x : S2) {
            dust[x] = 0;
            from[x] = x;
            q.push(x);
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            if (M[v]) {
                for (auto x : g[v])
                    if (dust[x] == m + m + m + m + m) {
                        dust[x] = dust[v] + 1;
                        from[x] = v;
                        q.push(x);
                    }
                if (v < m) {
                    for (auto x : S2) {
                        if (dust[x] == m + m + m + m + m) {
                            dust[x] = dust[v] + 1;
                            from[x] = v;
                            q.push(x);
                        }
                    }
                } else {
                    for (auto x : S1) {
                       if (dust[x] == m + m + m + m + m) {
                            dust[x] = dust[v] + 1;
                            from[x] = v;
                            q.push(x);
                        }
                    }
                }
            } else {
                int opp = 0;
                if (v < m)
                    opp = v + m;
                else
                    opp = v - m;
                if (dust[opp] == m + m + m + m + m) {
                    dust[opp] = dust[v] + 1;
                    from[opp] = v;
                    q.push(opp);
                }
                if (!C[v % m])
                    for (int i = 0; i < m + m; ++i)
                        if (M[i] && dust[opp] == m + m + m + m + m) {
                            dust[i] = dust[v] + 1;
                            from[i] = v;
                            q.push(i);
                        }
            }
        }
        int opt = T[0];
        for (auto x : T)
            if (dust[x] < dust[opt])
                opt = x;
        if (dust[opt] == m + m + m + m + m)
            break;
        vector<int> way = {opt};
        while (from[way.back()] != way.back())
            way.push_back(from[way.back()]);
        for (int i = 1; i < way.size(); ++(++i)) {
            M[way[i]] = 0;
            C[way[i] % m] = 0;
        }
        for (int i = 0; i < way.size(); ++(++i)) {
            M[way[i]] = 1;
            C[way[i] % m] = 1;
        }
    }
    for (int i = 0; i < m; ++i)
        if (M[i])
            cout << i + 1 << ' ';
    cout << '\n';
    for (int i = 0; i < m; ++i)
        if (!M[i])
            cout << i + 1 << ' ';
    cout << '\n';
    return 0;
}
