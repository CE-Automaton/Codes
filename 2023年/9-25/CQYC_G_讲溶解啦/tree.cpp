#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N = 5e5+5;
int n, k, fa[N], cnt[N], in[N];
long long ans;
vector <int> to[N];
struct qwq {
	int u, v;
}ed[N];
struct tree {
	long long tr[N<<3]/*x^2的和*/, trr[N<<3]/*x的和*/, lzy[N<<3];
	#define ls (k<<1)
	#define rs ((k<<1)|1)
	void upup(int k) {
		tr[k]=(tr[ls]+tr[rs])%mod;
		trr[k]=(trr[ls]+trr[rs])%mod;
	}
	void down(int k, int l, int mid, int r) {
		if(lzy[k] != 0) {
			(tr[ls]+=trr[ls]*2%mod*lzy[k]%mod+1*lzy[k]*lzy[k]%mod*(mid-l+1)%mod)%=mod;
			(trr[ls]+=lzy[k]*(mid-l+1)%mod)%=mod;
			(lzy[ls]+=lzy[k])%=mod;
			
			(tr[rs]+=trr[rs]*2%mod*lzy[k]%mod+1*lzy[k]*lzy[k]%mod*(r-mid)%mod)%=mod;
			(trr[rs]+=lzy[k]*(r-mid)%mod)%=mod;
			(lzy[rs]+=lzy[k])%=mod;
			
			lzy[k]=0;
		}
	}
	void built(int k, int l, int r) {
		lzy[k]=0;
		tr[k]=0;
		trr[k]=0;
		if(l == r) 
			return ;
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
	}
	void updt(int k, int l, int r, int lq, int rq, long long w) {
		if(lq <= l && r <= rq) {
			(tr[k]+=trr[k]*2%mod*w%mod+1*(r-l+1)*w%mod*w%mod)%=mod;
			(trr[k]+=w*(r-l+1)%mod)%=mod;
			(lzy[k]+=w)%=mod;
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
	int ask(int k, int l, int r, int lq) {
		if(l == r) 
			return tr[k];
		int mid = ((l+r)>>1);
		down(k, l, mid, r);
		if(lq <= mid)
			return ask(ls, l, mid, lq);
		else
			return ask(rs, mid+1, r, lq);
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
int find(int x) {
	return (x == fa[x] ? x : fa[x]=find(fa[x]));
}
void merge(int x, int y) {
	x=find(x), y=find(y);
	if(cnt[x] < cnt[y])
		swap(x, y);
	fa[y]=x;
	cnt[x]+=cnt[y];
}
int comp(qwq AA, qwq BB) {
	return AA.v < BB.v;
}

signed main() {
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	read(n), read(k);
	for(int i = 2; i <= n; ++i) {
		read(ed[i].u), read(ed[i].v);
		to[ed[i].u].push_back(ed[i].v), to[ed[i].v].push_back(ed[i].u);
		++in[ed[i].u], ++in[ed[i].v];
		if(ed[i].u > ed[i].v) swap(ed[i].u, ed[i].v);
		if(k == 1) {
			(ans+=mod-1LL*ed[i].u*(n-ed[i].v+1)%mod)%=mod;
		} 
	}
	if(k == 1) {
		for(int i = 1; i <= n; ++i)
			ans=(ans+1LL*i*(n-i+1)%mod)%mod; 
		write(ans, '\n');
		return 0;
	}
	sort(ed+2, ed+1+n, comp);
	int l = 2;
	A.built(1, 1, n);
	for(int r = 1; r <= n; ++r) {
		A.updt(1, 1, n, 1, r, 1);
		while(l <= n && ed[l].v <= r) {
//			cout<<1<<" "<<ed[l].u<<"!?!?\n";
			A.updt(1, 1, n, 1, ed[l].u, mod-1);
			++l;
		}
		(ans+=A.tr[1])%=mod;
//		for(int i = r; i >= 1; --i)
//			write(A.ask(1, 1, n, i), ' ');
//		cout<<"\n";
	}
	write(ans%mod, '\n');
	return 0;
}
