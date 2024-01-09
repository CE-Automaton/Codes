#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5+5, B = 20000;
int n, q, a[N], opt, kk, to[N], gs;
struct qwq {
    int id, w;
}b[N];
struct tree {
    int lazy[(N<<4)], mx[(N<<4)], mn[(N<<4)];
    #define ls (k<<1)
    #define rs ((k<<1)|1)
    void built(int k, int l, int r) {
        if(l == r) {
            lazy[k]=0;
            mx[k]=mn[k]=b[l].w;
            return ;
        }
        int mid = ((l+r)>>1);
        built(ls, l, mid);
        built(rs, mid+1, r);
        mx[k]=max(mx[ls], mx[rs]);
        mn[k]=min(mn[ls], mn[rs]);
    }
    void down(int k) {
        if(lazy[k] == 0) return ;
        lazy[ls]+=lazy[k];
        mn[ls]+=lazy[k];
        mx[ls]+=lazy[k];
        lazy[rs]+=lazy[k];
        mn[rs]+=lazy[k];
        mx[rs]+=lazy[k];
        lazy[k]=0;
    }
    void mod(int k, int mo) {
        down(k);
        int x = mx[k]/mo, y = mn[k]/mo;
        if(x == y) {
            ++gs;
            lazy[k]-=mo*x;
            mn[k]-=mo*x;
            mx[k]-=mo*x;
            return ;
        }
        else 
            mod(ls, mo), mod(rs, mo);
        mx[k]=max(mx[ls], mx[rs]);
        mn[k]=min(mn[ls], mn[rs]);
    }
    int find(int k, int l, int r, int too) {
        if(l == r) 
            return mn[k];
        down(k);
        int mid = ((l+r)>>1);
        if(too <= mid)
            return find(ls, l, mid, too);
        return find(rs, mid+1, r, too);
    }
}A;
template <typename T> void read(T& x) {
	x = 0; int f = 0; char c = getchar();
	while(c < '0' || c > '9') f |= (c == '-'), c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x);
}
int lne; char put[105];
template <typename T> void write(T x) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
}
int comp(qwq A, qwq B) {
    return A.w < B.w;
}
void haha(int pd) {
    if(!pd)
        for(int i = 1; i <= n; ++i)
            a[i]=A.find(1, 1, n, to[i]);
    for(int i = 1; i <= n; ++i)
        b[i]=qwq{i, a[i]};
    sort(b+1, b+1+n, comp);
    for(int i = 1; i <= n; ++i)
        to[b[i].id]=i;
    A.built(1, 1, n);
}

signed main() {
    // freopen("mod.in", "r", stdin);
    // freopen("mod.in", "w", stdout);
    read(n), read(q);
    for(int i = 1; i <= n; ++i) 
        read(a[i]);
    haha(1);
    for(int i = 1; i <= q; ++i) {
        read(opt), read(kk);
        if(opt == 1) 
            A.mn[1]+=kk, A.mx[1]+=kk, A.lazy[1]+=kk;
        else {
            ++gs;
            A.mod(1, kk);
            if(gs >= B) 
                haha(0), gs=0;
        }
    }
    for(int i = 1; i <= n; ++i)
        a[i]=A.find(1, 1, n, to[i]), write(a[i]), putchar(' ');
    return 0;
}