#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e5+6;
int n, k, a[N], tot, cnt[N], fa[N], ans;
map <int, int> vis;

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
int find(int x) {
	return (x == fa[x] ? x : fa[x]=find(fa[x]));
}
void merge(int x, int y) {
	x=find(x), y=find(y);
	if(x == y) return ;
	ans-=(cnt[x]+1)/2;
	ans-=(cnt[y]+1)/2;
	if(cnt[x] > cnt[y]) swap(x, y);
	fa[x]=y, cnt[y]+=cnt[x];
	ans+=(cnt[y]+1)/2;
}

signed main() {
	File("checkln");
	read(n), read(k);
	for(int i = 1; i <= n; ++i)
		fa[i]=i, cnt[i]=1;
	for(int i = 1; i <= n; ++i) {
		read(a[i]);
		++ans;
		if(vis.find(a[i]-k) != vis.end()) 
			merge(vis[a[i]-k], i);
		if(vis.find(a[i]+k) != vis.end())
			merge(vis[a[i]+k], i);
		vis[a[i]]=i;
		write(ans, ' ');
	}
	FastIO::flusher.~Flusher();
	// debug(clock());
	return 0;
}