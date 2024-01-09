#include <bits/stdc++.h>
#define inf 1000000007
#define mod 1000000009
#define inv2 (mod-mod/2)
using namespace std;
const int N = 2e3+5, M = 3e4+5;
int n, m, s, t, u, v, w, dis[N], f[N][N], pdd[N][N], g[N], pd[N], in[N], oo[N], rk[N], cnt;
struct qwq {
	int y, w;
	bool operator <(const qwq& A) const {
		return A.w < w;
	};
};
vector <qwq> to[N];
vector <int> tt[N];
priority_queue <qwq> q;
queue <int> p;

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
void topuu() {
	p.push(s);
	while(!p.empty()) {
		int it = p.front(); p.pop(); rk[it]=++cnt, oo[cnt]=it;
		for(int y : tt[it])  if(!(--in[y])) p.push(y);
	}
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}

signed main() {
	read(n), read(m), read(s), read(t);
	for(int i = 1; i <= m; ++i)
		read(u), read(v), read(w), 
		to[u].push_back(qwq {v, w});
	for(int i = 1; i <= n; ++i)
		dis[i]=inf;
	dis[s]=0;
	q.push(qwq {s, 0});
	while(!q.empty()) {
		qwq it = q.top(); q.pop();
		if(it.w > dis[it.y]) continue;
		for(qwq y : to[it.y])
			if(it.w+y.w < dis[y.y]) {
				dis[y.y]=it.w+y.w;
				q.push(qwq {y.y, dis[y.y]});
			}
	}
	for(int i = 1; i <= n; ++i)
		for(qwq j : to[i])
			if(dis[i]+j.w == dis[j.y] && !pdd[i][j.y]/*要求了路径不同表示点集不同!*/)
				tt[i].push_back(j.y), pdd[i][j.y]=1, ++in[j.y];
	topuu();
	for(int j : tt[s])
		pd[rk[j]]=1;
	for(int i = 1; i <= cnt; ++i) {
		f[i][i]=1; 
		for(int j = i; j <= cnt; ++j)
			if(f[i][j])
				for(int k : tt[oo[j]])
					f[i][rk[k]]=upd(f[i][rk[k]]+f[i][j]);
		g[i]=1LL*(f[1][i]-1)*f[1][i]/2%mod;
		for(int j = 2; j <= i-1; ++j)
			if(f[j][i])
				g[i]=upd(upd(g[i]-1LL*g[j]*f[j][i]%mod*f[j][i]%mod+mod)-(pd[j] ? 1LL*(f[j][i]-1)*(f[j][i])/2%mod : 0)+mod);
	}
	write(upd(g[rk[t]]+pd[rk[t]]), '\n');
	FastIO::flusher.~Flusher(); 
	return 0 ;
}
