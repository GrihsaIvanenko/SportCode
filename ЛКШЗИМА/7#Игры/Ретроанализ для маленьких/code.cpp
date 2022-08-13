#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300000;

vector<int> g[MAXN];

int win[MAXN], step[MAXN], used[MAXN], n;

void solve() {
    for (int i = 0; i < n; ++i) {
        win[i] = -1;
        step[i] = 0;
        g[i].clear();
        used[i] = 0;
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        ++step[a];
        g[b].push_back(a);
    }
    queue<int> q;
    for (int i = 0; i < n; ++i)
        if (step[i] == 0) {
            win[i] = 0;
            q.push(i);
            used[i] = 1;
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
                --step[x];
                if (step[x] == 0) {
                    win[x] = 0;
                    used[x] = 1;
                    q.push(x);
                }
            }
        }
    }
    for (int i = 0; i < n; ++i)
        if (!used[i])
            win[i] = 1;
    for (int i = 0; i < n; ++i)
        if (win[i] == 0)
            cout << "SECOND\n";
        else if (win[i] == 1)
            cout << "DRAW\n";
        else
            cout << "FIRST\n";
}

int main() {
    while (cin >> n) {
        solve();
    }
    return 0;
}
