#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+5;
int n, k, q, gs[N], pd[N], ans[N], az[N];
struct qwq {
	int a, b;
}c[N];
struct pro {
	int l, r, ii;
}pr;
struct tree {
	int tr[N<<2], lzy[N<<2];
	#define ls (k<<1)
	#define rs ((k<<1)|1)
	void built(int k, int l, int r) {
		if(l == r) {
			tr[k]=az[l];
			return ;
		}
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
		tr[k]=max(tr[ls], tr[rs]);
	}
	void down(int k) {
		if(lzy[k] != 0) {
			tr[ls]+=lzy[k];
			tr[rs]+=lzy[k];
			lzy[ls]+=lzy[k];
			lzy[rs]+=lzy[k];
			lzy[k]=0;
		}
	}
	void updt(int k, int l, int r, int lq, int rq, int w) {
		if(lq <= l && r <= rq) {
			tr[k]+=w;
			lzy[k]+=w;
			return ;
		}
		down(k);
		int mid = ((l+r)>>1);
		if(lq <= mid)
			updt(ls, l, mid, lq, rq, w);
		if(mid+1 <= rq)
			updt(rs, mid+1, r, lq, rq, w);
		tr[k]=max(tr[ls], tr[rs]);
	}
	int ask(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq) 
			return tr[k];
		down(k);
		int mid = ((l+r)>>1), ret = 0;
		if(lq <= mid)
			ret=max(ret, ask(ls, l, mid, lq, rq));
		if(mid+1 <= rq)
			ret=max(ret, ask(rs, mid+1, r, lq, rq));
		tr[k]=max(tr[ls], tr[rs]);
		return ret;
	}
	#undef ls
	#undef rs
}A, B;
vector <pro> que[N];
vector <int> toa[N], tob[N];

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
	freopen("poker.in", "r", stdin);
	freopen("poker.out", "w", stdout);
	read(n), read(k);
	for(int i = 1; i <= k; ++i) {
		read(c[i].a), read(c[i].b);
		if(c[i].a > c[i].b) swap(c[i].a, c[i].b);
		toa[c[i].a].push_back(i), tob[c[i].b].push_back(i);
	}
	read(q);
	for(int i = 1; i <= q; ++i) {
		read(pr.l), read(pr.r), pr.ii=i;
		que[pr.l].push_back(pr);
	}
	for(int i = 1; i <= n; ++i) {
		gs[i]=gs[i-1]+toa[i].size();
		if(toa[i].size() == 0 && tob[i].size() == 0)
			pd[i]=1;
	}
	for(int i = 1; i <= n; ++i) 
		gs[i]=i-gs[i]+1/*, write(gs[i], ' ')*/, az[i]=gs[i];
//	puts("");
	A.built(1, 1, n);
	for(int i = 1; i <= n; ++i) 
		az[i]=pd[i];
	B.built(1, 1, n);
	for(int i = 1; i <= n; ++i) {
//		for(int j = 1; j <= n; ++j) 
//			cout<<A.ask(1, 1, n, j, j)<<" ";
//		cout<<" -> ";
		for(pro j : que[i]) {
			int mx = A.ask(1, 1, n, j.l, j.r), pdd = B.ask(1, 1, n, j.l, j.r);
//			cout<<j.ii<<" "<<mx<<" "<<pdd<<"\n";
			if(pdd || mx > j.l)
				ans[j.ii]=0;
			else
				ans[j.ii]=1;
		}
		for(int o : toa[i]) 
			A.updt(1, 1, n, i, c[o].b-1, 1);
		for(int o : tob[i]) 
			A.updt(1, 1, n, i, n, 1);
//		for(int j = 1; j <= n; ++j) 
//			cout<<A.ask(1, 1, n, j, j)<<" ";
//		puts("");
	}
	for(int i = 1; i <= q; ++i)
		if(ans[i])
			puts("Yes");
		else
			puts("No");
	return 0;
}
