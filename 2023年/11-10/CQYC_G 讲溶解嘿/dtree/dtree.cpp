#include <bits/stdc++.h>
using namespace std;
const int N = 5e2+5;
int n, p, ans, fa[N], vis[N][2], siz[N];

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
void dfs(int x) {
	if(x == 0) {
		for(int i = 1; i <= n; ++i) {
			siz[i]=1;
			if(vis[i][0])
				siz[i]+=siz[vis[i][0]];
			if(vis[i][1])
				siz[i]+=siz[vis[i][1]];
			if(vis[i][0] && vis[i][1]) 
				ans=(ans+siz[vis[vis[i][0]][1]]+siz[vis[vis[i][1]][0]]+2)%p;
		}
		return ;
	}
	for(int i = x+1; i <= n; ++i) {
		if(vis[i][0] == 0) {
			vis[i][0]=x;
			dfs(x-1);
			vis[i][0]=0;
		}
		if(vis[i][1] == 0) {
			vis[i][1]=x;
			dfs(x-1);
			vis[i][1]=0;
		}
	}
}

signed main() {
	freopen("dtree.in", "r", stdin);
	freopen("dtree.out", "w", stdout);
	read(n), read(p);
	dfs(n-1);
	write(ans, '\n');
	return 0;
}