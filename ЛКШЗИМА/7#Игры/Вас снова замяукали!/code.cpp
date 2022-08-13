#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100000, INF = 1e9 + 7;

vector<int> g[MAXN];

int st[MAXN], used[MAXN], win[MAXN];

int main() {
    for (int i = 0; i < MAXN; ++i) {
        st[i] = 0;
        win[i] = -1;
        used[i] = 0;
    }
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        ++st[a];
        g[b].push_back(a);
    }
    queue<int> q;
    vector<int> dust(n, INF);
    for (int i = 0; i < n; ++i)
        if (!st[i]) {
            q.push(i);
            used[i] = 1;
            win[i] = 0;
            dust[i] = 0;
        }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (win[v] == 0) {
            for (auto x : g[v]) {
                if (used[x])
                    continue;
                win[x] = 2;
                q.push(x);
                used[x] = 1;
            }
        }
        if (win[v] == 2) {
            for (auto x : g[v]) {
                if (used[x])
                    continue;
                --st[x];
                if (!st[x]) {
                    win[x] = 0;
                    used[x] = 1;
                    q.push(x);
                }
            }
        }
    }

    return 0;
}
