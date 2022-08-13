#include <bits/stdc++.h>

using namespace std;

const int INF = 100;

int n;

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


int dfs(int Cmin, int v, int Cmax, int fin) {
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

int get_potok(int S, int Fin) {
    for (int i = 0; i < rebs.size(); ++i) {
        C[i] = 1;
        F[i] = 0;
    }
    while (bfs(1, S, Fin)) {
            for (int i = 0; i < n; ++i)
                first[i] = 0;
            while (dfs(1, S, INF, Fin));
        }
    int sum = 0;
    for (int i = 0; i < g[S].size(); ++i) {
        sum += F[g[S][i]];
    }
    return sum;
}

void imba_potok(int ST, int FIN, int n) {
    for (int i = 0; i < rebs.size(); ++i) {
        C[i] = 1;
        F[i] = 0;
    }
    while (bfs(1, ST, FIN)) {
            for (int i = 0; i < n; ++i)
                first[i] = 0;
            while (dfs(1, ST, INF, FIN));
        }
    queue<int> q;
    q.push(ST);
    vector<int> used(n);
    set<int> ans;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (used[v])
            continue;
        used[v] = 1;
        ans.insert(v);
        for (auto x : g[v])
            if (C[x] - F[x] > 0)
                q.push(rebs[x]);
    }
    for (auto x : ans) {
        cout << x + 1 << " ";
    }
    cout << endl;
    for (int i = 0; i < n; ++i)
        if (ans.find(i) == ans.end())
            cout << i + 1 << " ";
    cout << endl;
}

int main() {
    cin >> n;
    g.resize(n);
    dust.resize(n);
    first.resize(n);
    vector<vector<char>> v(n, vector<char>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> v[i][j];
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (v[i][j] - '0') {
                g[i].push_back(rebs.size());
                rebs.push_back(j);
                g[j].push_back(rebs.size());
                rebs.push_back(i);
            }
        }
    }
    C.resize(rebs.size());
    F.resize(rebs.size());
    int opt_sz = rebs.size() + 1, optx = 1, opty = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int cur = get_potok(i, j);
            if (cur < opt_sz) {
                opt_sz = cur;
                optx = i;
                opty = j;
            }
        }
    }
    imba_potok(optx, opty, n);
    return 0;
}
