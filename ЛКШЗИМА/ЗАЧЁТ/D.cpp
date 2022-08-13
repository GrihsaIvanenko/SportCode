#include <bits/stdc++.h>

using namespace std;

long long n, m;

long long pw(long long a, long long b = n) {
    if (b == 0)
        return 1;
    if (b % 2)
        return (a * pw((a * a) % m, b / 2)) % m;
    return pw((a * a) % m, b / 2);
}

const int MAXN = 524288 * 4, T = 21;

int rev[MAXN];

pair<long double, long double> roots[MAXN];

const long double P = 3.14159265358979323846264338327950288419716939937510, TWO = 2.0;

void precalc() {
    for (int j = 0; j < MAXN; ++j) {
        long double ang = (TWO * P * (long double)j) / (long double)MAXN;
        roots[j].first = cos(ang);
        roots[j].second = sin(ang);
    }
    rev[0] = 0;
    for (int i = 1; i < MAXN; ++i)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (T - 1));
}

void fft(vector<pair<long double, long double>> &a) {
    for (int i = 0; i < MAXN; ++i)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    for (int level = 0; level < T; ++level) {
        for (int i = 0; i < MAXN; i += (1 << (level + 1))) {
            for (int k = 0; k < (1 << level); ++k) {
                pair<long double, long double> A = a[i + k];
                pair<long double, long double> B;
                B.first = a[i + k + (1 << level)].first * roots[k * (1 << (T - level - 1))].first;
                B.first -= a[i + k + (1 << level)].second * roots[k * (1 << (T - level - 1))].second;
                B.second = a[i + k + (1 << level)].first * roots[k * (1 << (T - level - 1))].second;
                B.second += a[i + k + (1 << level)].second * roots[k * (1 << (T - level - 1))].first;
                a[i + k].first = A.first + B.first;
                a[i + k].second = A.second + B.second;
                a[i + k + (1 << level)].first = A.first - B.first;
                a[i + k + (1 << level)].second = A.second - B.second;
            }
        }
    }
}

vector<long long> fft_square(vector<long long> a) {
    vector<pair<long double, long double>> N1(MAXN), N2(MAXN);
    for (size_t i = 0; i < a.size(); ++i)
        N1[i] = {a[i], 0};
    for (size_t i = a.size(); i < MAXN; ++i)
        N1[i] = {0, 0};
    for (size_t i = 0; i < a.size(); ++i)
        N2[i] = {a[i], 0};
    for (size_t i = a.size(); i < MAXN; ++i)
        N2[i] = {0, 0};
    fft(N1);
    fft(N2);
    for (int i = 0; i < MAXN; ++i) {
        pair<long double, long double> p;
        p.first = N1[i].first * N2[i].first - N1[i].second * N2[i].second;
        p.second = N1[i].first * N2[i].second + N1[i].second * N2[i].first;
        N1[i] = p;
    }
    fft(N1);
    for (int i = 0; i < MAXN; ++i) {
        N1[i].first /= (long double)MAXN;
        N1[i].second /= (long double)MAXN;
    }
    reverse(N1.begin() + 1, N1.end());
    vector<long long> ans(MAXN);
    for (int i = 0; i < MAXN; ++i) {
        ans[i] = round(N1[i].first);
    }
    return ans;
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    precalc();
    cin >> n >> m;
    vector<long long> tmps(m);
    for (int i = 1; i < m; ++i)
        ++tmps[pw(i)];
    vector<long long> res = fft_square(tmps);
    long long ans = 0;
    for (int i = 0; i < res.size(); ++i) {
        ans += tmps[i % m] * res[i];
    }
    for (int i = 0; i < tmps.size(); ++i)
        ans += tmps[i] * tmps[(i + i) % m];
    cout << ans / 2ll << endl;
    return 0;
}
