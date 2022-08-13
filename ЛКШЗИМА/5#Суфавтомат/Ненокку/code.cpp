#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> go;

vector<int> suf, len;

int last = 0;

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    go.push_back(vector<int>(26, -1));
    suf.push_back(-1);
    len.push_back(0);
    char t;
    while (cin >> t) {
        string it;
        cin >> it;
        for (int i = 0; i < it.size(); ++i) {
            if ('A' <= it[i] && it[i] <= 'Z')
                it[i] = 'a' + it[i] - 'A';
        }
        if (t == '?') {
            int id = 0;
            bool skipped = false;
            for (auto x : it) {
                id = go[id][x - 'a'];
                if (id == -1) {
                    cout << "NO\n";
                    skipped = true;
                    break;
                }
            }
            if (!skipped) {
                cout << "YES\n";
            }
        } else {
            for (auto x : it) {
                int new_last = go.size();
                go.push_back(vector<int>(26, -1));
                suf.push_back(-1);
                len.push_back(len[last] + 1);
                int p = last;
                for (; p != -1 && go[p][x - 'a'] == -1; ) {
                    go[p][x - 'a'] = new_last;
                    p = suf[p];
                }
                if (p == -1) {
                    suf[new_last] = 0;
                    last = new_last;
                    continue;
                }
                int q = go[p][x - 'a'];
                if (len[q] == len[p] + 1) {
                    suf[new_last] = q;
                    last = new_last;
                    continue;
                }
                int qcop = go.size();
                go.push_back(go[q]);
                suf.push_back(suf[q]);
                len.push_back(len[p] + 1);
                suf[new_last] = qcop;
                suf[q] = qcop;
                for (;p != -1 && go[p][x - 'a'] == q;) {
                    go[p][x - 'a'] = qcop;
                    p = suf[p];
                }
                last = new_last;
            }
        }
    }
    return 0;
}
