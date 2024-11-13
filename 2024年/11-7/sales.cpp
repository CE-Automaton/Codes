#include <bits/stdc++.h>
#define inf 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e5+5;
int n, s[N], a[N], gs, rt[N], ans[N];
struct node {
	int ls, rs, w, ss;
}tr[N*20];
struct tree {
	#define ls(k) tr[k].ls
	#define rs(k) tr[k].rs
	#define w(k) tr[k].w
	#define ss(k) tr[k].ss
	void updt(int &k, int l, int r, int to) {
		tr[++gs]=tr[k], k=gs;
		if(l == r) {
			++tr[k].w;
			tr[k].ss+=l;
			return ;
		}
		int mid = ((l+r)>>1);
		if(to <= mid)
			updt(ls(k), l, mid, to);
		else
			updt(rs(k), mid+1, r, to);
		tr[k].w=w(ls(k))+w(rs(k));
		tr[k].ss=ss(ls(k))+ss(rs(k));
	}
	int ask(int k, int l, int r, int w) {
		if(l == r) return w*l;
		int mid = ((l+r)>>1);
		if(w <= w(ls(k)))
			return ask(ls(k), l, mid, w);
		return ask(rs(k), mid+1, r, w-w(ls(k)))+ss(ls(k));
	}
}A;

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
void solve(int l, int r, int L, int R) {
	if(L > R) return ;
	int sum = -1, now = ((L+R)>>1);
	ans[now]=inf;
	for(int mid = max(l, now); mid <= r; ++mid) {
		int op = A.ask(rt[mid], 0, 1000, now)+s[mid]*2;
		if(op < ans[now])
			ans[now]=op, sum = mid;
	}
	// debug(l, r, L, R, now, ans[now], sum, "???\n");
	solve(l, sum, L, now-1);
	solve(sum, r, now+1, R);
}

signed main() {
	// File("sales");
	read(n);
	for(int i = 1; i <= n; ++i)
		read(s[i]);
	for(int i = 1; i <= n; ++i)
		read(a[i]), rt[i]=rt[i-1], A.updt(rt[i], 0, 1000, a[i]);
	solve(1, n, 1, n);
	for(int i = 1; i <= n; ++i)
		write(ans[i], '\n');
	return 0;
}