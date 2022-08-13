#include <bits/stdc++.h>

using namespace std;

pair<int, int> solve(vector<int> A, vector<int> B) {
    reverse(B.begin(), B.end());
    for (int i = 0; i < A.size() - 1; ++i)
        B.push_back(B[i]);

}

int main () {
    int m;
    cin >> m;
    string A, B;
    cin >> A >> B;
    vector<int> M1(m), M2(m);
    for (int i = 0; i < m; ++i) {
        if (A[i] == 'A')
            M1[i] = 1;
        else if (A[i] == 'C')
            M1[i] = 2;
        else if (A[i] == 'G')
            M1[i] = 3;
        else
            M1[i] = 4;
        if (B[i] == 'A')
            M2[i] = 1;
        else if (B[i] == 'C')
            M2[i] = 2;
        else if (B[i] == 'G')
            M2[i] = 3;
        else
            M2[i] = 4;
    }
    pair<int, int> p = solve(M1, M2);
    cout << p.first << " " << p.second << endl;
    return 0;
}
