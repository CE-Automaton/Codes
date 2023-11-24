#include <bits/stdc++.h>
#define inf 100000000000000000LL
using namespace std;
const int N = 2e3+5;
int n, q, u;
long long v, a[N], dp[N][N];
char s[N];

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
int chg(int i, char to) {
	return (s[i] == to ? 0 : a[i]);
}
void solv() {
	for(int i = 1; i <= 2*n; ++i)
		for(int j = 1; j <= 2*n; ++j)
			dp[i][j]=inf;
	for(int i = 1; i+1 <= 2*n; ++i) 
		dp[i][i+1]=chg(i, '(')+chg(i+1, ')');
	for(int len = 4; len <= 2*n; ++len)
		for(int i = 1, j = len; j <= 2*n; ++i, ++j) {
			dp[i][j]=min(dp[i][j], dp[i+1][j-1]+chg(i, '(')+chg(j, ')'));
			for(int le = 2; le < len; le+=2)
				dp[i][j]=min(dp[i][j], dp[i][i+le-1]+dp[i+le][j]);
		}
	write(dp[1][2*n], '\n');
	return ;
}

signed main() {
	freopen("brackets.in", "r", stdin);
	freopen("brackets.out", "w", stdout);
	read(n), read(q);
	for(int i = 1; i <= 2*n; ++i)
		read(a[i]);
	scanf("%s", s+1);
	solv();
	for(int i = 1; i <= q; ++i) {
		read(u), read(v);
		a[u]=v;
		solv();
	}
	return 0;
}
