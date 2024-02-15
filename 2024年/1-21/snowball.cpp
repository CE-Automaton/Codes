#include <bits/stdc++.h>
#define inf 100100007
#define mod 2500000001LL
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e4+5;
int t, n, m, k, op[N], opp[N], tot, zhan[1002], dis[1002][N];
unordered_map <LL, LL> inv;
LL gs[N<<1], ans;
struct qwq {
	int u, v;
}a[N];

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
struct FastMod
{
	using ull=unsigned long long;
	using L=__int128;
	ull b,m;
	FastMod(ull b):b(b),m(ull((L(1)<<64)/b)){}
	ull reduce(ull a)// return a mod b
	{
		ull q=(ull)((L(m)*a)>>64),r=a-q*b;
		return r>=b?r-b:r;
	}
}F(mod);
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
int comp(qwq A, qwq B) {
	return A.v < B.v;
}

signed main() {
	File("snowball");
	read(t);
	while(t--) {
		ans=0; tot=0;
		read(n), read(m), read(k);
		for(int i = 0; i < n+m-1; ++i)
			gs[i]=0;
		for(int i = 1; i <= n; ++i)
			op[i]=0;
		for(int i = 1; i <= m; ++i)
			opp[i]=0;
		int gsn = 0, gsm = 0;
		for(int i = 1; i <= k; ++i)
			read(a[i].u), read(a[i].v), op[a[i].u]=1;
		for(int i = 1; i <= n; ++i)
			if(op[i]) {
				zhan[++tot]=i, op[i]=tot;
				for(int j = 1; j <= m; ++j)
					dis[tot][j]=n+m-1;
			}
		sort(a+1, a+1+k, comp);
		for(int i = 1; i <= tot; ++i) {//题解的桶排方法常数巨大，所以只能这样直接枚
			int kk = 1, mn = inf;
			for(int j = 1; j <= m; ++j) {
				while(kk <= k && a[kk].v <= j)
					mn=min(mn, abs(a[kk].u-zhan[i])-a[kk].v), ++kk;
				dis[i][j]=min(dis[i][j], mn+j);
			}
			kk=k, mn=inf;
			for(int j = m; j >= 1; --j) {
				while(kk >= 1 && a[kk].v >= j)
					mn=min(mn, abs(a[kk].u-zhan[i])+a[kk].v), --kk;
				dis[i][j]=min(dis[i][j], mn-j);
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