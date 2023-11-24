#include <bits/stdc++.h>
using namespace std;
const signed N = 5e3+5;
int n, mod, m, aaa[15], c[N][N], ans[2][N][N], sum;

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
	freopen("au.in", "r", stdin);
	freopen("au.out", "w", stdout);
	read(n), read(mod);
	aaa[1]=1, aaa[2]=0, aaa[3]=3, aaa[4]=4, aaa[5]=125, aaa[6]=306, aaa[7]=2317;
	if(n <= 6) {
		write(aaa[n], '\n');
		return 0;
	}
	for(int i = 0; i <= n; ++i)
		c[i][0]=1;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= i; ++j)
			c[i][j]=upd(c[i-1][j-1]+c[i-1][j]);
	m=(n+3)/4;
	ans[0][0][0]=c[n][1];
	int now = 0;
	for(int i = m; i >= 2; --i) {
		now^=1;
		for(int lg = 0; lg <= n/2; ++lg)
			for(int ls = 0; ls <= n-1; ++ls) 
				ans[now][lg][ls]=ans[now^1][lg][ls];
		int w = 1;
		for(int gs = 1; gs <= n/i; ++gs) {
			w=1LL*w*c[gs*(i-1)][i-1]%mod;
			for(int lg = 0; gs+lg <= n/2; ++lg) 
				for(int ls = 0; gs*i+ls <= n-1; ++ls) 
					if(ans[now^1][lg][ls] != 0)	
						ans[now][lg+gs][ls+gs*i]=upd(ans[now][lg+gs][ls+gs*i]+
						1LL*ans[now^1][lg][ls]*c[n-1-ls][gs*i]%mod*c[gs*i][gs]%mod*w%mod);
		}
	}
	sum=c[n][1];
	for(int i = 1; i <= n/2; ++i)
		for(int ls = 0; ls <= n-1; ++ls)
			if(n-1-ls+i >= n/2)
				sum=upd(sum+ans[now][i][ls])/*, cout<<i<<" "<<ls<<" "<<ans[now][i][ls]<<"!\n"*/;
	write(sum, '\n');
	return 0;
}
