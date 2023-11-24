#include <bits/stdc++.h>
using namespace std;
int n, s[15], a[15][15], xx[15], b[15], c[15], ans;

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
		for(int i = 1; i <= n; ++i) {
			b[i]=0;
			for(int j = i+1; j <= n+1; ++j)
				b[i]+=(xx[j] < xx[i]);
		}
		int pd = 1;
		for(int i = 1; i <= n; ++i) 
			if(b[i] < c[i]) {
				pd=0;
				break;
			}
			else
				if(b[i] > c[i]) {
					ans=0;
					for(int j = 1; j <= n; ++j)
						c[j]=b[j];
					break;
				}
		ans+=pd;
		return ;
	}
	for(int i = 1; i <= s[x]; ++i) {
		xx[x]=a[x][i];
		dfs(x+1);
	}
}

signed main() {
	freopen("marketeers.in", "r", stdin); 
	freopen("marketeers.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i) {
		read(s[i]);
		for(int j = 1; j <= s[i]; ++j)
			read(a[i][j]);
	}
	dfs(1);
	write(ans, '\n');
	return 0;
}
