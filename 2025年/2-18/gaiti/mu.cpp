#include <bits/stdc++.h>
#include <bits/extc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
using namespace __gnu_pbds;
typedef long long LL;
const int N = 1e5+5;
int nn, B, mul[N], vis[N], pri[N], cnt;
LL n, k, ans, x, y;
gp_hash_table <LL, int> mull;

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
LL exgcd(LL u, LL v, LL& xx, LL& yy) {
	LL ret = 0;
	if(u%v == 0) xx=0, yy=1, ret=v;
	else ret=exgcd(v, u%v, yy, xx), yy-=u/v*xx;
	return ret;
}
LL solve(LL d2, LL e2) {
	LL gc = exgcd(d2, e2, x, y);
	// debug(gc, k, x, y, "?????\n");
	if(k%gc != 0) return 0;
	__int128 xx = (__int128) k/gc*x, yy = (__int128) k/gc*y;
	LL aa = e2/gc, bb = d2/gc;
	if(yy > 0)
		xx+=(__int128) (yy-1)/bb*aa, yy-=(__int128) (yy-1)/bb*bb;
	if(xx >= 0)
		yy+=(__int128) (xx/aa+1)*bb, xx-=(__int128) (xx/aa+1)*aa;
	// debug(d2, e2, x, y, (y <= n/e2 ? (n/e2-y)/bb+1 : 0), "???\n");
	return (yy <= n/e2 ? (n/e2-yy)/bb+1 : 0);
}

signed main() {
	File("mu");
	read(n), read(k);
	nn=(LL) sqrtl((long double) n);
	mul[1]=1;
	for(int i = 2; i <= nn; ++i) {
		if(!vis[i])
			mul[i]=-1, pri[++cnt]=i;
		for(int j = 1; j <= cnt && pri[j] <= nn/i; ++j) {
			vis[i*pri[j]]=1;
			if(i%pri[j] == 0) break;
			mul[i*pri[j]]=-mul[i];
		}
	}
	B=min(nn, 360);
	// debug(B, "?\n");
	for(int i = 1; i <= B; ++i)
		for(int j = 1; j <= nn; ++j)
			if(mul[i] && mul[j])
				ans+=1LL*mul[i]*mul[j]*solve(1LL*i*i, 1LL*j*j);
	for(int i = B+1; i <= nn; ++i)
		for(int j = 1; j <= B; ++j)
			if(mul[i] && mul[j])
				ans+=1LL*mul[i]*mul[j]*solve(1LL*i*i, 1LL*j*j);
	// debug(ans, "???\n");
	for(int i = B+1; i <= nn; ++i)
		if(mul[i])
			for(LL j = 1LL*i*i; j <= n; j+=1LL*i*i)
				mull[j]+=mul[i];
	for(int i = B+1; i <= nn; ++i)
		if(mul[i])
			for(LL j = 1LL*i*i+k; j <= n; j+=1LL*i*i)
				if(mull.find(j) != mull.end())
					ans+=1LL*mul[i]*mull[j];
	write(ans, '\n');
	return 0;
}
