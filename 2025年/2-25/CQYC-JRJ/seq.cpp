#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2.1e3+5;
int n, m, q, u, v, s[N][N], ss[N][N], zhan[N][N], cnt[N];

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
	File("seq");
	read(n), read(m), read(q);
	ss[0][0]=1;
	zhan[0][cnt[0]=1]=0;
	int rr = 1;
	while(rr < m) rr<<=1;
	for(int i = 1; i <= n; ++i) {
		read(u), read(v);
		for(int j = u; j; j-=(j&(-j)))
			for(int k = j-(j&(-j)); k < j; ++k)
				s[i][k]=1LL*j*(j^v)%mod;
		for(int j = 0; j < m; ++j)
			if(s[i][j])
				for(int k = 1; k <= cnt[i-1]; ++k)
					ss[i][j^zhan[i-1][k]]=upd(ss[i][j^zhan[i-1][k]]+1LL*ss[i-1][zhan[i-1][k]]*s[i][j]%mod);
		for(int j = 0; j < rr; ++j)
			if(ss[i][j])
				zhan[i][++cnt[i]]=j;
	}
	for(int i = 1; i <= q; ++i) 
		read(u), read(v), write(ss[u][v], '\n');
	return 0;
}
