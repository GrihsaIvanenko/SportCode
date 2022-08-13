#include <bits/stdc++.h>

using namespace std;

int main() {
    string A;
    cin >> A;
    int n;
    cin >> n;
    int ST, k;
    cin >> ST >> k;
    --ST;
    vector<int> term(n);
    for (int i = 0; i < k; ++i) {
        int t;
        cin >> t;
        term[t - 1] = 1;
    }
    vector<vector<vector<int>>> revg(n, vector<vector<int>>(A.size()));
    vector<vector<int>> g(n, vector<int> (A.size()));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < A.size(); ++j) {
            int t;
            cin >> t;
            --t;
            revg[t][j].push_back(i);
            g[i][j] = t;
        }
    }
    vector<vector<int>> dif(n, vector<int>(n));
    deque<pair<int, int>> q;
    for (int i = 0; i < n; ++i) {
        if (!term[i])
            continue;
        for (int j = 0; j < n; ++j) {
            if (term[j])
                continue;
            q.push_back({i, j});
            q.push_back({j, i});
            dif[i][j] = 1;
            dif[j][i] = 1;
        }
    }
    while (!q.empty()) {
        pair<int, int> tmp = q.front();
        q.pop_front();
        int a = tmp.first, b = tmp.second;
        for (int i = 0; i < A.size(); ++i) {
            for (auto x : revg[a][i])
                for (auto y : revg[b][i])
                    if (!dif[x][y]){
                        dif[x][y] = 1;
                        dif[y][x] = 1;
                        q.push_back({x, y});
                        q.push_back({y, x});
                    }
        }
    }
    int timer = 0;
    vector<int> renamer(n, -1);
    for (int i = 0; i < n; ++i) {
        if (renamer[i] == -1) {
            renamer[i] = timer++;
            for (int j = i + 1; j < n; ++j) {
                if (renamer[j] == -1 && dif[i][j] == 0)
                    renamer[j] = renamer[i];
            }
        }
    }
    vector<vector<int>> newg(timer, vector<int>(A.size()));
    ST = renamer[ST];
    set<int> terms;
    for (int i = 0; i < n; ++i)
        if (term[i])
            terms.insert(renamer[i]);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < A.size(); ++j) {
            newg[renamer[i]][j] = renamer[g[i][j]];
        }
    }
    vector<vector<int>> ansg;
    vector<int> added(timer);
    set<int> queqe;
    queqe.insert(ST);
    vector<int> rerename(timer);
    timer = 0;
    while (!queqe.empty()) {
        int it = *queqe.begin();
        queqe.erase(*queqe.begin());
        if (added[it])
            continue;
        added[it] = 1;
        rerename[it] = timer++;
        for (auto x : newg[it])
            queqe.insert(x);
        ansg.push_back(newg[it]);
    }
    for (int i = 0; i < ansg.size(); ++i) {
        for (int j = 0; j < ansg[i].size(); ++j) {
            ansg[i][j] = rerename[ansg[i][j]];
        }
    }
    vector<int> terrms;
    for (auto x : terms)
        if (added[x])
            terrms.push_back(rerename[x]);
    ST = rerename[ST];
    cout << timer << endl << ST + 1 << " " << terrms.size() << " ";
    for (auto x : terrms)
        cout << x + 1 << " ";
    cout << endl;
    for (int i = 0; i < timer; ++i) {
        for (auto x : ansg[i])
            cout << x + 1 << " ";
        cout << endl;
    }
    return 0;
}
