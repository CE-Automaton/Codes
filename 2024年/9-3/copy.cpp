#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e5+5;
int k, m, n, l[N], r[N], xx[N], to[202];
char s[N];

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

signed main() {
	read(k), read(m);
	scanf("%s", s+1);
	read(n);
	for(int i = 1; i <= n; ++i) 
		read(l[i]), read(r[i]), read(xx[i]);
	for(int i = 1; i <= k; ++i)
		to[i]=i;
	for(int i = n; i >= 1; --i) 
		for(int j = 1; j <= k; ++j)
			if(xx[i]+1 <= to[j] && to[j] <= xx[i]+r[i]-l[i]) 
				to[j]=l[i]+to[j]-xx[i];
			else
				if(to[j] > xx[i]+r[i]-l[i])
					to[j]=to[j]-r[i]+l[i];
	for(int j = 1; j <= k; ++j)
		putchar(s[to[j]]);
	return 0;
}