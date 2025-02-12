#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int n, tot;
LL a[N], zhan[N], ans;

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
long double kkk(int x, int y) {
	return (long double) 1.0*(a[x]-a[y])/(x-y);
}

signed main() {
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	for(int i = 1; i <= n; ++i) {
		while(tot >= 2 && ceil(kkk(zhan[tot-1], zhan[tot])) >= ceil(kkk(zhan[tot], i)))
			--tot;
		zhan[++tot]=i;
	}
	for(int i = 1; i < tot; ++i) {
		if(ceil(kkk(zhan[i], zhan[i+1])) == kkk(zhan[i], zhan[i+1])) {
			LL k = kkk(zhan[i], zhan[i+1]), b = a[zhan[i]]-k*zhan[i];
			for(int j = zhan[i]+1; j < zhan[i+1]; ++j)
				ans+=k*j+b;
		}
		else {
			LL k = floor(kkk(zhan[i], zhan[i+1])), b = a[zhan[i]]-k*zhan[i],
			kk = ceil(kkk(zhan[i], zhan[i+1])), bb = a[zhan[i+1]]-kk*zhan[i+1];
			for(int j = zhan[i]+1; j < zhan[i+1]; ++j) {
				LL now = k*j+b;
				if(now+1LL*(zhan[i+1]-j)*kk < a[zhan[i+1]]) {
					for(int o = j; o < zhan[i+1]; ++o)
						ans+=kk*o+bb;
					break;
				}
				ans+=now;
			}
		}
	}
	for(int i = 1; i <= tot; ++i) 
		ans+=a[zhan[i]];
	write(ans, '\n');
	return 0;
}