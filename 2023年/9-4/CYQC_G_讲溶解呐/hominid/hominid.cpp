#include <bits/stdc++.h>
using namespace std;
const int N = 1e3+5;
int n, gs, pdd[N], ans;
char s[N][N];

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

signed main() {
	freopen("hominid.in", "r", stdin);
	freopen("hominid.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i)
		scanf("%s", s[i]+1);
	for(int i = 1; i <= n; ++i) {
		int pd = 0;
		for(int j = 1; j <= n; ++j)
			if(s[j][i] != 'x') {
				pd=1;
				break;
			}
		gs+=pd;
		for(int j = 1; j <= n; ++j)
			if(s[i][j] == 'x')
				pdd[j]|=1;
	}
	ans = 1000000007;
	for(int i = 1; i <= n; ++i) {
		int pd = 1, op = 0;
		for(int j = 1; j <= n; ++j)
			if(s[i][j] != 'x') {
				pd=0;
				++op;
			}
		if(pd) {
			write(gs, '\n');
			return 0;
		}
		else 
			if(pdd[i]) 
				ans=min(ans, op+gs);
	}
	write(ans, '\n');
	return 0;
}
