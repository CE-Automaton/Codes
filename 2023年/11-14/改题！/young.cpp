#include <bits/stdc++.h>
#define mod 1000000007
#define inv2 (mod-mod/2)
using namespace std;
const int N = 5e5+5;
int n, zhan[N*10]/*节点回收,或许有用*/, tot, gs, rt[N], b[N], u, v, cnt, c[N], e[N], to[N];
long long sum[N];
vector <int> az[N];
struct qwq {
	int d, w;
}a[N];
struct node {
	int ls, rs, gs;
	long long sm, ans;
}tr[N*10];
int upd(int x) {
	return (x < 0 ? x+mod : (x >= mod ? x-mod : x));
}
struct tree {//线段树合并板子 
	#define ls(x) tr[x].ls
	#define rs(x) tr[x].rs
	#define gs(x) tr[x].gs
	#define sm(x) tr[x].sm
	#define ans(x) tr[x].ans
	void upup(int k) {
		gs(k)=gs(ls(k))+gs(rs(k));
		sm(k)=upd(sm(ls(k))+sm(rs(k)));
		ans(k)=upd(upd(upd(ans(ls(k))+ans(rs(k)))+1LL*gs(ls(k))*sm(rs(k))%mod)-1LL*gs(rs(k))*sm(ls(k))%mod);
	}
	void dlt(int k) { zhan[++tot]=k; }
	void cnw(int& ret) {
		if(tot) ret=zhan[tot], --tot;
		else ret=(++gs); 
		tr[ret]=node {0, 0, 0, 0, 0};
	}
	int merge(int x, int y, int l, int r) {
		if(!x || !y) return (x|y);
		if(l == r) {
			gs(x)+=gs(y);
			sm(x)=upd(sm(x)+sm(y));
			ans(x)=upd(ans(x)+ans(y));
			return x;
		}
		int mid = ((l+r)>>1); 
		ls(x)=merge(ls(x), ls(y), l, mid);
		rs(x)=merge(rs(x), rs(y), mid+1, r);
		upup(x), dlt(y);
		return x;
	}
	void updt(int& k, int l, int r, int tt) {
		if(!k) cnw(k);
		if(l == r) {
			++tr[k].gs;
			tr[k].sm=upd(tr[k].sm+to[l]);
			tr[k].ans=0;
			return ;
		} 
		int mid = ((l+r)>>1);
		if(tt <= mid)
			updt(ls(k), l, mid, tt);
		else
			updt(rs(k), mid+1, r, tt);
		upup(k);
	}
}A;

namespace FastIO {
	const int SIZE=(1<<21)+1;
	char ibuf[SIZE],obuf[SIZE],*iS,*iT,*oS=obuf,*oT=obuf;
	char* flush(){fwrite(obuf,1,oT-oS,stdout);return oT=obuf;}
	struct Flusher{~Flusher(){flush();}}flusher;
	inline char gc(){return iS==iT && (iT=(iS=ibuf)+fread(ibuf,1,SIZE,stdin),iS==iT)?EOF:*iS++;}
	inline void pc(char c){if(oT==oS+SIZE) flush();*oT++=c;}
	#define getchar gc
	#define putchar pc
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
}
using FastIO::gc;
using FastIO::pc;
using FastIO::read;
using FastIO::write;
int comp(qwq AA, qwq BB) {
	return AA.w < BB.w;
}
void dfs(int x, int fa, int w) {
	for(int y : az[x])
		if(y != fa) 
			dfs(y, x, w), rt[x]=A.merge(rt[x], rt[y], 1, cnt);
	A.updt(rt[x], 1, cnt, b[x]);
	sum[x]=upd(sum[x]+1LL*w*tr[rt[x]].ans%mod);
}
void sol(int w) {
	sort(a+1, a+1+n, comp);
	cnt=tot=gs=0;
	for(int i = 1; i <= n; ++i) {
		if(i == 1 || a[i].w != a[i-1].w)
			to[++cnt]=a[i].w%mod;
		b[a[i].d]=cnt;
		rt[i]=0;
	}
	dfs(1, 0, w);
}

signed main() {
	freopen("young.in", "r", stdin);
	freopen("young.out", "w", stdout);
	read(n);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), az[u].push_back(v), az[v].push_back(u);
	for(int i = 1; i <= n; ++i)
		read(c[i]), read(e[i]);
	for(int i = 1; i <= n; ++i)
		a[i]=qwq {i, c[i]};
	sol(1);
	for(int i = 1; i <= n; ++i)
		a[i]=qwq {i, e[i]};
	sol(1);
	for(int i = 1; i <= n; ++i)
		a[i]=qwq {i, (c[i]+e[i])};
	sol(1LL*(mod-1)*inv2%mod);
	for(int i = 1; i <= n; ++i)
		a[i]=qwq {i, (c[i]-e[i])};
	sol(1LL*(mod-1)*inv2%mod);
	for(int i = 1; i <= n; ++i)
		write(upd(sum[i]+sum[i]), '\n');
	FastIO::flusher.~Flusher(); 
	return 0 ;
}
