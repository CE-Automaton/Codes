#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+5, M = 32;
unordered_map<long long, int> az[M][M];
unordered_map<__int128, int> azz[M<<1][M<<1];
int tskk, n, m, cnt, xx, yy, www, wss[N], ans;
long long xxx, yyy;

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
	freopen("walpurgis.in", "r", stdin);
	freopen("walpurgis.out", "w", stdout);
	read(tskk);
	if(tskk <= 5) {
		read(n), read(m);
		for(int i = 1; i <= n; ++i) {
			read(xx), read(yy), read(www);
			int a = 0, b = 0;
			while(1<<(a+1) <= xx) ++a;
			while(1<<(b+1) <= yy) ++b;
			xx = (xx&((1<<a)-1)), yy = (yy&((1<<b)-1));
			long long ooo = (long long) xx*1000000000+yy;
			if(az[a][b].find(ooo) == az[a][b].end())
				az[a][b][ooo]=++cnt;
			int to = az[a][b][ooo];
			wss[to]+=www;
		}
		for(int i = 1; i <= m; ++i) {
			read(xx), read(yy);
			ans=0;
			for(int a = 0; a <= 29 && (1<<a) <= xx; ++a) 
				for(int b = 0; b <= 29 && (1<<b) <= yy; ++b) {
					int x = (xx&((1<<a)-1)), y = (yy&((1<<b)-1));
					long long ooo = (long long) x*1000000000+y;
					if(az[a][b].find(ooo) != az[a][b].end())
						ans+=wss[az[a][b][ooo]];
				}
			write(ans, '\n');
		}
	} 
	else {
		read(n), read(m);
		for(int i = 1; i <= n; ++i) {
			read(xxx), read(yyy), read(www);
			int a = 0, b = 0;
			while(1LL<<(a+1) <= xxx) ++a;
			while(1LL<<(b+1) <= yyy) ++b;
			xxx = (xxx&((1LL<<a)-1)), yyy = (yyy&((1LL<<b)-1));
			__int128 ooo = (__int128) xxx*100000000000000000+yyy;
			if(azz[a][b].find(ooo) == azz[a][b].end())
				azz[a][b][ooo]=++cnt;
			int to = azz[a][b][ooo];
			wss[to]+=www;
		}
		for(int i = 1; i <= m; ++i) {
			read(xxx), read(yyy);
			ans=0;
			for(int a = 0; a <= 59 && (1LL<<a) <= xxx; ++a) 
				for(int b = 0; b <= 59 && (1LL<<b) <= yyy; ++b) {
					long long x = (xxx&((1LL<<a)-1)), y = (yyy&((1LL<<b)-1));
					__int128 ooo = (__int128) x*100000000000000000+y;
					if(azz[a][b].find(ooo) != azz[a][b].end())
						ans+=wss[azz[a][b][ooo]];
				}
			write(ans, '\n');
		} 
	}
	FastIO::flusher.~Flusher(); 
	return 0;
}
