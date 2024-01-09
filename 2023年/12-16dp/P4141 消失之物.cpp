#include <bits/stdc++.h>
using namespace std;
const int N = 3e3+5;
int n, m, w[N], f[N], g[N];

template <typename T> void read(T& x) {
	x = 0; int f = 0; char c = getchar();
	while(c < '0' || c > '9') f |= (c == '-'), c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x);
}
int lne; char put[105];
template <typename T> void write(T x) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
}

signed main() {
	read(n), read(m);
	f[0]=1;
	for(int i = 1; i <= n; ++i) {
		read(w[i]);
		for(int j = m; j >= w[i]; --j)
			f[j]=(f[j]+f[j-w[i]])%10;
	}
	for(int i = 1; i <= n; ++i) {
		for(int j = m; j >= 0; --j)
			g[j]=f[j];
		for(int j = w[i]; j <= m; ++j)
			g[j]=(g[j]-g[j-w[i]]+10)%10;
		for(int j = 1; j <= m; ++j)
			write(g[j]);
		puts("");
	}
	return 0;
}
