#include <bits/stdc++.h>
#define mod 11417603
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5;
int n, m, tot, ans, jc[N], inv[N], inc[N];
char s[N];
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
struct addd {
	int x, w;
}zhan[N];
struct qwq {
	int f[N<<1], t[N<<1], st, t0, v0, va, s1, s2, tt, fgm/*大于m的*/;
	void csh() {
		st=100000;
		v0=va=s1=s2=fgm=0;
		t0=tt=1;
	}
	void gens(int x) { if(t[x] < t0) f[x]=v0, t[x]=t0; }
	void updt(int x, int v) {//单点修改
		++tt;
		gens(st+x); f[st+x]=upd(f[st+x]+v), t[st+x]=tt;
		s1=upd(s1+v), s2=upd(s2+upd(1LL*(x-1)*v%mod+mod));
	}
	int ask(int x) {//单点查值
		gens(st+x);
		return upd(f[st+x]+va);
	}
	void add_all(int v) {//全局修改
		++tt;
		va=upd(va+v), s1=upd(s1+1LL*(m+1)*v%mod), s2=upd(s2+1LL*(m-2)*(m+1)/2%mod*v%mod);
	}
	int all_s2() {//求s2
		return upd(s2+ask(0));
	}
	void shift() {//右移1位
		s1=upd(s1-ask(m)+mod);
		s2=upd(s2-1LL*ask(m)*(m-1)%mod+mod);
		fgm=upd(fgm+ask(m));
		--st;
		++tt;
		s2=upd(s2+s1);
		f[st]=upd(mod-va);
		t[st]=tt;
	}
	void clear() {//清零
		++tt;
		t0=tt;
		s1=s2=0;
		v0=upd(mod-va);
	}
}dp;

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
int C(int x, int y) {
	return 1LL*jc[x]*inc[x-y]%mod*inc[y]%mod;
}

signed main() {
	read(n), read(m);
	jc[0]=jc[1]=inc[0]=inc[1]=inv[0]=inv[1]=1;
	for(int i = 2; i <= m+1; ++i)
		inv[i]=1LL*(mod-mod/i)*inv[mod%i]%mod, 
		jc[i]=1LL*jc[i-1]*i%mod, inc[i]=1LL*inc[i-1]*inv[i]%mod;
	scanf("%s", s+1);
	dp.csh();
	for(int i = 1; i <= m; ++i)
		dp.updt(i, 1);
	int pw = m;
	for(int i = 1; i <= n-2; ++i) {
		pw=1LL*pw*m%mod;
		int add = dp.ask(1);
		tot=0;
		if(s[i] == 'A') {
			zhan[++tot]=addd {0, upd(upd(dp.all_s2()+1LL*dp.fgm*m%mod)+mod)};
			zhan[++tot]=addd {1, (int) (1LL*dp.ask(0)*m%mod)};
			LL jc = 1;
			for(int i = 2; i <= m; ++i) {
				jc=1LL*jc*i;
				if(jc > m) break;
				LL op = jc;
				for(int j = i; op <= m; ++j)
					zhan[++tot]=addd {(int) op, dp.ask(i)}, op=op/(j-i+1)*(j+1);
			}
			dp.clear();
		}
		else {
			zhan[++tot]=addd {0, upd(upd(dp.all_s2()+1LL*dp.fgm*m%mod)+mod)};
			zhan[++tot]=addd {1, upd(upd(dp.s1+(1LL*dp.ask(0)*(m-2)%mod))-dp.ask(1)+mod)};
			zhan[++tot]=addd {2, upd(mod-dp.ask(1))};
			for(int i = 2; i <= m; ++i) {
				LL op = 1LL*(i+2)*(i+1)/2;
				if(op > m) break;
				for(int j = 3; op <= m; ++j)
					zhan[++tot]=addd {(int) op, dp.ask(i)}, op=op*(i+j)/j;
			}
			dp.shift();
		}
		dp.add_all(add);
		dp.updt(0, upd(mod-add));
		while(tot)
			dp.updt(zhan[tot].x, zhan[tot].w), --tot;
		dp.fgm=upd(pw-dp.s1+mod);
	}
	ans=upd(1LL*m*dp.ask(0)%mod+1LL*C(m+1, 2)*dp.ask(1)%mod);
	if(s[n-1] == 'A') 
		for(int i = 2; i <= m; ++i)
			ans=upd(ans+1LL*dp.ask(i)*C(m+1, i+1)%mod*jc[i]%mod);
	else
		for(int i = 2; i <= m; ++i)
			ans=upd(ans+1LL*dp.ask(i)*C(m+1, i+1)%mod);
	write(ans, '\n');
	return 0;
}