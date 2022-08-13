#include <bits/stdc++.h>

using namespace std;

int main () {
    long long n;
    cin >> n;
    if (n == 1ll) {
        cout << "WIN\n";
        return 0;
    }
    if (n == 2ll) {
        cout << "LOSE\n";
        return 0;
    }
    for (long long loser = 2; loser <= n + 1000000000ll;) {
        long long new_loser = loser + (long long)sqrt(loser);
        for (long long cur = loser + (long long)sqrt(loser); cur - (long long)sqrt(cur) <= loser; ++cur) {
            new_loser = cur;
        }
        loser = new_loser + 1;
        if (n == loser) {
            cout << "LOSE\n";
            return 0;
        }
    }
    cout << "WIN\n";
    return 0;
}
