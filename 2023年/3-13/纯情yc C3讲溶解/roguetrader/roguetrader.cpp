#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, v, l, a[200005], b[200005], c[200005], dp[10005], pp[10005], qwq[10005], ans;
struct node {
    int az[15];
}ret, ll[200005], rr[200005];
node upup (node A, node B) {
    node qwq;
    for(int i = 0; i <= v; ++i)
        qwq.az[i]=0;
    for(int i = v; i >= 0; --i)
        for(int j = v-i; j >= 0; --j)
            qwq.az[i+j]=max(qwq.az[i+j], A.az[i]+B.az[j]);
    return qwq;
}
struct tree {
    node tr[400005];
    #define ls (k<<1)
    #define rs ((k<<1)|1)
    void built(int k, int l, int r) {
        if(l == r) {
            for(int i = v-b[l]; i >= 0; --i)
                tr[k].az[i+b[l]]=max(tr[k].az[i+b[l]], tr[k].az[i]+c[l]);
            return ;
        }
        int mid = ((l+r)>>1);
        built(ls, l, mid);
        built(rs, mid+1, r);
        tr[k]=upup(tr[ls], tr[rs]);
    }
    node find(int k, int l, int r, int lq, int rq) {
        if(lq <= l && r <= rq) 
            return tr[k];
        int mid = ((l+r)>>1);
        if(lq <= mid && mid+1 <= rq)
            return upup(find(ls, l, mid, lq, rq), find(rs, mid+1, r, lq, rq));
        if(lq <= mid) return find(ls, l, mid, lq, rq);
        if(mid+1 <= rq) return find(rs, mid+1, r, lq, rq);
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

signed main() {
    freopen("roguetrader.in", "r", stdin);
    freopen("roguetrader.out", "w", stdout);
    read(n), read(v), read(l);
    for(int i = 1; i <= n; ++i)
        read(a[i]), read(b[i]), read(c[i]);
    if(n > 100 && v <= 10) {
        A.built(1, 1, n);
        for(int i = 1; i <= n; ++i) {
            for(int j = v; j >= 0; --j)
                ll[i].az[j]=ll[i-1].az[j];
            for(int j = v-a[i]; j >= 0; --j)
                ll[i].az[j+a[i]]=max(ll[i].az[j+a[i]], ll[i-1].az[j]+c[i]);
        }
        for(int i = n; i >= 1; --i) {
            for(int j = v; j >= 0; --j)
                rr[i].az[j]=rr[i+1].az[j];
            for(int j = v-a[i]; j >= 0; --j)
                rr[i].az[j+a[i]]=max(rr[i].az[j+a[i]], rr[i+1].az[j]+c[i]);
        }
        // for(int i = 1; i <= n; ++i) {
        //     int lll = i, rrr = n, sum = -1;
        //     node ret;
        //     while(lll <= rrr) {
        //         int mid = ((lll+rrr)>>1), o = 0, ppp = 0;
        //         ret=upup(ll[i-1], upup(A.find(1, 1, n, i, mid), rr[mid+1]));
        //         for(int i = 1; i <= v; ++i)
        //             o=max(o, ret.az[i]), ppp+=o;
        //         if(ppp <= l*v)
        //             sum=mid, rrr=mid-1;
        //         else
        //             lll=mid+1;
        //     }
        //     if(sum != -1)
        //         ans+=n-sum+1;
        // }
        // write(ans);
        int r = 1;
        ans=0;
        for(int i = 1; i <= n; ++i) {
            while(r < i) ++r;
            while(r <= n) {
                node ret = upup(ll[i-1], upup(A.find(1, 1, n, i, r), rr[r+1]));
                int o = 0, ppp = 0;
                for(int i = 1; i <= v; ++i)
                    o=max(o, ret.az[i]), ppp+=o;
                if(ppp <= l*v)
                    break;
                else
                    ++r;
            }
            ans+=(r <= n ? n-r+1 : 0);
        }
        write(ans);
        return 0;
    }
    for(int i = 1; i <= n; ++i) {
        for(int o = 1; o <= v; ++o)
            qwq[o]=dp[o];
        for(int j = n; j >= i; --j) {
            for(int o = 1; o <= v; ++o)
                pp[o]=dp[o];
            for(int k = i; k <= j; ++k)
                for(int ll = v-b[k]; ll >= 0; --ll)
                    pp[ll+b[k]]=max(pp[ll+b[k]], pp[ll]+c[k]);
            int o = 0, sum = 0;
            for(int l = 1; l <= v; ++l)
                o=max(o, pp[l]), sum+=o;
            if(sum <= l*v)
                ++ans;
            for(int o = v-a[j]; o >= 0; --o)
                dp[o+a[j]]=max(dp[o+a[j]], dp[o]+c[j]);
        }
        for(int o = 1; o <= v; ++o)
            dp[o]=qwq[o];
        for(int o = v-a[i]; o >= 0; --o)
            dp[o+a[i]]=max(dp[o+a[i]], dp[o]+c[i]);
    }
    write(ans);
	return 0;
}