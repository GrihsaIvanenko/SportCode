#include <bits/stdc++.h>

using namespace std;

#define int long long
struct nd {
    vector<int> next;
    int suf, p, len;
    int my_char;
    long long kolvo_putey = 0;
    long long CSV = 0;
    int term = 0;
    int used = 0;
    nd() {
        next.assign(10, -1);
        suf = -1;
        p = -1;
        len = 0;
        my_char = -1;
    }
};

struct IMBA {
    vector<nd> s;
    int last = -1;
    IMBA() {
        s.push_back(nd());
        last = 0;
    }
    void dfsd() {
        int tmp = last;
        while (tmp != -1) {
            s[tmp].term = 1;
            tmp = s[tmp].suf;
        }
    }
    int add(int A, int lox) {
        int B = s.size();
        s.push_back(nd());
        s[B].my_char = lox;
        s[B].len = s[A].len + 1;
        s[B].p = A;
        s[B].suf = 0;
        for (; A != -1; A = s[A].suf) {
            if (s[A].next[lox] == -1) {
                s[A].next[lox] = B;
                continue;
            }
            int C = s[A].next[lox];
            if (s[C].p == A) {
                s[B].suf = C;
                break;
            }
            int D = s.size();
            s.push_back(nd());
            s[D].len = s[A].len + 1;
            s[D].my_char = s[C].my_char;
            s[D].suf = s[C].suf;
            s[C].suf = D;
            s[B].suf = D;
            s[D].p = A;
            s[D].next = s[C].next;
            for (; A != -1 && s[A].next[lox] == C; A = s[A].suf)
                s[A].next[lox] = D;
            break;
        }
        return last = s[s[B].p].next[lox];
    }
    long long dfs(int v = 0) {
        long long cur = 0;
        s[v].kolvo_putey = s[v].term;
        s[v].used = 1;
        for (auto x : s[v].next) {
            if (x == -1)
            continue;
            if (s[x].used == 0) {
                cur = max(cur, dfs(x));
            } else
                cur = max(cur, s[x].CSV);
            s[v].kolvo_putey += s[x].kolvo_putey;
        }
        s[v].CSV = s[v].kolvo_putey * s[v].len;
        return max(cur, s[v].CSV);
    }
    void printer() {
        vector<int> used(s.size());
        print(used);
    }
    void print(vector<int> &used, int v = 0) {
        if (used[v])
            return;
        used[v] = 1;
        cout << v << " " << s[v].suf << ": ";
        for (int i = 0; i < 10; ++i)
            if (s[v].next[i] != -1) {
                cout << i << " " << s[v].next[i] << "; ";
            }
        cout << endl;
        for (int i = 0; i < 10; ++i) {
            if (s[v].next[i] != -1) {
                print(used, s[v].next[i]);
            }
        }
    }
    void vosst(int x, vector<int> &rese) {
        while (x != -1) {
            rese.push_back(s[x].my_char);
            x = s[x].p;
        }
    }
};

signed main() {
    IMBA AVT;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        --t;
        AVT.add(AVT.last, t);
    }
    AVT.dfsd();
    long long res = AVT.dfs();
    for (int i = 0; i < AVT.s.size(); ++i) {
        if (AVT.s[i].CSV == res) {
            vector<int> rese;
            AVT.vosst(i, rese);
            rese.pop_back();
            reverse(rese.begin(), rese.end());
            cout << AVT.s[i].CSV << '\n' << AVT.s[i].len << '\n';
            for (auto x : rese)
                cout << x + 1 << ' ';
            cout << endl;
            return 0;
        }
    }
    return 0;
}

