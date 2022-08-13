#include <bits/stdc++.h>

using namespace std;

const int INF = 1<<30;

vector<int> rebs;

vector<int> C, F, first, dust;

vector<vector<int>> g;

bool bfs(int Cmin, int st = 0, int fin = g.size() - 1) {
    for (int i = 0; i < g.size(); ++i)
        dust[i] = INF;
    dust[st] = 0;
    deque<int> q;
    q.push_front(st);
    while (!q.empty()) {
        int t = q.front();
        q.pop_front();
        for (int i = 0; i < g[t].size(); ++i) {
            int id = g[t][i];
            int to = rebs[id];
            if (dust[to] == INF && Cmin <= C[id] - F[id]) {
                dust[to] = dust[t] + 1;
                q.push_back(to);
            }
       }
    }
    return dust[fin] != INF;
}

int dfs(int Cmin, int v = 0, int Cmax = INF, int fin = g.size() - 1) {
    if (v == fin)
        return Cmin;
    while (first[v] < g[v].size()) {
        int id = g[v][first[v]];
        int u = rebs[id];
        if ((dust[u] != dust[v] + 1) || (F[id] == C[id]) || Cmin > C[id] - F[id]) {
            ++first[v];
            continue;
        }
        int FF = dfs(Cmin, u, min(Cmax, C[id] - F[id]), fin);
        if (FF == 0) {
            ++first[v];
            continue;
        } else {
            F[id] += FF;
            F[id ^ 1]-=FF;
            return FF;
        }
    }
    return 0;
}

int main() {
    int n, m;
    cin >> n >> m;
    rebs.resize(m + m);
    C.resize(m + m);
    F.resize(m + m);
    g.resize(n);
    first.resize(n);
    dust.resize(n);
    for (int i = 0; i < m; ++i) {
        int a, b, cost;
        cin >> a >> b >> cost;
        --a;
        --b;
        g[a].push_back(i + i);
        g[b].push_back(i + i + 1);
        C[i + i] = cost;
        rebs[i + i] = b;
        rebs[i + i + 1] = a;
    }
    for (int Cmin = 1 << 30; Cmin > 0; Cmin>>=1) {
        while (bfs(Cmin)) {
            while (dfs(Cmin));
            for (int i = 0; i < n; ++i)
                first[i] = 0;
        }
    }
    long long sum = 0;
    for (int i = 0; i < g[0].size(); ++i) {
        sum += (long long)F[g[0][i]];
    }
    cout << sum << endl;
    for (int i = 0; i < m; ++i) {
        cout << F[i + i] << endl;
    }
    return 0;
}
