#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5;
int n, a, aa[N], hh[N], zhan[N], tot, vis[N];
LL ans, ww[N];

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
void dfs(int x) {
	if(x == n+1) {
		int op = a;
		LL now = 0;
		for(int j = 1; j <= n; ++j) {
			int i = zhan[j];
			now+=1LL*((hh[i]+op-1)/op-1)*aa[i];
			op=max(op, aa[i]);
		}
		ans=min(ans, now);
		return ;
	}
	for(int i = 1; i <= n; ++i)
		if(!vis[i]) {
			vis[i]=1, zhan[x]=i;
			dfs(x+1);
			vis[i]=0;
		}
}
int comp(int A, int B) {
	return ww[A] > ww[B];
}

signed main() {
	File("xinyue");
	read(n), read(a);
	int pd = 1;
	for(int i = 1; i <= n; ++i)
		read(aa[i]), read(hh[i]);
	if(n <= 10) {
		ans=1000000000000000000LL;
		dfs(1);
		write(ans, '\n');
		return 0;
	}
	for(int i = 1; i < n; ++i)
		pd&=(aa[i] > aa[i+1] && hh[i] < hh[i+1]);
	if(pd) {
		// debug("sub A!\n");
		LL now = 0;
		for(int i = 1; i <= n; ++i) {
			now+=1LL*((hh[i]+a-1)/a-1)*aa[i];
			a=max(a, aa[i]);
		}
		write(now, '\n');
		return 0;
	}
	if(n <= 1000) {
		for(int i = 1; i <= n; ++i) {
			tot=0;
			for(int j = 1; j <= n; ++j)
				if(!vis[j]) {
					ww[j]=1LL*((hh[j]+a-1)/a-1)*aa[j];
					zhan[++tot]=j;
				}
			for(int o = 1, j = zhan[1]; o <= tot; ++o, j=zhan[o])
				for(int k = 1, p = zhan[1]; k <= tot; ++k, p=zhan[k])
					if(o != k)
						ww[j]+=1LL*((hh[k]+a-1)/a-1)*aa[k]-1LL*((hh[k]+max(a, aa[j])-1)/max(a, aa[j])-1)*aa[k];
			sort(zhan+1, zhan+1+tot, comp);
			int j = zhan[1];
			ans+=1LL*((hh[j]+a-1)/a-1)*aa[j];
			a=max(a, aa[j]);
		}
		write(ans, '\n');
		return 0;
	}
	return 0;
}