#include <bits/stdc++.h>
#define inf 1000000007
#define mod 2500000001LL
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e4+5;
int t, n, m, k, u, v, op[N], tot, zhan[1002], dis[1002][N];
unordered_map <LL, LL> inv;
LL gs[N<<1], ans;
struct qwq {
	int u, v;
};
queue <qwq> q[N<<1];

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
LL inn(LL x) {
	if(inv.find(x) != inv.end())
		return inv[x];//希望有点用啊啊啊啊啊
	return inv[x]=ksm(x, mod-2);
}

signed main() {
	read(t);
	while(t--) {
		ans=0; tot=0;
		read(n), read(m), read(k);
		for(int i = 0; i < n+m-1; ++i)
			gs[i]=0;
		for(int i = 1; i <= n; ++i)
			op[i]=0;
		for(int i = 1; i <= k; ++i)
			read(u), read(v), q[0].push(qwq {u, v}), op[u]=1;
		for(int i = 1; i <= n; ++i)
			if(op[i]) {
				zhan[++tot]=i, op[i]=tot;
				for(int j = 1; j <= m; ++j)
					dis[tot][j]=n+m-1;
			}
		for(int i = 0; i < n+m-1; ++i) 
			while(!q[i].empty()) {
				qwq it = q[i].front(); q[i].pop();
				if(dis[op[it.u]][it.v] < i) continue;
				dis[op[it.u]][it.v]=i;
				int x, y;
				if(it.v != 1) {
					x = it.u, y = it.v-1;
					if(dis[op[x]][y] > i+1)
						dis[op[x]][y]=i+1, q[i+1].push(qwq {x, y});
				}
				if(it.v != m) {
					x = it.u, y = it.v+1;
					if(dis[op[x]][y] > i+1)
						dis[op[x]][y]=i+1, q[i+1].push(qwq {x, y});
				}
				if(op[it.u]^1) {
					x = zhan[op[it.u]-1], y = it.v;
					if(i+it.u-x < dis[op[x]][y])
						dis[op[x]][y]=i+it.u-x, q[dis[op[x]][y]].push(qwq {x, y});
				}
				if(op[it.u]^tot) {
					x = zhan[op[it.u]+1], y = it.v;
					if(i+x-it.u < dis[op[x]][y])
						dis[op[x]][y]=i+x-it.u, q[dis[op[x]][y]].push(qwq {x, y});
				}
			}
		for(int j = 1; j <= m; ++j) 
			++gs[dis[1][j]+1], --gs[dis[1][j]+zhan[1]], 
			++gs[dis[tot][j]], --gs[dis[tot][j]+n-zhan[tot]+1];
		for(int i = 1; i <= tot-1; ++i)
			for(int j = 1; j <= m; ++j) 
				if(zhan[i+1]-zhan[i] != 1) {
					++gs[dis[i][j]], ++gs[dis[i+1][j]+1];
					int mid = (zhan[i+1]-zhan[i]+dis[i+1][j]+dis[i][j])/2;
					--gs[mid];
					--gs[mid+1];
					if(mid-dis[i][j]+mid-dis[i+1][j] == zhan[i+1]-zhan[i]-1)
						++gs[mid], --gs[mid+1];
				}
				else
					++gs[dis[i][j]], --gs[dis[i][j]+1];
		ans=1LL;
		LL now = 0;
		for(int i = 0; i < n+m-1; ++i)
			gs[i]+=(i ? gs[i-1] : 0), now+=gs[i], ans=ans*now%mod, --now;
		LL sum = 1;
		for(LL i = 1LL*n*m; i > now; --i)
			sum=sum*i%mod;
		write(ans*ksm(sum, mod-2)%mod, '\n');
	}
	FastIO::flusher.~Flusher();
	return 0;
}