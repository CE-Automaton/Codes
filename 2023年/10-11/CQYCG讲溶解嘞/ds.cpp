#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
const int N = 1e5+5;
int n, q, xx[N], yy[N], u, r, d, l;
vector <int> to[N];

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
	freopen("ds.in", "r", stdin);
	freopen("ds.out", "w", stdout);
	read(n), read(q);
	for(int i = 1; i <= n; ++i)
		read(xx[i]);
	for(int i = 1; i <= n; ++i)
		read(yy[i]), to[yy[i]].push_back(xx[i]);
	for(int i = 1; i <= n; ++i)
		sort(to[i].begin(), to[i].end());
	for(int i = 1; i <= q; ++i) {
		read(u), read(r), read(d), read(l);
		int ans = 0;
		for(int x = r; x >= l; --x) {
			if(to[x].size() == 0) continue;
			int l = 0, r = (int) to[x].size()-1, rr = -1, ll = -1;
			while(l <= r) {
				int mid = ((l+r)>>1);
				if(to[x][mid] <= u)
					rr=mid, l=mid+1;
				else
					r=mid-1;
			}
			l = 0, r = (int) to[x].size()-1;
			while(l <= r) {
				int mid = ((l+r)>>1);
				if(to[x][mid] >= d)
					ll=mid, r=mid-1;
				else
					l=mid+1;
			}
			if(ll == -1 || rr == -1 || ll > rr) continue;
			ans+=rr-ll+1;
			d=to[x][rr];
		}
		write(ans, '\n');
	}
	return 0;
}
