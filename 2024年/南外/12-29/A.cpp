#include <bits/stdc++.h>
#define inf 1000000007
using namespace std;
const int N = 5e5+5, M = 10;
int n, m, u, v, p[N], pp[N];
long long ans;
vector <int> to[N];
struct node {
	int lzy;
	pair<int, int> val[M];
}tr[N<<2];
struct tree {
	#define ls (k<<1)
	#define rs (ls|1)
	void add(int k, int v) {
		tr[k].lzy+=v;
		for(int i = 1; i <= 8; i++) 
			tr[k].val[i].second+=v;
	}
	void down(int k) {
		if(tr[k].lzy == 0) return;
		add(ls, tr[k].lzy);
		add(rs, tr[k].lzy);
		tr[k].lzy=0;
	}
	void upup(int k) {
		for (int i = 1, l = 1, r = 1; i <= 8; i++) 
			if(!tr[ls].val[l].first && !tr[rs].val[r].first)
				tr[k].val[i]={0, inf};
			else if(l <= 8 && r <= 8 && tr[ls].val[l].second == tr[rs].val[r].second) 
				tr[k].val[i]={tr[ls].val[l].first+tr[rs].val[r].first, tr[ls].val[l].second}, ++l, ++r;
			else if(tr[ls].val[l].second < tr[rs].val[r].second) 
				tr[k].val[i]=tr[ls].val[l], ++l;
			else 
				tr[k].val[i]=tr[rs].val[r], ++r;
	}
	void build(int k, int l, int r) {
		tr[k].lzy=0;
		if(l == r) {
			tr[k].val[1]={1, 0};
			for(int j = 2; j <= 8; j++) 
				tr[k].val[j]={0, inf};
			return;
		}
		int mid = ((l+r)>>1);
		build(ls, l, mid);
		build(rs, mid+1, r);
		upup(k);
	}
	void updt(int k, int l, int r, int lq, int rq, int v) {
		if (lq <= l && r <= rq) {
			add(k, v);
			return;
		}
		down(k);
		int mid = ((l+r)>>1);
		if(lq <= mid)
			updt(ls, l, mid, lq, rq, v);
		if(mid+1 <= rq)
			updt(rs, mid+1, r, lq, rq, v);
		upup(k);
	}
}QAQ/*打包的线段树*/;

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
	freopen("shovel.in", "r", stdin);
	freopen("shovel.out", "w", stdout);
    read(n), read(m);
	for(int i = 1; i <= n; ++i)
		read(p[i]), pp[p[i]]=i;
	for(int i = 2; i <= n; ++i) {
		read(u), read(v);
		to[u].push_back(v);
		to[v].push_back(u);
	}
	QAQ.build(1, 1, n);
	for(int i = 1; i <= n; ++i) {
		QAQ.updt(1, 1, n, 1, i, 1);
		int x = pp[i];
		for(int j : to[x])
			if(p[j] <= i)
				QAQ.updt(1, 1, n, 1, p[j], -1);
		for(int j = 1; j <= 8; ++j)
			if(tr[1].val[j].second && tr[1].val[j].second <= m)
				ans+=tr[1].val[j].first;
	}
	write(ans, '\n');
	return 0;
}