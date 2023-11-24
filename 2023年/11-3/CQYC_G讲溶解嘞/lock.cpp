#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int n, m, dp[N][28], mn[N][28], u;
char s[N], v;

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
void sol(int l = 1) {
	for(int i = l; i <= n; ++i) {
		for(int j = 1; j <= 26; ++j)
			dp[i][j]=abs(s[i]-'a'+1-j)+mn[i-1][j];
		mn[i][1]=dp[i][1];
		for(int j = 2; j <= 26; ++j)
			mn[i][j]=min(mn[i][j-1], dp[i][j]);
	}
	write(mn[n][26], '\n');
}

signed main() {
	freopen("lock.in", "r", stdin);
	freopen("lock.out", "w", stdout);
	scanf("%s", s+1);
	n=strlen(s+1);
	sol();
	read(m);
	for(int i = 1; i <= m; ++i) {
		read(u), scanf(" %c", &v);
		s[u]=v;
		sol(u);
	}
	return 0;
}
