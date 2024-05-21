#include <bits/stdc++.h>
#define mod 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int ccc, t, n, ds[N], u, inv[N];
vector <int> to[N];

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

signed main() {
	File("chess");
	read(ccc), read(t);
	while(t--) {
		read(n);
		for(int i = 1; i <= n; ++i)
			to[i].clear(), ds[i]=0;
		for(int i = 2; i <= n; ++i)
			read(u), ++ds[i], ++ds[u], to[u].push_back(i);
		int rt = 0;
		for(int i = 1; i <= n; ++i)
			if(ds[i] == n-1) {
				rt=i;
				break;
			}
		if(rt) {
			// cout<<"...\n";
			if(rt == 1)
				write(n-1, '\n');
			else {
				int p = n-2, ans = n-1;
				inv[0]=inv[1]=1;
				for(int j = 2; j <= n-2; ++j)
					inv[j]=1LL*(mod-mod/j)*inv[mod%j]%mod, 
					p=1LL*p*(n-j-1)%mod*inv[j]%mod, ans=upd(ans+p);
				write(ans, '\n');
			}
			continue;
		}
	}
	return 0;
}