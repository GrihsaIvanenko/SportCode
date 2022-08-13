#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second

const int MAXN = 1000;

int mt[MAXN];

char used[MAXN];

vector<int> g[MAXN];

bool dfs(int v) {
    if (used[v] == 1) {
        return 0;
    }
    used[v] = 1;
    for (auto x : g[v]) {
        if (mt[x] == -1) {
            mt[x] = v;
            return true;
        } else if (dfs(mt[x])) {
            mt[x] = v;
            return true;
        }
    }
    return false;
}

void solve(){
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    for (int i = 0; i < MAXN; ++i) {
        mt[i] = -1;
        used[i] = 0;
    }
    int n;
    cin >> n;
    vector<pair<int, int>> victor(n);
    for (int i = 0; i < n; ++i) {
        cin >> victor[i].x;
        victor[i].y = i;
    }
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        for (int j = 0; j < t; ++j) {
            int v;
            cin >> v;
            --v;
            g[i].push_back(v);
        }
    }
    sort(victor.begin(), victor.end());
    reverse(victor.begin(), victor.end());
    for (int i = 0; i < n; ++i) {
        dfs(victor[i].y);
        for (int j = 0; j < MAXN; ++j) {
           used[j] = 0;
        }
    }
    vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
        if (mt[i] != -1) {
            ans[mt[i]] = i + 1;
        }
    }
    for (int i = 0; i < n; ++i){
        cout << ans[i] << " ";
    }
}

int main(){
    solve();
    return 0;
}
