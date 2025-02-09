#include <bits/stdc++.h>
#include <bits/extc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
using namespace __gnu_pbds;
typedef long long LL;
typedef unsigned long long ull;
const int N = 3.5e6+5, base = 31, mod = 1000000007, modd = 998244353, B = 3300000;
int n, k, hs[N], hss[N], pw[N], pww[N], now, noww, ans, ll;
LL a, b;
char s[N];
gp_hash_table <long long, int> gs[28], vis;

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
int ask(int x, LL y) {
	if(gs[x].find(y) == gs[x].end())
		return 0;
	return gs[x][y];
}
void sol() {
	int ad = 1;
	LL pp = 1000000000LL*now+noww;
	for(int i = 2; i <= 26; ++i)
		if(ask(i, pp) > ask(ad, pp))
			ad=i;
	++gs[ad][pp];
	s[++n]='a'+ad-1;
	now=upd(1LL*now*base%mod+ad);
	now=upd(now-1LL*(s[n-k]-'a'+1)*pw[k]%mod+mod);
	noww=updd(1LL*noww*base%modd+ad);
	noww=updd(noww-1LL*(s[n-k]-'a'+1)*pww[k]%modd+modd);
}

signed main() {
	File("string");
	read(n), read(k), read(a), read(b);
	scanf("%s", s+1);
	pw[0]=pww[0]=1;
	for(int i = 1; i <= 1100000; ++i)
		pw[i]=1LL*pw[i-1]*base%mod, pww[i]=1LL*pww[i-1]*base%modd;
	for(int i = 1; i <= n; ++i)
		hs[i]=upd(1LL*base*hs[i-1]%mod+s[i]-'a'+1), 
		hss[i]=updd(1LL*base*hss[i-1]%modd+s[i]-'a'+1);
	for(int i = k; i < n; ++i)
		++gs[s[i+1]-'a'+1][1000000000LL*upd(hs[i]-1LL*hs[i-k]*pw[k]%mod+mod)+updd(hss[i]-1LL*hss[i-k]*pww[k]%modd+modd)];
	now=upd(hs[n]-1LL*hs[n-k]*pw[k]%mod+mod);
	noww=updd(hss[n]-1LL*hss[n-k]*pww[k]%modd+modd);
	int nn = n;
	for(int i = nn+1; i <= B; ++i)
		sol();
	// exit(1);
	for(int i = nn+1; i <= B; ++i)
		hs[i]=upd(1LL*base*hs[i-1]%mod+s[i]-'a'+1), 
		hss[i]=updd(1LL*base*hss[i-1]%modd+s[i]-'a'+1);
	ans = 0, ll = B;
	for(int i = 1100000; i >= 1 && ans == 0; --i) {
		LL pp = 1000000000LL*upd(hs[B]-1LL*hs[B-i]*pw[i]%mod+mod)+updd(hss[B]-1LL*hss[B-i]*pww[i]%modd+modd);
		for(int j = B-i; j >= i; j-=i) {
			LL ppp = 1000000000LL*upd(hs[j]-1LL*hs[j-i]*pw[i]%mod+mod)+updd(hss[j]-1LL*hss[j-i]*pww[i]%modd+modd);
			if(ppp == pp) 
				ans=i, ll=j-i;
			else
				break;
		}
	}
	// for(int i = 1; i <= B; ++i)
	// 	putchar(s[i]);
	// debug(ans, ll, "???\n");
	if(a <= ll) {
		if(b <= ll) {
			for(int i = a; i <= b; ++i)
				putchar(s[i]);
			return 0;
		}
		for(int i = a; i <= ll; ++i)
			putchar(s[i]);
		a=ll+1;
	}
	a-=ll, b-=ll;
	for(LL i = a; i <= b; ++i) {
		LL j = i-(i-1)/ans*ans;
		putchar(s[j+ll]);
	}
	return 0;
}