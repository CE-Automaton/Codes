#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int n, m, s, t, u, v, w, head[N], cnt=1, nxt[N<<1], to[N<<1], f[N<<1];

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
void add(int x, int y, int w) {
	nxt[++cnt]=head[x];
	to[cnt]=y, f[cnt]=w;
	head[x]=cnt;
}

signed main() {
	read(n), read(m), read(s), read(t);
	for(int i = 1; i <= m; ++i) 
		read(u), read(v), read(w), add(u, v, w), add(v, u, 0);
	
	return 0;
}
