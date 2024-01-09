#include <bits/stdc++.h>
#define uLL unsigned long long
using namespace std;
const int N = 4.5e5+5;
int n, m, a[N], opt, k, rr, st, gs[N];
struct node {
    int mn, mg, ans, lzy;
};
struct tree {
    node tr[N<<2];
    #define ls (k<<1)
    #define rs (ls|1)
    void upup(int k) {
        tr[k].mn=min(tr[ls].mn, tr[rs].mn);
        tr[k].mg=(tr[ls].mn == tr[k].mn ? tr[ls].mg : 0)+(tr[rs].mn == tr[k].mn ? tr[rs].mg : 0);
        tr[k].ans=tr[ls].ans+tr[rs].ans;
    }
    void down(int k) {
        if(tr[k].lzy == 0) return ;
        tr[ls].mn+=tr[k].lzy;
        tr[ls].ans=(tr[ls].mn == 0 ? tr[ls].mg : 0);
        tr[ls].lzy+=tr[k].lzy;
        tr[rs].mn+=tr[k].lzy;
        tr[rs].ans=(tr[rs].mn == 0 ? tr[rs].mg : 0);
        tr[rs].lzy+=tr[k].lzy;
        tr[k].lzy=0;
    }
    void built(int k, int l, int r) {
        if(l == r) {
            tr[k].mn=tr[k].lzy=0;
            tr[k].mg=tr[k].ans=1;
            return ;
        }
        int mid = ((l+r)>>1);
        built(ls, l, mid);
        built(rs, mid+1, r);
        upup(k);
        return ;
    }
    void updt(int k, int l, int r, int lq, int rq, int w) {
        if(lq <= l && r <= rq) {
            tr[k].mn+=w;
            tr[k].lzy+=w;
            tr[k].ans=(tr[k].mn == 0 ? tr[k].mg : 0);
            return ;
        }
        down(k);
        int mid = ((l+r)>>1);
        if(lq <= mid)
            updt(ls, l, mid, lq, rq, w);
        if(mid+1 <= rq)
            updt(rs, mid+1, r, lq, rq, w);
        upup(k);
        return ;
    }
    int ask(int k, int l, int r, int lq, int rq) {
        if(lq <= l && r <= rq)
            return tr[k].ans;
        down(k);
        int mid = ((l+r)>>1), ret = 0;
        if(lq <= mid)
            ret+=ask(ls, l, mid, lq, rq);
        if(mid+1 <= rq)
            ret+=ask(rs, mid+1, r, lq, rq);
        return ret;
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

signed main() {
    read(n), read(m);
    st=150001, rr=450001;
    A.built(1, 1, rr);
    for(int i = 1; i <= n; ++i)
        read(a[i]), a[i]+=st, ++gs[a[i]], A.updt(1, 1, rr, a[i]-gs[a[i]]+1, a[i]-gs[a[i]]+1, 1);
    for(int i = 1; i <= m; ++i) {
        read(opt), read(k);
        if(opt > 0) {
            if(a[opt] <= st+n)
                A.updt(1, 1, rr, a[opt]-gs[a[opt]]+1, a[opt]-gs[a[opt]]+1, -1);
            --gs[a[opt]];
            a[opt]=k+st;
            if(a[opt] <= st+n)
                A.updt(1, 1, rr, a[opt]-gs[a[opt]], a[opt]-gs[a[opt]], 1);
            ++gs[a[opt]];
        }
        else {
            if(k == 1) {
                if(gs[st+n])
                    A.updt(1, 1, rr, st+n-gs[st+n]+1, st+n, -1);
                --st;
            }
            else {
                ++st;
                if(gs[st+n])
                    A.updt(1, 1, rr, st+n-gs[st+n]+1, st+n, 1);
            }
        }
        write(A.ask(1, 1, rr, st+1, st+n), '\n');
    }
	return 0;
}