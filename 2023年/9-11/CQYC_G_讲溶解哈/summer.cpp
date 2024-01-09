#include <bits/stdc++.h>
#define mod 4294967296LL
using namespace std;
const int N = 1e6+5;
int n, T, op, l, r, fa[N], zhan[N], tot, dep[N], vis[N], lstans;

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
	freopen("summer.in", "r", stdin);
	freopen("summer.out", "w", stdout);
	read(n), read(T);
	for(int i = 1; i <= n+1; ++i) 
		fa[i]=-1; 
	for(int i = 1; i <= n; ++i) {
		read(op), read(l), read(r);
		l^=(lstans*T);
		r^=(lstans*T);
		if(op == 1) 
			fa[l]=r;
		if(op == 2)
			fa[l]=fa[r], fa[r]=l;
		if(op == 3) {
			int pd = 1;
			for(int j = l; j <= r; ++j) 
				if(fa[j] != -1) {
					pd=0;
					int now = j;
					while(now) {
						++vis[now];
						zhan[++tot]=now;
						now=fa[now];
					}
					while(tot)
						dep[zhan[tot]]=dep[fa[zhan[tot]]]+1, --tot;
				}
			if(pd) {
				write(-1, '\n');
				lstans=0;
				continue;
			}
			else {
				int mx = 0, mmx=0;
				for(int j = 1; j <= n+1; ++j) 
					if(vis[j] > mx || (vis[j] == mx && (dep[j] > dep[mmx] || (dep[j] == dep[mmx] && j >= mmx))))
						mx=vis[j], mmx=j;
				write(mmx, '\n');
				lstans=mmx;
			}
			for(int j = l; j <= r; ++j) 
				if(fa[j] != -1) {
					int now = j;
					while(now) {
						--vis[now];
						now=fa[now];
					}
				}
		}
	}
	FastIO::flusher.~Flusher();
	return 0;
}
