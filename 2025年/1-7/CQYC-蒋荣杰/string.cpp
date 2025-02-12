#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int m, n, typ, ps, ln, nxt[N], l, ans;
char p[N], s[N], w[N];

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
	File("string");
	read(m), read(n);
	scanf("%s", p+1);
	for(int i = 1; i <= n; ++i) {
		read(typ);
		if(typ == 1) {
			scanf("%s", w+1);
			int op = strlen(w+1);
			for(int j = 1; j <= op; ++j)
				s[++l]=w[j];
		}
		else {
			read(ps), read(ln);
			for(int j = 1; j <= ln; ++j)
				s[++l]=s[ps+j-1];
		}
	}
	for(int i = 2, j = 0; i <= m; ++i) {
		while(j && p[i] != p[j+1]) j=nxt[j];
		if(p[i] == p[j+1]) ++j;
		nxt[i]=j;
	}
	for(int i = 1, j = 0; i <= l; ++i) {
		while(j && p[j+1] != s[i])
			j=nxt[j];
		if(p[j+1] == s[i])
			++j;
		if(j == m)
			++ans, j=nxt[j];
	}
	write(ans, '\n');
	return 0;
}
