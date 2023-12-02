#include <bits/stdc++.h>
using namespace std;
const int N = 1e3+5;
int n, q, sum[N][N], ls[N], hs[N], sm, a, b, c, d;
char p[N][N];

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
long long sol(int x, int y, int xx, int yy) {
	return (sum[xx+1][yy+1]-sum[xx+1][y]-sum[x][yy+1]+sum[x][y]);
}

signed main() {
	read(n), read(q);
	for(int i = 1; i <= n; ++i) 
		scanf("%s", p[i]+1);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			sum[i][j]=(p[i][j] == 'W' ? 0 : 1)+sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1], 
			hs[i]+=(p[i][j] == 'W' ? 0 : 1), ls[j]+=(p[i][j] == 'W' ? 0 : 1);
	for(int i = 1; i <= n; ++i)
		hs[i]+=hs[i-1], ls[i]+=ls[i-1];
	for(int i = 1; i <= q; ++i) {
		read(a), read(b), read(c), read(d);
		int A = a/n, B = b/n, C = c/n, D = d/n;
		a%=n, b%=n, c%=n, d%=n;
		long long ans = 0;
		if(A == C) {
			if(B == D) 
				ans=sol(a, b, c, d);
			else 
				ans=sol(a, b, c, n-1)+sol(a, 0, c, d)+1LL*sol(a, 0, c, n-1)*(D-B-1);
		}
		else {
			if(B == D) 
				ans=sol(a, b, n-1, d)+sol(0, b, c, d)+1LL*sol(0, b, n-1, d)*(C-A-1);
			else 
				ans=sol(a, b, n-1, n-1)+sol(a, 0, n-1, d)+sol(0, b, c, n-1)+sol(0, 0, c, d)+
				1LL*(D-B-1)*(sol(a, 0, n-1, n-1)+sol(0, 0, c, n-1))+1LL*(C-A-1)*(sol(0, b, n-1, n-1)+sol(0, 0, n-1, d))+
				1LL*(D-B-1)*(C-A-1)*sol(0, 0, n-1, n-1);
		}
		write(ans, '\n');
	}
	return 0;
}
