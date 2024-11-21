#include <bits/stdc++.h>
#include <bits/extc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
using namespace __gnu_pbds;
typedef long long LL;
const int N = 4e5+5, base=1000003, mod = 998244353, modd = 1000000007;
int T, n, jc[N], inv[N], hs[N], hss[N], pw[N], pww[N], nwhs, nwhss, gs[N], cnt, sss, ans, tot;
LL zhan[N];
char s[N];
gp_hash_table <LL, int> vis, viss;

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
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
int updd(int x) {
	return (x >= modd ? x-modd : x);
}
void add(LL x) {
	if(vis.find(x) == vis.end())
		vis[x]=++cnt, gs[cnt]=0;
	x=vis[x];
	nwhs=upd(nwhs+pw[x]);
	nwhss=updd(nwhss+pww[x]);
	++gs[x];
	sss=1LL*sss*inv[gs[x]]%mod;
}
void dlt(LL x) {
	x=vis[x];
	nwhs=upd(nwhs-pw[x]+mod);
	nwhss=updd(nwhss-pww[x]+modd);
	sss=1LL*sss*gs[x]%mod;
	--gs[x];
}

signed main() {
	File("dog");
	jc[0]=jc[1]=inv[0]=inv[1]=pw[0]=pww[0]=1;
	pw[1]=pww[1]=base;
	for(int i = 2; i <= 200000; ++i)
		inv[i]=1LL*(mod-mod/i)*inv[mod%i]%mod, jc[i]=1LL*jc[i-1]*i%mod,
		pw[i]=1000003LL*pw[i-1]%mod, pww[i]=1000003LL*pww[i-1]%modd;
	read(T);
	while(T--) {
		scanf("%s", s+1);
		n=strlen(s+1);
		// debug(n, "???\n");
		ans=0;
		for(int i = 1; i <= n; ++i)
			hs[i]=upd(1000003LL*hs[i-1]%mod+s[i]-'a'+1),
			hss[i]=updd(1000003LL*hss[i-1]%modd+s[i]-'a'+1);
		for(int d = 1; d <= n; ++d) {
			// debug(d, "?????\n");
			vis.clear();
			sss=jc[n/d];
			cnt=0, nwhs=0, nwhss=0, tot=0;
			for(int i = n; i-d >= 0; i-=d) {
				zhan[++tot]=(LL) updd(hss[i]-1LL*hss[i-d]*pww[d]%modd+modd)*1000000000LL+upd(hs[i]-1LL*hs[i-d]*pw[d]%mod+mod);
				add(zhan[tot]);
			}
			ans=upd(ans+sss);
			if(n%d == 0) 
				continue;
			viss.clear();
			viss[(LL) 1000000000LL*nwhss+nwhs]=1;
			for(int i = 1, j = tot; i+d-1 <= n; i+=d, --j) {
				add((LL) updd(hss[i+d-1]-1LL*hss[i-1]*pww[d]%modd+modd)*1000000000LL+upd(hs[i+d-1]-1LL*hs[i-1]*pw[d]%mod+mod));
				dlt(zhan[j]);
				if(viss.find((LL) 1000000000LL*nwhss+nwhs) == viss.end())
					ans=upd(ans+sss), viss[(LL) 1000000000LL*nwhss+nwhs]=1;
			}
		}
		write(ans, '\n');
		// debug(clock(), '\n');
	}
	// debug(clock(), '\n');
	return 0;
}
//map怎么这么慢啊/ll