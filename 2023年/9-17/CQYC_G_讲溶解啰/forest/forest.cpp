#include <bits/stdc++.h>
using namespace std;
const int N = 5e5+5;
int t, n, m, a[N], to[N][2], u, v;
struct tree {
    int mn[N<<2], gs[N<<2], lzy[N<<2];
    #define ls (k<<1)
    #define rs ((k<<1)|1)
    void upup(int k) {
        mn[k]=min(mn[ls], mn[rs]);
        gs[k]=(mn[ls] == mn[k] ? gs[ls] : 0)+(mn[rs] == mn[k] ? gs[rs] : 0);
    }
    void down(int k) {
        if(lzy[k] != 0) {
            lzy[ls]+=lzy[k];
            mn[ls]+=lzy[k];
            lzy[rs]+=lzy[k];
            mn[rs]+=lzy[k];
            lzy[k]=0;
        }
    }
    void built(int k, int l, int r) {
        lzy[k]=0;
        if(l == r) {
            mn[k]=0;
            gs[k]=1;
            return ;
        }
        int mid = ((l+r)>>1);
        built(ls, l, mid);
        built(rs, mid+1, r);
        upup(k);
    }
    void updt(int k, int l, int r, int lq, int rq, int w) {
        if(lq <= l && r <= rq) {
            lzy[k]+=w;
            mn[k]+=w;
            return ;
        }
        down(k);
        int mid = ((l+r)>>1);
        if(lq <= mid)
            updt(ls, l, mid, lq, rq, w);
        if(mid+1 <= rq)
            updt(rs, mid+1, r, lq, rq, w);
        upup(k);
    }
}A;

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
void cf(int o, int w, int op, int wp, int ww) {
    if(o == 0) {
        if(op == 0) 
            A.updt(1, 0, n, wp/2, n, ww)/*, cout<<wp/2<<" "<<n<<" "<<ww<<"!\n"*/;
        else
            A.updt(1, 0, n, w/2, wp/2, ww)/*, cout<<w/2<<" "<<wp/2<<" "<<ww<<"!\n"*/;
    }
    else {
        if(op == 1) 
            A.updt(1, 0, n, 0, w/2, ww)/*, cout<<0<<" "<<w/2<<" "<<ww<<"!\n"*/;
        else
            if((w+1)/2 <= wp/2-1)
                A.updt(1, 0, n, (w+1)/2, wp/2-1, ww)/*, cout<<(w+1)/2<<" "<<wp/2-1<<" "<<ww<<"!\n"*/;
    }
}

signed main() {
    freopen("forest.in", "r", stdin);
    freopen("forest.out", "w", stdout);
    read(t);
    while(t--) {
        read(n), read(m);
        for(int i = 1; i <= n; ++i) 
            to[i][0]=to[i][1]=0;
        A.built(1, 0, n);
        for(int i = 1; i <= 2*n; ++i) {
            read(a[i]);
            if(!to[a[i]][0])
                to[a[i]][0]=i;
            else
                to[a[i]][1]=i;
        }
        for(int i = 1; i <= n; ++i)
            cf(to[i][0]%2, to[i][0], to[i][1]%2, to[i][1], 1);
        for(int i = 1; i <= m; ++i) {
            read(u), read(v);
            if(a[u] == a[v]) {
                if(A.mn[1] == 0)
                    write(A.gs[1], '\n');
                else
                    write(0, '\n');
                continue;
            }
            int t = a[u];
            cf(to[t][0]%2, to[t][0], to[t][1]%2, to[t][1], -1);
            if(u == to[t][0]) 
                to[t][0]=v;
            else 
                to[t][1]=v;
            if(to[t][0] > to[t][1]) swap(to[t][0], to[t][1]);
            cf(to[t][0]%2, to[t][0], to[t][1]%2, to[t][1], 1);

            t = a[v];
            cf(to[t][0]%2, to[t][0], to[t][1]%2, to[t][1], -1);
            if(v == to[t][0]) 
                to[t][0]=u;
            else 
                to[t][1]=u;
            if(to[t][0] > to[t][1]) swap(to[t][0], to[t][1]);
            cf(to[t][0]%2, to[t][0], to[t][1]%2, to[t][1], 1);

            swap(a[u], a[v]);
            if(A.mn[1] == 0)
                write(A.gs[1], '\n');
            else
                write(0, '\n');
        }
    }
	return 0;
}