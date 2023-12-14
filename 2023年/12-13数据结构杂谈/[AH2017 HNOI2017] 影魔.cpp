#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 2e5+5;
int n, m, p1, p2, k[N], ll[N], rr[N], tot, zhan[N], a, b;
long long ans[N];
struct qwq {
	int w, t;
};
struct add {
	int l, r, w;
};
vector <qwq> pro[N], pro2[N];
vector <add> ps[N], az[N];
struct tree {
	long long tr[N<<2], lzy[N<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	void upup(int k) {
		tr[k]=tr[ls]+tr[rs];
	}
	void down(int k, int l, int mid, int r) {
		if(lzy[k] == 0) return ;
		tr[ls]+=1LL*lzy[k]*(mid-l+1);
		tr[rs]+=1LL*lzy[k]*(r-mid);
		lzy[ls]+=lzy[k];
		lzy[rs]+=lzy[k];
		lzy[k]=0;
	}
	void built(int k, int l, int r) {
		tr[k]=0, lzy[k]=0;
		if(l == r) 
			return ;
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
	}
	void updt(int k, int l, int r, int lq, int rq, int w) {
		if(lq <= l && r <= rq) {
			tr[k]+=1LL*(r-l+1)*w;
			lzy[k]+=w;
			return ;
		}
		int mid = ((l+r)>>1);
		down(k, l, mid, r);
		if(lq <= mid)
			updt(ls, l, mid, lq, rq, w);
		if(mid+1 <= rq)
			updt(rs, mid+1, r, lq, rq, w);
		upup(k);
	}
	long long ask(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq) 
			return tr[k];
		int mid = ((l+r)>>1);
		down(k, l, mid, r);
		long long ret = 0;
		if(lq <= mid)
			ret+=ask(ls, l, mid, lq, rq);
		if(mid+1 <= rq)
			ret+=ask(rs, mid+1, r, lq, rq);
		return ret;
	}
}AA;

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
	read(n), read(m), read(p1), read(p2);
	for(int i = 1; i <= n; ++i)
		read(k[i]);
	for(int i = 1; i <= n; ++i) {
		while(tot && k[zhan[tot]] <= k[i])
			--tot;
		ll[i]=zhan[tot];
		zhan[++tot]=i;
	}
	tot=0;
	for(int i = n; i >= 1; --i) {
		while(tot && k[zhan[tot]] <= k[i])
			--tot;
		rr[i]=zhan[tot];
		zhan[++tot]=i;
	}
	for(int i = 1; i <= n; ++i) {
		if(ll[i] && rr[i])
			ps[rr[i]].push_back(add {ll[i], ll[i], p1});
		if(rr[i] && ll[i]+1 <= i-1)
			ps[rr[i]].push_back(add {ll[i]+1, i-1, p2});
		if(!rr[i])
			rr[i]=n+1;
		if(ll[i] && i+1 <= rr[i]-1)
			az[ll[i]].push_back(add {i+1, rr[i]-1, p2});
	}
	for(int i = 1; i <= m; ++i)
		read(a), read(b), ans[i]=1LL*(b-a)*p1, 
		pro[b].push_back(qwq {a, i}), pro2[a].push_back(qwq {b, i});
	AA.built(1, 1, n);
	for(int i = 1; i <= n; ++i) {
		for(add y : ps[i])
			AA.updt(1, 1, n, y.l, y.r, y.w);
		for(qwq y : pro[i])
			ans[y.t]+=AA.ask(1, 1, n, y.w, i);
	}
	AA.built(1, 1, n);
	for(int i = n; i >= 1; --i) {
		for(add y : az[i])
			AA.updt(1, 1, n, y.l, y.r, y.w);
		for(qwq y : pro2[i])
			ans[y.t]+=AA.ask(1, 1, n, i, y.w);
	}
	for(int i = 1; i <= m; ++i)
		write(ans[i], '\n');
	return 0;
}