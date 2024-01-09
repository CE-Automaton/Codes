#include <bits/stdc++.h>
using namespace std;
int n, h[5005], d[5005], vis[5005], ans[5005];

template <typename T> inline void read(T& s) {
	s=0; char ch = getchar(); while(ch<'0' || ch > '9') ch=getchar();
	while(ch >= '0'&& ch <= '9') s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
}
int lne; char put[105];
template <typename T> void write(T x) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
}
int pd(int i, int j, int k) {
	return (1LL*(h[i]-h[k])*(d[i]-d[j]) <= 1LL*(d[i]-d[k])*(h[i]-h[j]));
}
int dfs(int x) {
	if(x == n+1) {
		for(int i = 1; i <= n; ++i)
			write(ans[i]), putchar(' ');
		return 1;
	}
	for(int i = 1; i <= n; ++i)
		if(!vis[i]) {
			ans[x]=i;
			if(i >= 3 && !pd(ans[x-2], ans[x-1], ans[x]))
				continue;
			vis[i]=1;
			if(dfs(x+1))
				return 1;
			vis[i]=0;
		}
	return 0;
}

int main() {
	read(n);
	for(int i = 1; i <= n; ++i)
		read(h[i]), read(d[i]);
	if(!dfs(1)) 
		puts("-1");
	return 0;
}
