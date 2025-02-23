#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
int n, m, A, B, u, v, ad[4005][2], dl[4005][2], f[2][(1<<20)+5], ans, nb[205][205], vis[4005];

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
void add(int &x, int y) {
	x+=y, x=(x >= mod ? x-mod : x);
}

signed main() {
	File("education");
	read(n), read(m), read(A), read(B);
	for(int i = 1; i <= m; ++i) {
		read(u), read(v);
		if(u > v) swap(u, v);
		if(v-u == A)
			ad[u][0]=1, dl[v][0]=1;
		else
			ad[u][1]=1, dl[v][1]=1;
	}
	if(B <= 20) {
		// debug("!!!???\n");
		int now = 0;
		f[0][0]=1;
		for(int i = 1; i <= n; ++i) {
			now^=1;
			for(int j = 0; j < (1<<B); ++j)
				f[now][j]=0;
			for(int j = 0; j < (1<<B); ++j) 
				if(f[now^1][j]) {
					if(!((j>>(B-1))&1) && dl[i][1])
						add(f[now][(j<<1)|1], f[now^1][j]);
					if(!((j>>(A-1))&1) && dl[i][0])
						add(f[now][((j^(((j>>(B-1))&1)<<(B-1)))<<1)|1|(1<<A)], f[now^1][j]);
					add(f[now][((j^(((j>>(B-1))&1)<<(B-1)))<<1)], f[now^1][j]);
				}
		}
		for(int j = 0; j < (1<<B); ++j)
			add(ans, f[now][j]);
		write(ans, '\n');
		return 0;
	}
	else {
		int len = n/B+1, d = __gcd(A, B), sum = 0;
		for(int i = 0; i < len; ++i)
			for(int j = 0; j < B; ++j)
				nb[i][j]=i*B+j;
		ans=1;
		for(int i = 1; i <= d; ++i) {
			for(int o = 0; o < (1<<len); ++o) {
				int st = (i+A)%B, pd = 1, now = 0, gs = (i+A)/B;
				for(int j = 0; j < len; ++j)
					if(((o>>j)&1) && !dl[nb[j][i]][0]) {
						pd=0;
						break;
					}
				if(pd) {
					for(int j = 0; j < len; ++j)
						if((o>>j)&1)
							vis[(nb[j][i]-A)]=1;
					for(int j = 0; j < (1<<len); ++j)
						f[0][j]=f[1][j]=0;
					f[0][o]=1;
					for(int ls = o; ls < (1<<len); ++ls)
						if(f[0][ls])
							for(int j = 1; j < len; ++j) 
								if(!((ls>>(j-1))&1) && !((ls>>j)&1) && dl[nb[j][i]][1]) 
									f[0][ls|(1<<(j-1))|(1<<j)]=1;
					for(; st != i; gs=(st+A)/B, st=(st+A)%B) {
						for(int j = len-1; j >= 0; --j) {
							now^=1;
							for(int ls = 0; ls < (1<<len); ++ls)
								f[now][ls]=0;
							for(int ls = 0; ls < (1<<len); ++ls)
								if(f[now^1][ls]) {
									int ns = (ls^(((ls>>j)&1)<<j));
									if(!vis[nb[j][st]]) {
										if(j != len-1 && !((ls>>(j+1))&1) && !vis[nb[j][st]+B] && ad[nb[j][st]][1]) 
											add(f[now][ns|(1<<(j+1))|(1<<j)], f[now^1][ls]);
										if(j >= gs && !((ls>>(j-gs))&1) && dl[nb[j][st]][0])
											add(f[now][ns|(1<<j)|(1<<(j-gs))], f[now^1][ls]);
									}
									add(f[now][ns], f[now^1][ls]);
								}
						}
					}
					for(int ls = 0; ls < (1<<len); ++ls) 
						add(sum, f[now][ls]);
					for(int j = 0; j < len; ++j)
						if((o>>j)&1)
							vis[(nb[j][i]-A)]=0;
				}
			}
			ans=1LL*ans*sum%mod;
			sum=0;
		}
		write(ans, '\n');
		return 0;
	}
	return 0;
}
