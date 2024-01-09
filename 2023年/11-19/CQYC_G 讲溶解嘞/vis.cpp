#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N = 3e5+5;
int n, m, u, v, l[N], r[N], ans, zhan[N], tot;

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
int upd(int x) {
	return (x >= mod ? x-mod : x);
}

signed main() {
	freopen("vis.in", "r", stdin);
	freopen("vis.out", "w", stdout);
	read(n), read(m);
	for(int i = 1; i <= n; ++i)
		l[i]=r[i]=i;
	int pd = 1, pd2 = 1;
	for(int i = 1; i <= m; ++i)
		read(u), read(v), pd&=((u > v)&(u == i+1)), 
		l[u]=min(l[u], v), r[u]=max(r[u], v), 
		pd2&=(u < v);
	if(pd && m == n-1) {
		for(int i = 1, mx = 1; i <= n; ++i) {
			mx=max(mx, r[i]);
			if(mx <= i)
				++ans;
		}
		write(ans, '\n');
		return 0;
	}
	if(pd2) {
		r[0]=n+1;
		zhan[++tot]=0;
		for(int i = 1; i <= n; ++i) {
			while(tot && r[zhan[tot]] <= r[i])
				--tot;
			zhan[++tot]=i;
			int ll = 1, rr = tot, ret = tot+1;
			while(ll <= rr) {
				int mid = ((ll+rr)>>1);
				if(r[zhan[mid]] <= i)
					ret=mid, rr=mid-1;
				else
					ll=mid+1;
			}
			ans=upd(ans+i-zhan[ret-1]);
		}
		write(ans, '\n');
		return 0;
	}
	for(int ll = 1; ll <= n; ++ll) {
		int mx = 0;
		for(int rr = ll; rr <= n; ++rr) {
			if(l[rr] < ll) break;
			mx=max(mx, r[rr]);
			if(mx <= rr)
				ans=upd(ans+1);
		}
	}
	write(ans, '\n');
	return 0;
}