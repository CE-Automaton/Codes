#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+5;
int n, a[N], u, cnt, hd[N], nxt[N<<1], to[N<<1], pd[N<<1], sz[N];
long long sum;

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
void edge(int x, int y) {
	nxt[++cnt]=hd[x];
	to[cnt]=y;
	pd[cnt]=0;
	hd[x]=cnt;
//	cout<<cnt<<" "<<x<<"->"<<y<<"\n";
}
void gett(int x, int fa) {
	sz[x]=a[x];
	for(int i = hd[x]; i; i=nxt[i])
		if(pd[i] == 1) {
			gett(to[i], x);
			sz[x]+=sz[to[i]];
		}
}
void dfs(int x) {
	if(x > cnt) {
		long long ans = 0;
		for(int i = 1; i <= n; ++i) 
			sz[i]=0;
		for(int i = 1; i <= n; ++i) {
			if(sz[i] == 0)
				gett(i, i);
			ans+=1LL*a[i]*(sz[i]-a[i])+1LL*(a[i]-1)*a[i]/2;
		}
		sum=max(sum, ans);
		return ;
	}
	pd[x]=1;
	pd[x+1]=0;
	dfs(x+2);
	pd[x]=0;
	pd[x+1]=1;
	dfs(x+2);
}

signed main() {
	freopen("winter.in", "r", stdin);
	freopen("winter.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	cnt=1;
	for(int i = 2; i <= n; ++i)
		read(u), edge(i, u), edge(u, i);
	dfs(2);
	write(sum, '\n');
	FastIO::flusher.~Flusher(); 
	return 0;
}
