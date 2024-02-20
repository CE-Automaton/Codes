#include <bits/stdc++.h>
#define mod 998244353
#define inv2 499122177
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e5+5;
int n, m, cnt, t, as, jc[N], inv[N], inc[N];
char s[N], tt;

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
int c(int x, int y) {
	return (y < 0 || x < y ? 0 : 1LL*jc[x]*inc[x-y]%mod*inc[y]%mod);
}
int upd(int x) {
	return (x < 0 ? x+mod : (x >= mod ? x-mod : x));
}
struct fxy {
	int x, y, sum;
	void add_x(int pd) {
		sum=upd(sum+(pd ? mod-c(y, x) : c(y, x+1)));
		x=(pd ? x-1 : x+1);
	}
	void add_y(int pd) {
		if(!pd && y == -1) 
			sum=(pd ? 0 : (x >= 0));//!!!!!!
		else
			sum=(pd ? 1LL*upd(sum+c(y-1, x))*inv2%mod : upd(upd(sum+sum)+mod-c(y, x)));
		y=(pd ? y-1 : y+1);
	}
}A/*f t cnt*/, B/*f t-1 cnt-1*/, C/*f cnt cnt*/, D/*f cnt-1 cnt-1*/;
int ksm(int x, int y, int ret = 1) {
	while(y) {
		if(y&1) ret=1LL*ret*x%mod;
		x=1LL*x*x%mod;
		y=(y>>1);
	}
	return ret;
}
int getans() {
	if(cnt == 1) {//啊啊啊死卡在了这里结果直接特判就行
		int ret = 0;
		for(int i = 0; i <= cnt; ++i)
			if(!((i+t)&1)) 
				ret=upd(ret+1LL*abs(i-t)*c(cnt, i)%mod);
		ret=1LL*ret*inv2%mod;
		return ret;
	}
	return 1LL*ksm(inv2, cnt, upd(upd(upd(1LL*upd(t+t)*A.sum%mod-1LL*upd(cnt+cnt)*B.sum%mod)-1LL*t*C.sum%mod)+1LL*cnt*D.sum%mod));
}
void sol(int i, int pd) {
	if(s[i] == 'b')
		A.add_x((i&1)^pd), B.add_x((i&1)^pd), t-=(pd ? -1 : 1)*(i&1 ? 1 : -1);
	if(s[i] == '?') {
		A.add_y(pd), B.add_y(pd), C.add_y(pd), C.add_x(pd), D.add_y(pd), D.add_x(pd), cnt+=(pd ? -1 : 1);
		if((i&1)^1)
			A.add_x(pd), B.add_x(pd), t+=(pd ? -1 : 1);
	}
}

signed main() {
	read(n), read(m);
	scanf("%s", s+1);
	jc[0]=jc[1]=inv[0]=inv[1]=inc[0]=inc[1]=1;
	for(int i = 2; i <= n; ++i)
		inv[i]=1LL*inv[mod%i]*(mod-mod/i)%mod, 
		jc[i]=1LL*jc[i-1]*i%mod, inc[i]=1LL*inc[i-1]*inv[i]%mod;
	A.y=-1;C.y=-1;B.x=-1;B.y=-2;D.x=-1;D.y=-2;
	for(int i = 1; i <= n; ++i) 
		sol(i, 0);
	// debug(t, cnt, A.sum, B.sum, C.sum, D.sum, upd(upd(upd(1LL*upd(t+t)*A.sum%mod-1LL*upd(cnt+cnt)*B.sum%mod)-1LL*t*C.sum%mod)+1LL*cnt*D.sum%mod), "!?\n");
	write(getans(), '\n');
	for(int i = 1; i <= m; ++i) {
		read(as), scanf(" %c", &tt);
		sol(as, 1);
		s[as]=tt;
		sol(as, 0);
		write(getans(), '\n');
	}
	return 0;
}