#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5, B = 1000;
int n, m, q, u, v, typ[N], uu[N], vv[N], tot, pnt[N], ans[N], ds[N], in[N], vis[N], bl[N], zhan[B+5];
bitset <B+3> hh[N];
vector <int> to[N], que[N];
queue <int> qa;

template <typename T> inline void debug(T x) { cerr<<x; }
template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
template <typename T> void read(T& x) {
	x = 0; int f = 0; char c = getchar();
	while(c < '0' || c > '9') f |= (c == '-'), c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x);
}
int lne; char put[105];
template <typename T> void write(T x, char ch) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
	putchar(ch);
}
void sol() {
    for(int i = 1; i <= n; ++i) {
        in[i]=ds[i];
        hh[i].reset();
        if(ds[i] == 0)
            qa.push(i);
    }
    for(int i = 1; i <= tot; ++i)
        hh[uu[zhan[i]]][i]=1, pnt[uu[zhan[i]]]=vv[zhan[i]], bl[uu[zhan[i]]]=zhan[i];
    while(!qa.empty()) {
        int now = qa.front(); qa.pop();
        for(int y : to[now]) {
            --in[y];
            if(bl[now] > bl[y]) bl[y]=bl[now], pnt[y]=pnt[now];
            hh[y]|=hh[now];
            if(!in[y])
                qa.push(y);
        }
        for(int o = 0; o < (int) que[now].size(); ++o) {
            int pp = que[now][o];
            int& anss = ans[pp];
            for(int j = 1; j <= tot && zhan[j] <= pp; ++j)
                if(hh[now][j])
                    anss=vv[zhan[j]];
        }
    }
    for(int i = 1; i <= n; ++i) 
        que[i].clear();
}
void ddfs(int x, int d) {
    pnt[x]=(typ[d] == 1 ? vv[d] : min(pnt[x], vv[d]));
    vis[x]=1;
    for(int y : to[x])
        if(!vis[y])
            ddfs(y, d);
}

signed main() {
    File("dag");
    // debug(B, '\n');
	read(n), read(m), read(q);
    for(int i = 1; i <= m; ++i)
        read(u), read(v), to[u].push_back(v), ++ds[v];
    int pd1 = 1, pd2 = 1;
    for(int i = 1; i <= q; ++i) {
        read(typ[i]), read(uu[i]);
        if(typ[i] != 3) read(vv[i]);
        pd1&=(typ[i] != 1);
        pd2&=(typ[i] != 2);
    }
    if(pd1) {//10
        for(int i = 1; i <= q; ++i)
            write(0, '\n');
        return 0;
    }
    if(n <= 5000 && m <= 5000) {//20
        for(int i = 1; i <= q; ++i) {
            if(typ[i] != 3) {
                for(int j = 1; j <= n; ++j)
                    vis[j]=0;
                ddfs(uu[i], i);
            }
            else
                write(pnt[uu[i]], '\n');
        }
        return 0;
    }
    if(pd2) {//30?
        for(int i = 1; i <= q; ++i) {
            if(typ[i] != 3) 
                zhan[++tot]=i;
            else 
                que[uu[i]].push_back(i), ans[i]=pnt[uu[i]];
            if(tot == B)
                sol(), tot=0;
        }
        if(tot)
            sol(), tot=0;
        for(int i = 1; i <= q; ++i)
            if(typ[i] == 3)
                write(ans[i], '\n');
        return 0;
    }
    for(int i = 1; i <= q; ++i) {
        if(typ[i] != 3) {
            for(int j = 1; j <= n; ++j)
                vis[j]=0;
            ddfs(uu[i], i);
        }
        else
            write(pnt[uu[i]], '\n');
    }
	return 0;
}