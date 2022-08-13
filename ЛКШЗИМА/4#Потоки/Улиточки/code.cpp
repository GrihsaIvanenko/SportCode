#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6;

vector<int> reb;
vector<vector<int>> g;
vector<int> C, F, first, dust, used;

bool bfs(int S, int Fin) {
    dust.assign(g.size(), MAXN);
    dust[S] = 0;
    queue<int> q;
    q.push(S);
    while (!q.empty()) {
        int t = q.front();
        q.pop();
        for (auto x : g[t]) {
            if (dust[reb[x]] == MAXN && C[x] - F[x] > 0) {
                dust[reb[x]] = dust[t] + 1;
                q.push(reb[x]);
            }
        }
    }
    return dust[Fin] != MAXN;
}

int dfs(int v, int Fin, int p, int cmin = MAXN) {
    if (v == Fin)
        return cmin;
    while (first[v] < g[v].size()) {
        int id = g[v][first[v]];
        int u = reb[id];
        if ((dust[u] != dust[v] + 1) || (C[id] == F[id])) {
            ++first[v];
            continue;
        }
        int FF = dfs(u, Fin, v, min(cmin, C[id] - F[id]));
        if (FF == 0) {
            ++first[v];
            continue;
        }
        F[id] += FF;
        F[id ^ 1] -= FF;
        return FF;
    }
    return 0;
}

vector<int> way;

bool dfs1(int v, int fin) {
    if (v == fin) {
        used[fin] = 1;
        return true;
    }
    used[v] = 1;
    for (auto x : g[v]) {
        if (!used[reb[x]] && C[x] > 0 && dfs1(reb[x], fin)) {
            --C[x];
            way.push_back(v);
            return true;
        }
    }
    return false;
}

int main() {
    int n, m, SSS, TTT;
    cin >> n >> m >> SSS >> TTT;
    g.resize(n);
    dust.resize(n);
    C.resize(m + m);
    F.resize(C.size());
    first.resize(n);
    used.resize(n);
    --SSS;
    --TTT;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        if (a == b)
            continue;
        C[i + i] = 1;
        C[i + i + 1] = 1;
        g[a].push_back(reb.size());
        reb.push_back(b);
        g[b].push_back(reb.size());
        reb.push_back(a);
    }
    while (bfs(SSS, TTT)) {
        for (int i = 0; i < n; ++i)
            first[i] = 0;
        while (dfs(SSS, TTT, -1));
    }
    int sum = 0;
    for (auto x : g[SSS])
        sum += F[x];
    if (sum < 2) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    dfs1(SSS, TTT);
    reverse(way.begin(), way.end());
    for (auto x : way) {
        cout << x + 1 << " ";
    }
    cout << TTT + 1 << endl;
    way.clear();
    for (int i = 0; i < n; ++i) {
        used[i] = 0;
    }
    dfs1(SSS, TTT);
    reverse(way.begin(), way.end());
    for (auto x : way) {
        cout << x + 1 << " ";
    }
    cout << TTT + 1 << endl;
    return 0;
}


