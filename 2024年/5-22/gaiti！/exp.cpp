#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e6+5;
int len, n, siz[N], l[N], r[N];
char s[N<<2];

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
int dfs(int now) {
	int nw = ++n;
	siz[nw]=0;
	if(s[now] == '?') {
		siz[nw]=1;
		l[nw]=r[nw]=1;/*表示第l~r小能够成为子树的权值*/
		return now+1;
	}
	else {
		int ll = n+1, rt = dfs(now+4), rr = n+1;
		++rt;
		rt=dfs(rt);
		if(s[now+1] == 'a') {
			l[nw]=l[ll]+l[rr];
			r[nw]=max(siz[rr]+r[ll], siz[ll]+r[rr]);
		}
		else {
			l[nw]=min(l[ll], l[rr]);
			r[nw]=r[ll]+r[rr]-1;
		}
		siz[nw]=siz[ll]+siz[rr];
		return rt+1;
	}
}

signed main() {
	scanf("%s", s+1);
	len=strlen(s+1);
	int rt = dfs(1);
	write(r[1]-l[1]+1, '\n');
	return 0;
}