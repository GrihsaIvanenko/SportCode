#include "message.h"
#include "crates.h"
#include <iostream>
#include <vector>

using namespace std;

signed main( void ) {
    int id = MyNodeId();
    if (id == 0) {
        long long N = NumberOfNodes(), n = GetNumStacks();
        vector<long long> l, r, sm;
        for (int i = 1; i < N; ++i) {
            Receive(i);
            l.push_back(GetLL(i));
            r.push_back(GetLL(i));
            sm.push_back(GetLL(i));
        }
        long long summ = 0;
        for (auto x : sm)
            summ += x;
        long long should_be = summ / n, plus_odin = summ % n;
        vector<long long> was_before;
        long long cnt = 0;
        for (int i = 0; i < N - 1; ++i) {
            if (l[i] == n)
                continue;
            was_before.push_back(cnt);
            cnt += sm[i];
            cnt -= (r[i] - l[i]) * should_be;
            long long minr = min(plus_odin, r[i]);
            cnt -= max(0ll, minr - l[i]);
        }
        for (int i = 1; i < N; ++i) {
            PutLL(i, was_before[i - 1]);
            PutLL(i, should_be);
            PutLL(i, plus_odin);
            Send(i);
        }
        long long ans = 0;
        for (int i = 1; i < N; ++i) {
            Receive(i);
            ans += GetLL(i);
        }
        cout << ans << endl;
    } else {
        long long n = GetNumStacks();
        int itt = NumberOfNodes() - 1;
        long long ans = 0;
        if (id > n) {
            PutLL(0, n);
            PutLL(0, n);
            PutLL(0, 0);
            Send(0);
        } else {
            long long step = (n + itt - 1) / itt;
            long long lb = (id - 1) * step, rb = min(n, id * step);
            for (int i = lb; i < rb; ++i) {
                ans += GetStackHeight(i + 1);
            }
            PutLL(0, lb);
            PutLL(0, rb);
            PutLL(0, ans);
            Send(0);
        }
        Receive(0);
        long long was_before = GetLL(0);
        long long should_be = GetLL(0);
        long long plus_odin = GetLL(0);
        if (id > n) {
            PutLL(0, 0);
            Send(0);
        } else {
            ans = 0;
            long long step = (n + itt - 1) / itt;
            long long lb = (id - 1) * step, rb = min(n, id * step);
            for (int i = lb; i < rb; ++i) {
                long long vi = GetStackHeight(i + 1);
                if (i < plus_odin) {
                    was_before += vi - 1 - should_be;
                    ans += abs(was_before);
                } else {
                    was_before += vi - should_be;
                    ans += abs(was_before);
                }
            }
            PutLL(0, ans);
            Send(0);
        }
    }
    return 0;
}
