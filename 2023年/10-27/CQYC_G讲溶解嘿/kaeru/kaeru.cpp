#include <bits/stdc++.h>
using namespace std;
const int N = 5e5+5;
int n, q, typ, u, v, vis[N][2], sum[N][2], ans, lst, r[N][2], a, b, c, d;
vector <int> to[N][2];

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
	freopen("kaeru.in", "r", stdin);
	freopen("kaeru.out", "w", stdout);
	read(n), read(q), read(typ);
	for(int i = 1; i <= n; ++i)
		read(u), read(v), vis[u][0]=1, vis[v][1]=1, 
		to[u][0].push_back(v), to[v][1].push_back(u);
	r[500001][0]=r[500001][1]=500001;
	for(int i = 500000; i >= 0; --i)
		r[i][0]=(vis[i+1][0] ? i+1 : r[i+1][0]), 
		r[i][1]=(vis[i+1][1] ? i+1 : r[i+1][1]);
	for(int i = 1; i <= 500000; ++i) {
		if(vis[i][0])
			sort(to[i][0].begin(), to[i][0].end());
		if(vis[i][1])
			sort(to[i][1].begin(), to[i][1].end());
	}
	for(int i = 1; i <= q; ++i) {
		read(a), read(b), read(c), read(d);
		ans=0;
		a^=lst*typ;
		b^=lst*typ;
		c^=lst*typ;
		d^=lst*typ;
		if(vis[a][0] == 1) {
			int l = 0, r = (int) to[a][0].size()-1, tt = -1;
			while(l <= r) {
				int mid = ((l+r)>>1);
				if(to[a][0][mid] >= c)
					tt=mid, r=mid-1;
				else
					l=mid+1;
			}
			if(tt != -1 && to[a][0][tt] <= d)
				++ans;
		}
		for(int i = r[a][0]; i <= b; i=r[i][0]) {
			int l = 0, r = (int) to[i][0].size()-1, tt = -1;
			while(l <= r) {
				int mid = ((l+r)>>1);
				if(to[i][0][mid] >= c)
					tt=mid, r=mid-1;
				else
					l=mid+1;
			}
			if(tt != -1 && to[i][0][tt] <= d)
				++ans;
		}
		
		if(vis[c][1] == 1) {
			int l = 0, r = (int) to[c][1].size()-1, tt = -1;
			while(l <= r) {
				int mid = ((l+r)>>1);
				if(to[c][1][mid] >= a)
					tt=mid, r=mid-1;
				else
					l=mid+1;
			}
			if(tt != -1 && to[c][1][tt] <= b)
				++ans;
		}
		for(int i = r[c][1]; i <= d; i=r[i][1]) {
			int l = 0, r = (int) to[i][1].size()-1, tt = -1;
			while(l <= r) {
				int mid = ((l+r)>>1);
				if(to[i][1][mid] >= a)
					tt=mid, r=mid-1;
				else
					l=mid+1;
			}
			if(tt != -1 && to[i][1][tt] <= b)
				++ans;
		}
		lst=ans;
		write(ans, '\n');
	}
	return 0;
}
