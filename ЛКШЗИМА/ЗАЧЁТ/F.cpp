#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

vector<vector<int>> go;
vector<int>len;
vector<int>suf;
vector<int> good;
int last = 0;

int main () {
    go.push_back(vector<int>(26, -1));
    len.push_back(0);
    suf.push_back(-1);
    good.push_back(1);
    string s;
    cin >> s;
    for (auto x : s) {
        int new_last = go.size();
        go.push_back(vector<int>(26, -1));
        len.push_back(len[last] + 1);
        suf.push_back(-1);
        good.push_back(1);
        int p = last;
        while (p != -1 && go[p][x - 'a'] == -1) {
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
        good.push_back(1);
        suf[q] = qcop;
        suf[new_last] = qcop;
        while(p != -1 && go[p][x - 'a'] == q) {
            go[p][x - 'a'] = qcop;
            p = suf[p];
        }
        last = new_last;
    }
    string T;
    cin >> T;
    int timer = 0;
    int ans = 0, gops = 0;
    for (auto x : T) {
        ++timer;
        int new_last = go.size();
        go.push_back(vector<int>(26, -1));
        len.push_back(len[last] + 1);
        suf.push_back(-1);
        good.push_back(0);
        int p = last;
        while (p != -1 && go[p][x - 'a'] == -1) {
            go[p][x - 'a'] = new_last;
            p = suf[p];
        }
        if (p != -1 && (ans < len[p] + 1) && good[p]) {
            ans = len[p] + 1;
            gops = timer - 1;
             string answ;
            for (int it = gops; gops - it <= ans && it >= 0; --it)
                answ.push_back(T[it]);
            reverse(answ.begin(), answ.end());
            cout << answ << endl;
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
        good.push_back(0);
        suf[q] = qcop;
        suf[new_last] = qcop;
        while(p != -1 && go[p][x - 'a'] == q) {
            if (p != -1 && (ans < len[p] + 1) && good[p]) {
                ans = len[p] + 1;
                gops = timer - 1;
                 string answ;
                for (int it = gops; gops - it <= ans && it >= 0; --it)
                    answ.push_back(T[it]);
                reverse(answ.begin(), answ.end());
                cout << answ << endl;
            }
            go[p][x - 'a'] = qcop;
            p = suf[p];
        }
        last = new_last;
    }
    return 0;
}
