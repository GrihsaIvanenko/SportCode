#include <bits/stdc++.h>

using namespace std;

struct nd {
    vector<int> next;
    int suf, p, len;
    char my_char;
    nd() {
        next.assign(26, -1);
        suf = -1;
        p = -1;
        len = 0;
        my_char = '1';
    }
};

struct IMBA {
    vector<nd> s;
    int last = -1;
    long long kolvo;
    IMBA() {
        s.push_back(nd());
        last = 0;
        kolvo = 0;
    }
    int add(int A, char lox) {
        lox -= 'a';
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
        kolvo += (long long)(s[B].len - s[s[B].suf].len);
        return last = s[s[B].p].next[lox];
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
        for (int i = 0; i < 26; ++i)
            if (s[v].next[i] != -1) {
                cout << char('a' + i) << " " << s[v].next[i] << "; ";
            }
        cout << endl;
        for (int i = 0; i < 26; ++i) {
            if (s[v].next[i] != -1) {
                print(used, s[v].next[i]);
            }
        }
    }
};

int main() {
    IMBA AVT;
    string s;
    cin >> s;
    for (auto x : s) {
        AVT.add(AVT.last, x);
        cout << AVT.kolvo << '\n';
    }
}

