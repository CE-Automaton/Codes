#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int base = 131, mod = 1000000007;
const int N = (1<<20)+5;
int n, u, v, bs[N], pd[N];
vector <int> to[N];

struct BIT {
	int tr[N];
	void add(int x, int w) {
		while(x <= n)
			tr[x]=(tr[x]+w)%mod, x+=(x&(-x));
	}
	int ask(int x, int ret = 0) {
		while(x >= 1)
			ret=(ret+tr[x])%mod, x-=(x&(-x));
		return ret;
	}
}A, B;
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
void ssss(int x, int fa) {
	pd[x]=1;
	for(int y : to[x])
		if(y != fa)
			ssss(y, x);
}
void dfs(int x, int fa) {
	int len = min(x, n-x+1);
	A.add(x, bs[x]);
	B.add(x, bs[n-x+1]);
	for(int y : to[x]) 
		if(y != fa) {
			int ll = (B.ask(x-1)-B.ask(x-len)+mod)%mod, 
			rr = (A.ask(x+len-1)-A.ask(x)+mod)%mod;
			dfs(y, x);
			int lll = (B.ask(x-1)-B.ask(x-len)+mod)%mod, 
			rrr = (A.ask(x+len-1)-A.ask(x)+mod)%mod;
			lll=(lll-ll+mod)%mod;
			rrr=(rrr-rr+mod)%mod;
			if(1LL*lll*bs[x-1]%mod != 1LL*rrr*bs[n-x]%mod) {
				// debug(x, len, "???\n");
				putchar('Y'), putchar('E'), putchar('S'), putchar(' ');
				ssss(y, x);
				for(int i = 1; i < len; ++i)
					if(pd[x-i]^pd[x+i]) {
						write(x-i, ' '), write(x, ' '), write(x+i, '\n');
						break;
					}
				exit(0);
			}
		}
}

signed main() {
	read(n);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	bs[0]=1;
	for(int i = 1; i <= n; ++i)
		bs[i]=1LL*bs[i-1]*base%mod;
	dfs(1, 0);
	puts("NO");
	return 0;
}