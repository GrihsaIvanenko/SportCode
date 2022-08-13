#include <bits/stdc++.h>

using namespace std;

const int MAXN = 16;

vector<int> g[MAXN], ng[MAXN], euler;

int h[MAXN], v[MAXN], tin[MAXN], num = 0, timer = 0;

int dfs_swap(int x){
    int weight[g[x].size()], sum = 0, ind_max = 0;
    for(int i = 0; i < g[x].size(); ++i){
        weight[i] = dfs_swap(g[x][i]);
        sum += weight[i];
        if(weight[i] > weight[ind_max])
            ind_max = i;
    }
    if(g[x].size() > 0)
        swap(g[x][0], g[x][ind_max]);
    return sum + 1;
}

void dfs_number(int x){
    v[x] = num++;
    for(int i = 0; i < g[x].size(); ++i)
        dfs_number(g[x][i]);
}

void dfs_print(int x){
    cout << x << ": ";
    for(int i = 0; i < g[x].size(); ++i)
        cout << g[x][i] << " ";
    cout << endl;
    for(int i = 0; i < g[x].size(); ++i)
        dfs_print(g[x][i]);
}

void copy_g(int x){
    ng[v[x]].resize(g[x].size());
    for(int i = 0; i < g[x].size(); ++i)
        ng[v[x]][i] = v[g[x][i]];
    for(int i = 0; i < g[x].size(); ++i)
        copy_g(g[x][i]);
}

void print_ng(int n){
    cout << "v:\n";
    for(int i = 0; i < n; ++i)
        cout << i << " -> " << v[i] << endl;
    cout << endl;

    for(int i = 0; i < n; ++i){
        cout << i << ": ";
        for(int j = 0; j < ng[i].size(); ++j)
            cout << ng[i][j] << " ";
        cout << endl;
    }
}

void euler_dfs(int x){
    euler.push_back(x);
    tin[x] = timer++;
    for(int i = 0; i < ng[x].size(); ++i){
        euler_dfs(ng[x][i]);
        euler.push_back(x);
    }
}

struct segtree{
    segtree *l, *r;
    int lb, rb, mid, min_tin;
    long long sum = 0;
    segtree(int lb_, int rb_){
        lb = lb_;
        rb = rb_;
        mid = (lb + rb)>>1;
        if(rb - lb > 1){
            l = new segtree(lb, mid);
            r = new segtree(mid, rb);
        }
    }
    void build(int pos = 0){
        if(lb + 1 == rb){
            min_tin = tin[pos];
            sum = h[pos];
            return;
        }
        l->build(pos);
        r->build(pos + mid - lb);
        sum = l->sum + r->sum;
        min_tin = min(l->min_tin, r->min_tin);
    }
};

void solve(){
    int n;
    cin >> n;
    //for(int i =0; i < n; ++i)
       //n cin >> h[i];
    for(int i = 0; i < n - 1; ++i){
        int a, b;
        cin >> a >> b;
       // --a;
       // --b;
        if(a > b)
            swap(a, b);
        g[a].push_back(b);
    }
    dfs_swap(0);
    dfs_number(0);
    //dfs_print(0);
    copy_g(0);
    //print_ng(n);
    euler_dfs(0);
    segtree *root = new segtree(0, MAXN);
    root->build();
}

int main(){
    solve();
    return 0;
}
/*10
0 1
1 2
1 3
0 4
4 5
5 6
5 7
7 8
8 9*/
