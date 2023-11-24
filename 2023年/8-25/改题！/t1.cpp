#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+5, M = 1e6+5;
int n, m, ans[N], vis[M], sm[N], tot, pd[N], ed[N], lst[M];
struct qwq {
	int a, b;
}p[N];

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
//	freopen("marketplace.in", "r", stdin); 
//	freopen("marketplace.out", "w", stdout);
	read(n), read(m);
	for(int i = 1; i <= n; ++i) {
		read(p[i].a), read(p[i].b);
		if(tot == i-1)
			if(!vis[p[i].a])
				sm[++tot]=p[i].a, vis[p[i].a]=1;
			else if(!vis[p[i].b])
				sm[++tot]=p[i].b, vis[p[i].b]=1, pd[i]=1;
	}
	if(tot == n) 
		for(int i = 1; i <= n; ++i) {
			if(pd[i] || vis[p[i].b])
				break;
			sm[++tot]=p[i].b, vis[p[i].b]=1, pd[i]=1;
		}
	for(int i = tot; i >= 1; --i) {
		lst[sm[i]]=i;
		if(i > n || pd[i] || vis[p[i].b]) {
			++ans[(i-1)%n+1];
			ed[i]=(i-1)%n+1;
		}
		else {
			ed[i]=ed[lst[p[i].b]];
			++ans[ed[i]];
		}
		vis[sm[i]]=0;
	}
	ans[tot%n+1]+=ans[0]+m-tot;
	for(int i = 1; i <= n; ++i)
		write(ans[i], '\n');
	return 0;
}
