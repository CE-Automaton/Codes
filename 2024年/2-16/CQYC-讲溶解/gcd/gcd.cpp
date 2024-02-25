#include <bits/stdc++.h>
#define orz 1
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e4+5, LG = 18;
int n, a[N], st[N][LG], ll[N][LG], rr[N][LG], totl[N], totr[N], ls[N][LG], rs[N][LG];
LL ans, aaa, sum[N]/*被gcd非1区间覆盖的个数*/;

template <typename T> inline void debug(T x) { cerr<<x; }
template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
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
int gcd(int x, int y) {
	if(x == y) return x;
	int aa = __builtin_ctz(x), bb = __builtin_ctz(y), cc;
	cc=min(aa, bb), y>>=bb;
	while(x) {
		x>>=aa;
		int d = abs(y-x);
		aa=__builtin_ctz(d);
		if(x < y) y=x;
		x=d;
	}
	return (y<<cc);
}
int ask(int l, int r) {
	int ln = log2(r-l+1);
	return (l == r ? a[l] : gcd(st[l][ln], st[r-(1<<ln)+1][ln]));
}

signed main() {
	File("gcd");
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]), st[i][0]=a[i];
	for(int j = 1; j <= 15; ++j)
		for(int i = 1; i+(1<<j)-1 <= n; ++i)
			st[i][j]=gcd(st[i][j-1], st[i+(1<<(j-1))][j-1]);
	for(int i = 1; i <= n; ++i)	{
		if(a[i] == 1) continue;
		ll[i][++totl[i]]=a[i];
		rr[i][++totr[i]]=a[i];
		int now = i;
		while(orz) {//求gcd
			int l = 1, r = now-1, to = 0;
			while(l <= r) {
				int mid = ((l+r)>>1), gd = ask(mid, i);
				if(gd != ll[i][totl[i]])
					to=mid, l=mid+1;
				else
					r=mid-1;
			}
			ls[i][totl[i]]=now-to;
			now=to;
			if(!to || ask(to, i) == 1) break;
			ll[i][++totl[i]]=ask(to, i);
		}
		++sum[now+1];
		sum[i+1]-=i-now+1;
		sum[i+2]+=i-now;
		ans+=(LL) i-now;
		// debug("LLL", i, '!', totl[i], ":\n");
		// for(int j = 1; j <= totl[i]; ++j)
		// 	debug(ll[i][j]), debug(' ');
		// debug('\n');
		for(int j = 1; j <= totl[i]; ++j)
			ls[i][j]+=ls[i][j-1]/*, debug(ls[i][j]), debug(' ')*/;
		// debug('\n');
		now = i;
		while(orz) {//求gcd
			int l = now+1, r = n, to = n+1;
			while(l <= r) {
				int mid = ((l+r)>>1), gd = ask(i, mid);
				if(gd != rr[i][totr[i]])
					to=mid, r=mid-1;
				else
					l=mid+1;
			}
			rs[i][totr[i]]=to-now;
			now=to;
			if(to == n+1 || ask(i, to) == 1) break;
			rr[i][++totr[i]]=ask(i, to);
		}
		// debug("RRR", i, '!', totr[i], ":\n");
		// for(int j = 1; j <= totr[i]; ++j)
		// 	debug(rr[i][j]), debug(' ');
		// debug('\n');
		for(int j = 1; j <= totr[i]; ++j)
			rs[i][j]+=rs[i][j-1]/*, debug(rs[i][j]), debug(' ')*/;
		// debug('\n');
	}
	// debug(ans, "!\n");
	for(int i = 1; i <= n; ++i)
		sum[i]+=sum[i-1];
	for(int i = 1; i <= n; ++i)
		sum[i]+=sum[i-1];
	// for(int i = 1; i <= n; ++i)
	// 	debug(sum[i], ' ');
	// debug('\n');
	for(int i = 1; i <= n; ++i) {
		LL now = max(ls[i-1][totl[i-1]], rs[i+1][totr[i+1]]);//直接填两边的最小gcd的情况
		if(i > 1 && i < n && a[i-1] != 1 && a[i+1] != 1) {
			LL ab = 1LL*ll[i-1][totl[i-1]]*rr[i+1][totr[i+1]]/gcd(ll[i-1][totl[i-1]], rr[i+1][totr[i+1]]);//两边最小gcd值的最小公倍数
			if(ab <= 500000)
				now=max(now, (LL) ls[i-1][totl[i-1]]+rs[i+1][totr[i+1]]);
			for(int o = totl[i-1]; o >= 1; --o)
				for(int p = totr[i+1]; p >= 1; --p)
					if(gcd(ll[i-1][o], rr[i+1][p]) != 1) {//填gcd把两边连起来
						int op = gcd(ll[i-1][o], rr[i+1][p]);
						// debug(i, o, p, op, '\n');
						LL haha = (LL) ls[i-1][o]+rs[i+1][p]+1LL*ls[i-1][o]*rs[i+1][p];
						//判断填成两边最小gcd值的倍数
						if(ab <= 500000 && 1LL*ab*op/gcd(ab, op) <= 500000) {
							haha+=(LL) ls[i-1][totl[i-1]]-ls[i-1][o]+rs[i+1][totr[i+1]]-rs[i+1][p];
							now=max(now, haha);
						}
						else {
							if(1LL*ll[i-1][totl[i-1]]*op/gcd(ll[i-1][totl[i-1]], op) <= 500000)
								now=max(now, haha+ls[i-1][totl[i-1]]-ls[i-1][o]);
							if(1LL*rr[i+1][totr[i+1]]*op/gcd(rr[i+1][totr[i+1]], op) <= 500000)
								now=max(now, haha+rs[i+1][totr[i+1]]-rs[i+1][p]);
						}
					}
		}
		// debug(i, now, "!?\n");
		aaa=max(aaa, now-sum[i]+1);
	}
	write(ans+aaa, '\n');
	return 0;
}
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症