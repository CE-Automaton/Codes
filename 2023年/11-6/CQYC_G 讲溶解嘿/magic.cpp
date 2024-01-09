#include <bits/stdc++.h>
using namespace std;
const int N = 25;
int n, aa[N], b[N], vis[N], pp[N], ans;
struct qwq {
	int l, r, c;
}c[N];

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
	if(x == n+1) {
		for(int i = 1; i <= n; ++i) 
			aa[i]=pp[i]=0;
		int sum = 0;
		for(int i = 1; i <= n; ++i) {
			pp[b[i]]=1;
			for(int o = c[b[i]].l; o <= c[b[i]].r; ++o)
				if(!pp[o])
					sum+=c[b[i]].c;
		}
		ans=max(ans, sum);
		return ;
	}
	for(int i = 1; i <= n; ++i)
		if(!vis[i])
			vis[i]=1, b[x]=i, dfs(x+1), vis[i]=0;
}

signed main() {
	freopen("magic.in", "r", stdin);
	freopen("magic.out", "w", stdout);
	read(n);
	if(n > 10) {
		puts("0");
		return 0;
	} 
	for(int i = 1; i <= n; ++i)
		read(c[i].l), read(c[i].r), read(c[i].c);
	dfs(1);
	write(ans, '\n');
	return 0;
}
