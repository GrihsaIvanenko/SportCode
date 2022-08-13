#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

vector<vector<int>> go;
vector<int>len;
vector<int>suf;
int last = 0;

int main () {
    go.push_back(vector<int>(26, -1));
    len.push_back(0);
    suf.push_back(-1);
    string s;
    cin >> s;
    long long ans = 0;
    for (auto x : s) {
        int new_last = go.size();
        go.push_back(vector<int>(26, -1));
        len.push_back(len[last] + 1);
        suf.push_back(-1);
        int p = last;
        while (p != -1 && go[p][x - 'a'] == -1) {
            go[p][x - 'a'] = new_last;
            p = suf[p];
        }
        if (p == -1) {
            suf[new_last] = 0;
            ans += (long long)(len[new_last]);
            last = new_last;
            cout << ans << endl;
            continue;
        }
        int q = go[p][x - 'a'];
        if (len[q] == len[p] + 1) {
            suf[new_last] = q;
            ans += (long long)(len[new_last] - len[q]);
            last = new_last;
            cout << ans << endl;
            continue;
        }
        int qcop = go.size();
        go.push_back(go[q]);
        suf.push_back(suf[q]);
        len.push_back(len[p] + 1);
        if (suf[qcop] != -1)
            ans += (long long)(len[qcop] - len[suf[qcop]]);
        if (suf[q] != -1)
            ans -= (long long)(len[q] - len[suf[q]]);
        suf[q] = qcop;
        ans += (long long)(len[q] - len[qcop]);
        suf[new_last] = qcop;
        ans += (long long)(len[new_last] - len[qcop]);
        while(p != -1 && go[p][x - 'a'] == q) {
            go[p][x - 'a'] = qcop;
            p = suf[p];
        }
        last = new_last;
        cout << ans << endl;
    }
    return 0;
}
