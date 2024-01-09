#include <bits/stdc++.h>
#define mod 4294967296LL
using namespace std;
const int N = 1e6+5;
int t, n, m, p, c[10][10], zhan[55], vis[55][55], dp[N<<1], ans;

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
int upd(int x) {
	return (x >= p ? x-p : x);
}

signed main() {
	freopen("cumulonimbus.in", "r", stdin);
	freopen("cumulonimbus.out", "w", stdout);
	read(t);
	while(t--) {
		read(n), read(m), read(p);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				read(c[i][j]);
		for(int i = 0; i < n*m; ++i)
			for(int j = 0; j < n*m; ++j)
				vis[i][j]=0;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				for(int k = 0; k < m; ++k)
					vis[i*m+j][i*m+k]=1;
		for(int i = 0; i < m; ++i)
			for(int j = 0; j < n; ++j)
				for(int k = 0; k < n; ++k)
					vis[i+j*m][i+k*m]=1;
		ans=0;
		for(int i = 0; i < (1<<(n*m))-1; ++i) {
			int gs = 0, cc = 1;
			for(int j = 0; j < n*m; ++j)
				if((i>>j)&1)
					++gs, zhan[gs]=j, cc=1LL*cc*upd(1+p-c[j/m][j%m])%p;
				else
					cc=1LL*cc*c[j/m][j%m]%p;
			dp[i]=gs;
			for(int j = 1; j <= gs; ++j)
				for(int k = j+1; k <= gs; ++k)
					if(vis[zhan[j]][zhan[k]])
						dp[i]=min(dp[i], dp[(i^(1<<zhan[j]))^(1<<zhan[k])]);
//			write(i, ' ');
//			write(dp[i], '\n');
			ans=upd(ans+1LL*dp[i]*cc%p);
		}
		write(ans, '\n');
	}
	FastIO::flusher.~Flusher();
	return 0;
}
