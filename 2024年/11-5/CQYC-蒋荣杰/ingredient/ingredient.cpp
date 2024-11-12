#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int M = (1<<21)+5;
int n, a[M], gs[M];
LL sum[M], f[M][25], ans, c[25][25];

template <typename T> inline void debug(T x) { cerr<<x; }
template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
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

signed main() {
	File("ingredient");
	read(n);
	for(int i = 0; i < (1<<n); ++i) 
		read(a[i]), sum[((1<<n)-1)^i]=a[i];
	for(int j = 0; j < n; ++j)
		for(int i = 0; i < (1<<n); ++i)
			if((i>>j)&1)
				sum[i]+=sum[i^(1<<j)];
	for(int i = 0; i < (1<<n); ++i) {
		gs[i]=0;
		for(int j = 0; j < n; ++j)
			gs[i]+=((i>>j)&1);
		f[i][gs[i]]=sum[((1<<n)-1)^i];
	}
	for(int j = 0; j < n; ++j)
		for(int i = 0; i < (1<<n); ++i) 
			if((i>>j)&1)
				for(int k = 0; k < gs[i]; ++k)
					f[i][k]+=f[i^(1<<j)][k];
	for(int i = 0; i <= n; ++i) {
		c[i][0]=1;
		for(int j = 1; j <= i; ++j)
			c[i][j]=c[i-1][j-1]+c[i-1][j];
	}
	for(int i = 0; i < (1<<n); ++i) {
		for(int j = gs[i]; j >= 0; --j) {
			LL su = 0;
			for(int k = j+1; k <= gs[i]; ++k)
				su+=f[i][k]*c[k][j];
			f[i][j]-=su;
		}
		for(int j = 0; j <= n; ++j)
			ans^=1LL*(f[i][j]+i)*(j+1);
	}
	write(ans, '\n');
	// write(clock(), '\n');
	FastIO::flusher.~Flusher();
	return 0;
}