#include <bits/stdc++.h>
using namespace std;
int n, q, a[100005], b[100005], c, d, e, f, g[100005];
template<typename T>
inline void read(T& x) {
	x=0; char c = getchar(); while(c < '0' || c > '9') c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
}
int main() {
	freopen("similar.in", "r", stdin);
	freopen("similar.out", "w", stdout);
	read(n), read(q);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	for(int i = 1; i <= q; ++i) {
		read(c), read(d), read(e), read(f);
		for(int j = c; j <= d; ++j)
			b[j]=a[j];
		for(int j = e; j <= f; ++j)
			g[j]=a[j];
		sort(b+c, b+1+d);
		sort(g+e, g+1+f);
		int o = 0;
		for(int j = 1; j <= d-c+1; ++j)
			if(b[j+c-1] != g[j+e-1])
				++o;
		if(o >= 2) 
			puts("NO");
		else
			puts("YES");
	}
	return 0;
}
