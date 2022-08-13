#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    for (int j = 0; j < t; ++j) {
        int n;
        cin >> n;
        long long xorr = 0;
        for (int i = 0; i < n; ++i) {
            int k;
            cin >> k;
            if (k % 4 == 0)
                xorr ^= (k - 1);
            else if (k % 4 == 3)
                xorr ^= (k + 1);
            else
                xorr ^= k;
        }
        if (xorr) {
            cout << "FIRST\n";
        } else {
            cout << "SECOND\n";
        }
    }
    return 0;
}
