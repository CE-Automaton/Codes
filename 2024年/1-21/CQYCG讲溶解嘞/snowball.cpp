#include <bits/stdc++.h>
#define inf 1000000007
#define mod 2500000001LL
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e4+5;
int t, n, m, k, u, v, fx[4][2]={{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
unordered_map <LL, LL> inv;
LL gs[N<<1], jc[1000005], ans;
vector <int> dis[N];
struct qwq {
	int u, v;
};
queue <qwq> q;

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
LL ksm(LL x, LL y, LL ret = 1LL) {
	while(y) {
		if(y&1) ret=ret*x%mod;
		x=x*x%mod;
		y=(y>>1);
	}
	return ret;
}
void sol(int x, int y) {
	if(x > y) swap(x, y);
	for(int i = x; i <= y; ++i)
		gs[i-1]+=1LL*x;
	for(int i = 1; i < x; ++i)
		gs[i-1]+=1LL*i, gs[x+y-1-i]+=1LL*i;
}
LL inn(LL x) {
	if(inv.find(x) != inv.end())
		return inv[x];//希望有点用啊啊啊啊啊
	return inv[x]=ksm(x, mod-2);
}

signed main() {
	File("snowball");
	jc[0]=1;
	for(int i = 1; i <= 1000000; ++i)
		jc[i]=1LL*jc[i-1]*i%mod;
	read(t);
	while(t--) {
		ans=0;
		read(n), read(m), read(k);
		for(int i = 0; i < n+m; ++i)
			gs[i]=0;
		if(k == 1) {
			read(u), read(v);
			int uu = n-u+1, vv = m-v+1;
			sol(u, v);
			sol(u, vv);
			sol(uu, v);
			sol(uu, vv);
			--gs[0];
			for(int i = 1; i <= m; ++i)
				--gs[abs(i-v)];
			for(int i = 1; i <= n; ++i)
				--gs[abs(i-u)];
			ans=1LL;
			LL now = 0;
			for(int i = 0; i < n+m-1; ++i)
				now+=gs[i], ans=ans*now%mod, --now;
			for(LL i = 1LL*n*m; i > now; --i)
				ans=ans*inn(i)%mod;
			write(ans, '\n');
			continue;
		}
		for(int i = 0; i < n; ++i) {
			dis[i].clear();
			for(int j = 0; j <= m; ++j)
				dis[i].push_back(inf);
		}
		for(int i = 1; i <= k; ++i)
			read(u), read(v), --u, --v, dis[u][v]=0, q.push(qwq {u, v});
		while(!q.empty()) {
			qwq it = q.front(); q.pop();
			for(int i = 0; i < 4; ++i) {
				int x = it.u+fx[i][0], y = it.v+fx[i][1];
				if(x < 0 || y < 0 || x >= n || y >= m) continue;
				if(dis[x][y] == inf)
					dis[x][y]=dis[it.u][it.v]+1, q.push(qwq {x, y});
			}
		}
		for(int i = 0; i < n; ++i) 
			for(int j = 0; j < m; ++j)
				++gs[dis[i][j]];
		ans=1;
		LL now = 0;
		for(int i = 0; i < n+m; ++i)
			now+=gs[i], ans=ans*now%mod, --now;
		ans=ans*jc[now]%mod;
		ans=ans*ksm(jc[n*m], mod-2)%mod;
		write(ans, '\n');
	}
	FastIO::flusher.~Flusher();
	return 0;
}