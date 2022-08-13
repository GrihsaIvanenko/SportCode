#include <bits/stdc++.h>

using namespace std;


const int MAXN = 524288, T = 19;

int rev[MAXN];

complex<long double> roots[MAXN];

const long double P = atan2(0.0, -1.0), TWO = 2.0;

void precalc() {
    for (int j = 0; j < MAXN; ++j) {
        long double ang = (TWO * P * (long double)j) / (long double)MAXN;
        roots[j] = complex<long double>(cos(ang), sin(ang));
    }
    rev[0] = 0;
    for (int i = 1; i < MAXN; ++i)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (T - 1));
}

void fft(vector<complex<long double>> &a) {
    for (int i = 0; i < MAXN; ++i)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    for (int level = 0; level < T; ++level) {
        for (int i = 0; i < MAXN; i += (1 << (level + 1))) {
            for (int k = 0; k < (1 << level); ++k) {
                complex<long double> A = a[i + k], B = a[i + k + (1 << level)] * roots[k * (1 << (T - level - 1))];
                a[i + k] = A + B;
                a[i + k + (1 << level)] = A - B;
            }
        }
    }
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    precalc();
    string a, b;
    cin >> a >> b;
    bool minn = 0;
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    if (a.back() == '-') {
        a.pop_back();
        minn ^= 1;
    }
    if (b.back() == '-') {
        b.pop_back();
        minn ^= 1;
    }
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    vector<complex<long double>> N1(MAXN), N2(MAXN);
    for (size_t i = 0; i < a.size(); ++i)
        N1[i] = complex<long double>(a[i] - '0', 0);
    for (size_t i = a.size(); i < MAXN; ++i)
        N1[i] = complex<long double>(0, 0);
    for (size_t i = 0; i < b.size(); ++i)
        N2[i] = complex<long double>(b[i] - '0', 0);
    for (size_t i = b.size(); i < MAXN; ++i)
        N2[i] = complex<long double>(0, 0);
    fft(N1);
    fft(N2);
    for (int i = 0; i < MAXN; ++i)
        N1[i] *= N2[i];
    fft(N1);
    for (int i = 0; i < MAXN; ++i)
        N1[i] /= MAXN;
    reverse(N1.begin() + 1, N1.end());
    vector<long long> ans(MAXN);
    for (int i = 0; i < MAXN; ++i) {
        ans[i] = N1[i].real();
        if ((long double)ceil(N1[i].real()) - N1[i].real() < N1[i].real() - ans[i])
            ans[i] = ceil(N1[i].real());
    }
    for (int i = MAXN - 1; i > 0; --i) {
        ans[i - 1] += ans[i] / 10;
        ans[i] %= 10;
    }
    while (ans.back() == 0)
        ans.pop_back();
    if (minn && ans.size() != 0)
        cout << '-';
    if (ans.size() == 0)
        ans.push_back(0);
    for (auto x : ans)
        cout << x;
    cout << '\n';
    return 0;
}
