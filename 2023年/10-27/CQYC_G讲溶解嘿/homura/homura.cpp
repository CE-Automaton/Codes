#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N = 1e5+5;
int n, m, c[15], d[15], ans;
char l[N], r[N]; 

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
void dfs(int x, int k) {
	if(x == 9) {
		c[x]=k;
		for(int i = l[m]-'0'+1; i+1 <= r[m]-'0'; ++i)
			if(c[i]) {
				ans=upd(ans+1);
				return ;
			}
		int now = 9, pd = 1;
		if(c[l[m]-'0']) {
			for(int i = 0; i <= 9; ++i)
				d[i]=c[i];
			--d[l[m]-'0'];//固定首位 
			while(now >= 0 && d[now] == 0)
				--now;
			for(int i = m-1; i >= 1; --i) {
				if(now < l[i]-'0') {
					pd=0;
					break;
				}
				if(now > l[i]-'0') {
					ans=upd(ans+1);
					return ;
				}
				--d[l[i]-'0'];
				while(now >= 0 && d[now] == 0)
					--now;
			}
			if(pd) {
				ans=upd(ans+1);
				return ;
			}
		}
		if(c[r[m]-'0']) {
			pd=1;
			for(int i = 0; i <= 9; ++i)
				d[i]=c[i];
			now=0;
			--d[r[m]-'0'];//固定首位
			while(now <= 9 && d[now] == 0)
				++now;
			for(int i = m-1; i >= 1; --i) {
				if(now > r[i]-'0') {
					pd=0; 
					break;
				}
				if(now < r[i]-'0') {
					ans=upd(ans+1);
					return ;
				}
				--d[r[i]-'0'];
				while(now <= 9 && d[now] == 0)
					++now;
			}
			if(pd) {
				ans=upd(ans+1);
				return ; 
			}
		} 
		return ;
	}
	for(int o = 0; o <= k; ++o)
		c[x]=o, dfs(x+1, k-o), c[x]=0;
}

signed main() {
	freopen("homura.in", "r", stdin);
	freopen("homura.out", "w", stdout);
	scanf("%s %s", l+1, r+1);
	n=strlen(l+1);
	for(int i = 1; i+i <= n; ++i)
		swap(l[i], l[n-i+1]);
	m=strlen(r+1);
	for(int i = 1; i+i <= m; ++i)
		swap(r[i], r[m-i+1]);
	for(int i = n+1; i <= m; ++i)
		l[i]='0';
	while(m >= 1 && l[m] == r[m])
		--m;
	if(m == 0) {
		puts("1");
		return 0;
	}
	dfs(0, m);
	write(ans%mod, '\n');
	return 0;
}
