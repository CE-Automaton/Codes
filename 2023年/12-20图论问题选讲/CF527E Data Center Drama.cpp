#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+3, M = 8e5+5;
int n, cnt=1, u, v, fir[N], to[M], nxt[M], val[M], d[N], ans, k, lst;

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
void edge(int x, int y) {
	++d[x], ++d[y];
	nxt[++cnt]=fir[x], to[cnt]=y, fir[x]=cnt;
	nxt[++cnt]=fir[y], to[cnt]=x, fir[y]=cnt;
}
void dfs(int x) {
	for(int& i = fir[x]; i; i=nxt[i])
		if(!val[i]) {
			val[i]=val[i^1]=1;
			int y = to[i];
			dfs(y);
			++k;
			if(k&1)
				write(x, ' '), write(y, '\n');
			else
				write(y, ' '), write(x, '\n');
		}
}

signed main() {
	read(n), read(ans);
	for(int i = 1; i <= ans; ++i)
		read(u), read(v), edge(u, v);
	for(int i = 1; i <= n; ++i)
		if(d[i]&1) {
			if(!lst)
				lst=i;
			else
				edge(lst, i), ++ans, lst=0;
		}
	if(ans&1)
		edge(1, 1), ++ans;
	write(ans, '\n');
	dfs(1);
	return 0;
}
