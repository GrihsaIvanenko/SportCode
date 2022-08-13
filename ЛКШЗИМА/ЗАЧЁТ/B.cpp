#include <bits/stdc++.h>

using namespace std;

const int INF = 1<<30;

int EEE, FFF;

vector<int> rebs;

vector<int> C, F, first, dust;

vector<vector<int>> g;

bool bfs(int Cmin, int st = EEE, int fin = FFF) {
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

int dfs(int Cmin, int v = EEE, int Cmax = INF, int fin = FFF) {
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

int main () {
    int n;
    cin >> n;
    EEE = n + n;
    FFF = n + n + 1;
    int m = n * (n + 100);
    rebs.resize(m + m);
    C.resize(m + m);
    F.resize(m + m);
    g.resize(n + n + 100);
    first.resize(n + n + 100);
    dust.resize(n + n + 100);
    int get12 = 0, has12 = 0;
    vector<int> v1(n), v2(n);
    for (int i = 0; i < n; ++i) {
        cin >> v1[i];
        get12 += v1[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> v2[i];
        has12 += v2[i];
    }
    if (get12 != has12) {
        cout << "NO\n";
        return 0;
    }
    int cnt_timer = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = n; j < n + n; ++j) {
            rebs[cnt_timer] = j;
            C[cnt_timer] = 100;
            g[i].push_back(cnt_timer);
            ++cnt_timer;
            rebs[cnt_timer] = i;
            g[j].push_back(cnt_timer);
            ++cnt_timer;
        }
    }
    for (int i = 0; i < n; ++i) {
            rebs[cnt_timer] = i;
            C[cnt_timer] = v1[i];
            g[EEE].push_back(cnt_timer);
            ++cnt_timer;
            rebs[cnt_timer] = EEE;
            g[i].push_back(cnt_timer);
            ++cnt_timer;

            rebs[cnt_timer] = FFF;
            C[cnt_timer] = v2[i];
            g[i + n].push_back(cnt_timer);
            ++cnt_timer;
            rebs[cnt_timer] = i + n;
            g[FFF].push_back(cnt_timer);
            ++cnt_timer;
    }
    for (int Cmin = INF; Cmin > 0; Cmin>>=1) {
        while (bfs(Cmin)) {
            while (dfs(Cmin));
            for (int i = 0; i < n + n + 3; ++i)
                first[i] = 0;
        }
    }
    for (auto x : g[EEE])
        get12 -= F[x];
    for (auto x : g[FFF])
        has12 += F[x];
    if (get12 != 0 || has12 != 0) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES" << endl;
    vector<vector<int>> ans(n, vector<int>(n));
    for (int i = 0; i < cnt_timer; ++i) {
        if (i % 2 == 1 && rebs[i] < n && rebs[i ^ 1] < n + n && rebs[i ^ 1] >= n) {
            ans[rebs[i]][rebs[i ^ 1] - n] = -F[i];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
