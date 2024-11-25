#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2.5e7+5;
int t, m, n, a[N], b[N], tot, zhan[N];
LL sum[N], ll[N], rr[N];
bitset <(N<<1)> tong, pd;

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
LL abb(LL x) {
	return (x < 0 ? -x : x);
}

signed main() {
	File("road");
	read(t);
	while(t--) {
		read(m), read(n);
		for(int i = 1; i <= n; ++i)
			read(a[i]), tong[a[i]]=1;
		for(int i = 1; i <= n; ++i)
			read(b[i]), tong[b[i]]=1, pd[b[i]]=1;
		tot=0;
		sum[tot]=0;
		for(int i = tong._Find_first(); i <= m; i=tong._Find_next(i)) {
			zhan[++tot]=i, tong[i]=0, sum[tot]=0;
			if(tot == n+n) break;//必须提前break不然会TLE 
		}
		// for(int i = 1; i <= tot; ++i)
		// 	debug(zhan[i]), debug(' ');
		// debug('\n');
		int now = n;
		sum[n]=zhan[1]+m-zhan[tot];
		for(int i = 1; i < tot; ++i)
			now+=(pd[zhan[i]] ? -1 : 1)/*, debug(now, "!\n")*/, 
			sum[now]=sum[now]+(zhan[i+1]-zhan[i]);
		now=n;
		LL ans = 0, mn = 0;
		for(int i = 0; i <= n+n; ++i)
			ll[i]=(i == 0 ? 0 : ll[i-1])+sum[i], 
			ans=ans+1LL*abb(i-n)*sum[i];
		// debug(ans, '\n');
		mn=ans;
		rr[n+n+1]=0;
		for(int i = n+n; i >= 0; --i)
			rr[i]=rr[i+1]+sum[i];
		for(int i = 1; i <= tot; ++i) {
			if(!pd[zhan[i]])
				ans=ans-rr[now+1]+ll[now], ++now;
			else
				ans=ans-ll[now-1]+rr[now], --now;
			mn=min(mn, ans);
			// debug(ans, '\n');
		}
		write(mn, '\n');
		for(int i = 1; i <= n; ++i)
			tong[a[i]]=0, tong[b[i]]=0, pd[b[i]]=0;
	}
	// write(clock(), '\n');
	FastIO::flusher.~Flusher();
	return 0;
}
