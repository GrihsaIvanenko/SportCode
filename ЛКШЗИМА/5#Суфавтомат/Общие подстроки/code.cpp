#include <bits/stdc++.h>

using namespace std;

struct z {
    vector<int> t;
    int s, p, l, u, k;
    z() {
        t.assign(26, -1);
        s = -1;
        p = -1;
        l = 0;
        u = 0;
        k = 0;
    }
};

vector<z> s;

int add(int A, char x) {
    x -= 'a';
    int B = s.size();
    s.push_back(z());
    s[B].l = s[A].l + 1;
    s[B].s = 0;
    s[B].p = A;
    for (; A != -1; A = s[A].s) {
        if (s[A].t[x] == -1) {
            s[A].t[x] = B;
            continue;
        }
        int C = s[A].t[x];
        if (s[C].p == A) {
            s[B].s = C;
            break;
        }
        int D = s.size();
        s.push_back(z());
        s[D].t = s[C].t;
        s[D].s = s[C].s;
        s[D].p = A;
        s[D].l = s[A].l + 1;
        s[C].s = D;
        s[B].s = D;
        for (; A != -1 && s[A].t[x] == C; A = s[A].s)
            s[A].t[x] = D;
        break;
    }
    return s[s[B].p].t[x];
}

void print() {
    for (unsigned int i = 0; i < s.size(); ++i) {
        cout << i << " " << s[i].s << " " << s[i].l << ": ";
        for (int j = 0; j < 26; ++j)
            if (s[i].t[j] != -1)
                cout << char(j + 'a') << " " << s[i].t[j] << "; ";
        cout << endl;
    }
}

void p(int v, int c) {
    s[v].u = c;
    ++s[v].k;
    if (s[v].p != -1 && s[s[v].p].u < c)
        p(s[v].p, c);
    if (s[v].s != -1 && s[s[v].s].u < c)
        p(s[v].s, c);
}

int main() {
    s.push_back(z());
    int n;
    cin >> n;
    vector<int> t(n);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        int v = 0;
        for (auto x : s) {
            v = add(v, x);
        }
        t[i] = v;
    }
    for (int i = 0; i < n; ++i) {
        p(t[i], i + 1);
    }
    //print();
    vector<int> a(n);
    for (int i = 1; i < s.size(); ++i)
        if (s[i].k - 1 > 0)
            a[s[i].k - 1] = max(a[s[i].k - 1], s[i].l);
    for (int i = n - 2; i >= 0; --i)
        a[i] = max(a[i], a[i + 1]);
    for (int i = 1; i < n; ++i)
        cout << a[i] << '\n';
    return 0;
}
