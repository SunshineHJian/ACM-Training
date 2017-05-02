#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 8000;

struct Tnode{
    int l, r, c;
    int left, right;
} T[4*N+1]; //..?
int root, total, _a, _b, _c, _x;

struct Seg{
    int l, r, key;
    friend bool operator <(Seg a, Seg b){
        return a.key < b.key;
    }
} S[N];

int hash[N];
vector<int> adj[N];
int n ,ans;

void addEdge(int x, int y){
    adj[x].push_back(y);
}


void build(int& now, int a, int b){
    now = total++;
    T[now].l = a, T[now].r = b, T[now].c = -1;
    if (a < b){
        int m = (a + b) / 2;
        build(T[now].left, a, m);
        build(T[now].right, m+1, b);
    }
}


void query(int now){
    if (T[now].c!=-1){
        if (hash[T[now].c]!=_c){
            hash[T[now].c] = _c;
            addEdge(T[now].c, _c);
        }
    }
    else {
        if (T[now].l < T[now].r){
            int m = (T[now].l  + T[now].r) / 2;
            if (_a <= m) query(T[now].left);
            if (m < _b) query(T[now].right);
        }
    }
}



void insert(int now){
    if (_a <= T[now].l && T[now].r <= _b)
        T[now].c = _c;
    else{
        if (T[now].c != -1){
            T[T[now].left].c = T[T[now].right].c = T[now].c;
            T[now].c = -1;
        }
        int m = (T[now].l + T[now].r) / 2;
        if (_a <= m) insert(T[now].left);
        if (m < _b) insert(T[now].right);
    }
}


void init(){
    scanf("%d", &n);
    for (int i=0;i<n;i++)
        scanf("%d%d%d", &S[i].l, &S[i].r, &S[i].key);
    
    sort(S, S+n), total = 0, build(root, 0, 2 * N);
    memset(hash, -1, sizeof(hash));
    memset(adj, 0, sizeof(adj));
    for (int i=0;i<n;i++){
        _a = S[i].l * 2, _b = S[i].r * 2, _c = i;
        query(root); insert(root);
    }
}


void stat(){
    ans = 0;
    for (int x=0;x<n;x++){
        memset(hash, 0, sizeof(hash));
        for (int i=0;i<adj[x].size();i++)
            hash[adj[x][i]] = 1;
        for (int i=0;i<adj[x].size();i++){
            int y = adj[x][i];
            for (int j=0;j<adj[y].size();j++)
                if (hash[adj[y][j]]) ans++;
        }
    }
}

void patch(){
    for (int u=0;u<n;u++){
        cout << u << ":";
        for (int i=0;i<adj[u].size();i++)
            cout << " " << adj[u][i];
        cout << endl;
    }
    
}

int main(){
    //freopen("in.txt", "r", stdin);
    int d;
    cin >> d;
    while (d--){
        init(); stat(); 
        //patch();
        cout << ans << endl;
    }
}