#include <bits/stdc++.h>
using namespace std;
const int N = 505;
int t, n, m, a[N][N], ans[N][N], h[N], hh[N][N], l[N], ll[N][N], k;

namespace FastIO {
	const int SIZE=(1<<21)+1;
	char ibuf[SIZE],obuf[SIZE],*iS,*iT,*oS=obuf,*oT=obuf;
	char* flush(){fwrite(obuf,1,oT-oS,stdout);return oT=obuf;}
	struct Flusher{~Flusher(){flush();}}flusher;
	inline char gc(){return iS==iT && (iT=(iS=ibuf)+fread(ibuf,1,SIZE,stdin),iS==iT)?EOF:*iS++;}
	inline void pc(char c){if(oT==oS+SIZE) flush();*oT++=c;}
	#define getchar gc
	#define putchar pc
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
}
using FastIO::gc;
using FastIO::pc;
using FastIO::read;
using FastIO::write;
int dfs(int x, int y) {
	if(x > n) 
		return 1;
	if(a[x][y] == 1) {
		ans[x][y]=0;
		if(dfs(x+(y == m ? 1 : 0), y%m+1))
			return 1;
		else
			return 0;
	}
	else
		for(int i = 1; i <= k; ++i)
			if(hh[x][i] == 0 && ll[y][i] == 0) {
				hh[x][i]=1;
				ll[y][i]=1;
				ans[x][y]=i;
				if(dfs(x+(y == m ? 1 : 0), y%m+1) == 1)
					return 1;
				hh[x][i]=0;
				ll[y][i]=0;
			}
	return 0;
}

signed main() {
	freopen("heart.in", "r", stdin);
	freopen("heart.out", "w", stdout);
	read(t);
	while(t--) {
		read(n), read(m);
		for(int i = 1; i <= n; ++i) {
			h[i]=0;
			for(int j = 1; j <= max(n, m); ++j)
				hh[i][j]=0;
		}
		for(int i = 1; i <= m; ++i) {
			l[i]=0;
			for(int j = 1; j <= max(n, m); ++j)
				ll[i][j]=0;
		}
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j) 
				read(a[i][j]), h[i]+=(a[i][j]^1), l[j]+=(a[i][j]^1),
				ans[i][j]=-1;
		k = 0;
		for(int i = 1; i <= n; ++i)
			k=max(k, h[i]);
		for(int j = 1; j <= m; ++j)
			k=max(k, l[j]);
		write(k, '\n');
		if(dfs(1, 1)) {
			for(int i = 1; i <= n; ++i) {
				for(int j = 1; j <= m; ++j)
					write(ans[i][j], ' ');
				pc('\n');
			}
		}
	}
	FastIO::flusher.~Flusher();
	return 0;
}
