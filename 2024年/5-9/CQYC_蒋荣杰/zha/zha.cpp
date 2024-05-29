#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 21, base=131, mod=1e9+7;
int n, a[N], b[N], c[N], hs, ans;
unordered_map <int, int> pd;

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
void dfs(int x, int l, int r) {
	if(x == 2*n-1) {
		hs=0;
		for(int i = 1; i <= 2*n-2; ++i)
			hs=(1LL*hs*base%mod+c[i])%mod;
		if(pd.find(hs) == pd.end())
			++ans;
		pd[hs]=1;
		return ;
	}
	if(n-l+1 >= 2)
		c[x]=b[r], dfs(x+1, l+1, r), c[x]=0;
	if(n-r+1 >= 2)
		c[x]=a[l], dfs(x+1, l, r+1), c[x]=0;
}

signed main() {
	File("zha");
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	for(int i = 1; i <= n; ++i)
		read(b[i]);
	dfs(1, 1, 1);
	write(ans, '\n');
	return 0;
}