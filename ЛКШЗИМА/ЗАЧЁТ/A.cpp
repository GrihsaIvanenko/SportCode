#include <bits/stdc++.h>

using namespace std;

int main() {
    long long n, c;
    cin >> n >> c;
    vector<long long> is(n), can(n);
    for (int i = 0; i < n; ++i)
        cin >> is[i];
    for (int i = 0; i < n; ++i)
        cin >> can[i];
    long long ans = 0;
    for (int pos = n - 1; pos >= 0; --pos) {
        long long easy = min(can[pos], is[pos]);
        ans += easy;
        can[pos] -= easy;
        for (int from = pos - 1; from >= 0; --from) {
            long long inc = min(c, is[from], can[pos]);

        }
    }
}
