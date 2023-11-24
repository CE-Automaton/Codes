#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
const int N = 1e5+5;
int n, m, id, q, dfn[N], siz[N], cnt, dep[N], top[N], fa[N], haha[N], s[N], pw[N], inc[N], incc[N], jc[N], inv[N];
vector <int> to[N];
struct edgeorpue {
	int u, v, w;
}b[N], pro;
struct node {
	int sum, lcol, rcol, llen, rlen, pd;
};
struct tree {
	node tr[N<<2];
	void upup(node& ret, node ls, node rs) {
		ret.lcol=ls.lcol;
		ret.rcol=rs.rcol;
		if(ls.pd) {
			if(rs.pd) {
				if(ls.lcol == rs.rcol)
					ret.pd=1, ret.sum=pw[ls.llen+rs.rlen], ret.llen=ret.rlen=ls.llen+rs.rlen;
				else
					ret.pd=0, ret.sum=1LL*ls.sum*rs.sum%mod, ret.llen=ls.llen, ret.rlen=rs.rlen;
			}
			else {
				ret.pd=0, ret.sum=1LL*ls.sum*rs.sum%mod, ret.llen=ls.llen, ret.rlen=rs.rlen;
				if(ls.rcol == rs.lcol)
					ret.sum=1LL*ret.sum*inc[ls.rlen]%mod*inc[rs.llen]%mod*pw[ls.rlen+rs.llen]%mod, ret.llen=ls.rlen+rs.llen;
			}
		}
		else {
			if(rs.pd) {
				ret.pd=0, ret.sum=1LL*ls.sum*rs.sum%mod, ret.llen=ls.llen, ret.rlen=rs.rlen;
				if(ls.rcol == rs.lcol)
					ret.sum=1LL*ret.sum*inc[ls.rlen]%mod*inc[rs.llen]%mod*pw[ls.rlen+rs.llen]%mod, ret.rlen=ls.rlen+rs.llen;
			}
			else {
				ret.pd=0, ret.sum=1LL*ls.sum*rs.sum%mod, ret.llen=ls.llen, ret.rlen=rs.rlen;
				if(ls.rcol == rs.lcol)
					ret.sum=1LL*ret.sum*inc[ls.rlen]%mod*inc[rs.llen]%mod*pw[ls.rlen+rs.llen]%mod;
			}
		} 
	}
	void updt(int k, int l, int r, int to, int w) {
		if(l == r) {
			tr[k].sum=pw[1];
			tr[k].pd=1;
			tr[k].lcol=tr[k].rcol=w;
			tr[k].llen=tr[k].rlen=1;
			return ;
		} 
		int mid = ((l+r)>>1);
		if(to <= mid)
			updt(k*2, l, mid, to, w);
		else
			updt(k*2+1, mid+1, r, to, w);
		upup(tr[k], tr[k*2], tr[k*2+1]);
	}
	node find(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq)
			return tr[k];
		int mid = ((l+r)>>1);
		node ret;
		if(lq <= mid && mid+1 <= rq)
			upup(ret, find(k*2, l, mid, lq, rq), find(k*2+1, mid+1, r, lq, rq));
		else
			if(lq <= mid)
				ret=find(k*2, l, mid, lq, rq);
			else
				ret=find(k*2+1, mid+1, r, lq, rq);
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
template <typename T> void write(T x) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
void dfs(int x, int faa) {
	dep[x]=dep[faa]+1;
	fa[x]=faa;
	siz[x]=1;
	for(auto y : to[x]) 
		if(y != faa)
			dfs(y, x), siz[x]+=siz[y];
}
void dfs2(int x, int faa) {
	dfn[x]=++cnt;
	int mxson = 0;
	for(auto y : to[x]) 
		if(y != faa)
			if(siz[y] > siz[mxson])
				mxson=y;
	if(mxson == 0) return ;
	top[mxson]=top[x];
	dfs2(mxson, x);
	for(auto y : to[x]) 
		if(y != faa && y != mxson) {
			top[y]=y;
			dfs2(y, x);
		}
}
int c(int x, int y) {
	return 1LL*jc[x]*incc[x-y]%mod*incc[y]%mod;
}

int main() {
	freopen("umi.in", "r", stdin);
	freopen("umi.out", "w", stdout);
	read(n), read(m), read(id);
	pw[1]=1;
	inc[1]=mod-mod/2;
	inv[0]=inv[1]=incc[0]=incc[1]=jc[0]=jc[1]=1;
	for(int i = 1; i <= n; ++i)
		read(s[i]);
	for(int i = 2; i <= n; ++i)
		pw[i]=upd(pw[i-1]+pw[i-1]), inc[i]=upd(inc[i-1]+inc[i-1]);
	for(int i = 2; i <= m; ++i)
		jc[i]=1LL*jc[i-1]*i%mod, inv[i]=1LL*inv[mod%i]*(mod-mod/i)%mod, incc[i]=1LL*incc[i-1]*inv[i]%mod;
	for(int i = 1; i <= n-1; ++i)
		read(b[i].u), read(b[i].v), 
		to[b[i].u].push_back(b[i].v), to[b[i].v].push_back(b[i].u);
	dfs(1, 1);
	top[1]=1;
	dfs2(1, 1);
	for(int i = 1; i <= n; ++i)
		A.updt(1, 1, n, dfn[i], s[i]);
	read(q);
	for(int i = 1; i <= q; ++i) {
		read(pro.u), read(pro.v);
		int l=pro.u, r=pro.v;
		node ll, rr;
		int pdll, pdrr, len = 0;
		pdll=pdrr=0;
		while(top[l] != top[r]) {
			if(dep[top[l]] < dep[top[r]]) {
				if(pdrr == 0)
					rr=A.find(1, 1, n, dfn[top[r]], dfn[r]), len+=dfn[r]-dfn[top[r]]+1, pdrr=1;
				else
					A.upup(rr, A.find(1, 1, n, dfn[top[r]], dfn[r]), rr), len+=dfn[r]-dfn[top[r]]+1;
				r=fa[top[r]];
			}
			else {
				if(pdll == 0)
					ll=A.find(1, 1, n, dfn[top[l]], dfn[l]), len+=dfn[l]-dfn[top[l]]+1, pdll=1;
				else
					A.upup(ll, A.find(1, 1, n, dfn[top[l]], dfn[l]), ll), len+=dfn[l]-dfn[top[l]]+1;
				l=fa[top[l]];
			}
		}
		if(dfn[l] >= dfn[r]) {
			if(pdll == 0)
				ll=A.find(1, 1, n, dfn[r], dfn[l]), len+=dfn[l]-dfn[r]+1, pdll=1;
			else
				A.upup(ll, A.find(1, 1, n, dfn[r], dfn[l]), ll), len+=dfn[l]-dfn[r]+1;
		}
		else {
			if(pdrr == 0)
				rr=A.find(1, 1, n, dfn[l], dfn[r]), pdrr=1, len+=dfn[r]-dfn[l]+1;
			else
				A.upup(rr, A.find(1, 1, n, dfn[l], dfn[r]), rr), len+=dfn[r]-dfn[l]+1;
		}
		if(!pdll && !pdrr) {
			putchar('0'), putchar('\n');
			continue;
		}
		if(pdll && pdrr) 
			swap(ll.lcol, ll.rcol), swap(ll.llen, ll.rlen), A.upup(ll, ll, rr);
		else if(pdrr) ll=rr;
//		cout<<len<<" "<<c(m, 2*len)<<" "<<ll.sum<<": \n";
		write(1LL*ll.sum*c(m, 2*len)%mod), putchar('\n');
	}
	return 0;
}
