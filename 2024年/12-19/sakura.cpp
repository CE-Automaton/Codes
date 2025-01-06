#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
typedef unsigned long long ull;
const int N = 2e5+5;
int n, m, q, op[N], ll[N], rr[N], vv[N], Bn, Bm, bln[N], blm[N], u, v;
ull sum[N], summ[N], ans[N];
struct qwq { int l, d; };
vector <qwq> pro[N], proo[N];
struct fk {//O(sqrt(n)) - O(1) 区间加减
	ull sw[N], lzy[N], ss[N];
	void addd(int x, int w) {
		if(!x) return ;
		int bl = bln[x], l = (bl-1)*Bn, r = min(bl*Bn, n);
		for(int i = l+1; i <= r; ++i)
			sw[i]+=1uLL*w*min(i-l, x-l);
		for(int i = 1; i < bl; ++i)
			lzy[i]+=w, ss[i]+=1uLL*w*Bn*i;
		for(int i = bl; i <= bln[n]; ++i)
			ss[i]+=1uLL*w*x;
	}
	ull askk(int x) {
		if(!x) return 0;
		int bl = bln[x], l = (bl-1)*Bn;
		return ss[bl-1]+sw[x]+lzy[bl]*(x-l);
	}
	void add(int l, int r, int w) { addd(l-1, -w), addd(r, w); }
	ull ask(int l, int r) { return askk(r)-askk(l-1); }
}A, B, C, D;

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
int comp(qwq A, qwq B) {
	return A.l < B.l;
}

signed main() {
	File("sakura");
	read(n), read(m), read(q);
	Bn=(int) sqrt(n);
	Bm=(int) sqrt(m);
	for(int i = 1; i <= n; ++i)
		bln[i]=(i+Bn-1)/Bn;
	for(int i = 1; i <= m; ++i) {
		blm[i]=(i+Bm-1)/Bm;
		read(op[i]), read(ll[i]), read(rr[i]);
		sum[i]=sum[i-1], summ[i]=summ[i-1];
		if(op[i] == 1) 
			read(vv[i]), A.add(ll[i], rr[i], vv[i]), summ[i]+=B.ask(ll[i], rr[i])*vv[i];
		else
			sum[i]+=A.ask(ll[i], rr[i]), B.add(ll[i], rr[i], 1);
	}
	for(int i = 1; i <= q; ++i) {
		read(u), read(v), ans[i]=sum[v]+summ[u-1];
		if(u-1) {
			pro[u-1].push_back(qwq {v, i});
			if(blm[v]-1)
				proo[blm[v]-1].push_back(qwq {u-1, i});
		}
	}
	for(int i = 1; i < blm[m]; ++i) {
		int l = (i-1)*Bm, r = i*Bm;
		for(int j = l+1; j <= r; ++j)
			if(op[j] == 2)
				C.add(ll[j], rr[j], 1);
		if(proo[i].empty()) continue;
		sort(proo[i].begin(), proo[i].end(), comp);
		int now = 1;
		ull sss = 0;
		for(int j = 0; j < proo[i].size(); ++j) {
			while(now <= proo[i][j].l)
				sss+=(op[now] == 1 ? C.ask(ll[now], rr[now])*vv[now] : 0), ++now;
			ans[proo[i][j].d]-=sss;
		}
	}
	for(int i = 1; i < m; ++i) {
		if(op[i] == 1)
			D.add(ll[i], rr[i], vv[i]);
		for(int j = 0; j < pro[i].size(); ++j) {
			ull sss = 0;
			int l = blm[pro[i][j].l]*Bm-Bm;
			for(int kk = l+1; kk <= pro[i][j].l; ++kk) 
				if(op[kk] == 2)
					sss+=D.ask(ll[kk], rr[kk]);
			ans[pro[i][j].d]-=sss;
		}
	}
	for(int i = 1; i <= q; ++i)
		write(ans[i], '\n');
	return 0;
}