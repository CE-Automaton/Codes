#include <bits/stdc++.h>
using namespace std;
const int N = 1e3+5;
int t, n, tot;
long long ans;
char a[N], b[N], c[N], d[N];

template <typename T> void read(T& x) {
	x = 0; int f = 0; char chh = getchar();
	while(chh < '0' || chh > '9') f |= (chh == '-'), chh=getchar();
	while(chh >= '0' && chh <= '9') x=(x<<1)+(x<<3)+(chh^48), chh=getchar();
	x=(f ? -x : x);
}
int lne; char put[105];
template <typename T> void write(T x, char ch) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
	putchar(ch);
}
void check() {
	for(int i = 1; i*2 <= tot; ++i)
		if(d[i] != d[tot-i+1])
			return ;
	++ans;
}

signed main() {
	freopen("pali.in", "r", stdin);
	freopen("pali.out", "w", stdout);
	read(t);
	while(t--) {
		scanf("%s\n%s\n%s", a+1, b+1, c+1);
		n=strlen(a+1);
		tot=0;
		ans=0;
		for(int i = 1; i <= n; ++i)
			for(int j = i; j <= n; ++j) {
				tot=0;
				for(int k = i; k <= j; ++k)
					d[++tot]=a[k];
				int op = tot;
				for(int ii = 1; ii <= n; ++ii)
					for(int jj = ii; jj <= n; ++jj) {
						tot=op;
						for(int k = ii; k <= jj; ++k)
							d[++tot]=b[k];
						int opp = tot;
						for(int iii = 1; iii <= n; ++iii)
							for(int jjj = iii; jjj <= n; ++jjj) {
								tot=opp;
								for(int k = iii; k <= jjj; ++k)
									d[++tot]=c[k];
								check();
							}
					}
			}
		write(ans, '\n'); 
	}
	return 0;
}
