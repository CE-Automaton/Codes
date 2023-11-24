#include <bits/stdc++.h>
using namespace std;
int n, k, vis[15], zhan[15], ans;

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
		int lst = 1;
		for(int i = 2; i <= n; ++i)
			if(zhan[i] < zhan[i-lst]) {
				++lst;
				if(lst > k) {
					if(zhan[i-lst+1] != n)
						++ans;
					return ;
				}
			}
			else
				lst=1;
		return ;
	}
	for(int i = 1; i <= n; ++i)
		if(vis[i] == 0)
			zhan[x]=i, vis[i]=1, dfs(x+1), vis[i]=0;
}

signed main() {
	freopen("arisu.in", "r", stdin);
	freopen("arisu.out", "w", stdout);
	read(n), read(k); 
	dfs(1);
	write(ans, '\n');
	return 0;
}
