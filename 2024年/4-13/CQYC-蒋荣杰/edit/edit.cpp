#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int n, c, gsa[2], gsb[2];
char s[N], t[N], a='0', b='0';

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
	File("edit");
	read(n), read(c);
	scanf("%s\n%s", s+1, t+1);
	for(int i = 1; i <= n; ++i) {
		if(s[i] != a) {
			if(a == '0') a=s[i];
			else b=s[i];
		}
		if(s[i] == t[i]) {
			if(s[i] == a)
				++gsa[0];
			else
				++gsb[0];
		}
		else {
			if(s[i] == a)
				++gsa[1];
			else
				++gsb[1];
		}
	}
	write(min(gsa[1]+gsb[1], min(c+gsa[0]+gsb[1], c+gsb[0]+gsa[1])), '\n');
	return 0;
}
