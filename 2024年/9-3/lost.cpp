#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
#define inf 1000000007
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int n, k, d[N], zhan[N], tot, vis[N], huan[N], cnt, ans, gs[N], mdep[N], pd[N], rt;
vector <int> to[N];

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
int dfs(int x, int fa, int dep) {
	mdep[x]=dep;
	int ret = 0;
	vis[x]=1;
	for(int y : to[x]) 
		if(y != 1)
			ret+=dfs(y, x, dep+1), mdep[x]=max(mdep[x], mdep[y]);
	if(mdep[x]-dep >= k-1 && fa != 1) 
		++ret, mdep[x]=dep-1;
	return ret;
}

signed main() {
	read(n), read(k);
	for(int i = 1; i <= n; ++i)
		read(d[i]);
	if(k == 1) {
		for(int i = 1; i <= n; ++i)
			ans+=(d[i] != 1);
		write(ans, '\n');
		FastIO::flusher.~Flusher();
		return 0;
	}
	ans=(d[1] != 1);
	for(int i = 2; i <= n; ++i)
		to[d[i]].push_back(i);
	for(int y : to[1])
		ans+=dfs(y, 1, 1);
	write(ans, '\n');
	FastIO::flusher.~Flusher();
	return 0;
}