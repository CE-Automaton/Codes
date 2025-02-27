#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e3+5;
int n, m, l, r, a[N][N];

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
	File("det");
	read(n), read(m);
	for(int i = 1; i <= m; ++i) {
		read(l), read(r);
		++a[l][l], ++a[r+1][r+1], --a[l][r+1], --a[r+1][l];
	}
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			a[i][j]+=a[i-1][j]+a[i][j-1]-a[i-1][j-1];
	int ret = 1, w = 1;
	for(int i = 1; i <= n; ++i) 
		for(int j = i+1; j <= n; ++j) {
    		while(a[i][i]) {
     	    	int ss = a[j][i]/a[i][i];
        		for(int k = i; k <= n; ++k) 
        		    a[j][k]=upd(a[j][k]-1LL*ss*a[i][k]%mod+mod);
				for(int k = 1; k <= n; ++k)
        			swap(a[i][k], a[j][k]);
				w=-w;
    		}
    		for(int k = 1; k <= n; ++k)
        		swap(a[i][k], a[j][k]);
			w=-w;
		}
	for(int i = 1; i <= n; ++i)
		ret=1LL*a[i][i]*ret%mod;
	ret=upd(w*ret+mod);
	write(ret, '\n');
	return 0;
}
