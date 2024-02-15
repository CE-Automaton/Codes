#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
const int N = 2e5+5;
int n, m, op, q, lst, rt[N], gs;
set<pii> az;
struct qwq {
	int u, v, w;
}a[N], pro;
struct node {
	int ls, rs;
	LL ws;
}tr[N*20];
struct tree {
	#define ls(x) tr[x].ls
	#define rs(x) tr[x].rs
	#define ws(x) tr[x].ws
	void updt(int &k, int l, int r, int to, int ws) {
		tr[++gs]=tr[k], k=gs;
		ws(k)+=ws;
		if(l == r) return ;
		int mid = ((l+r)>>1);
		if(to <= mid)
			updt(ls(k), l, mid, to, ws);
		else
			updt(rs(k), mid+1, r, to, ws);
	}
};

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
int comp(qwq AA, qwq BB) {
	return AA.u < BB.u;
}

signed main() {
	read(n), read(m), read(op);
	for(int i = 1; i <= n; ++i)
		read(a[i].u), read(a[i].v), read(a[i].w);
	sort(a+1, a+1+n, comp);
	for(int i = 1; i <= n; ++i)
	return 0;
}