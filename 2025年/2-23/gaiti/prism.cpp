#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e3+5;
int n, m, a[N][N], cnt, dd[N][N][4], fa[N*N], w[N][N], cc[N][N][4], t[N][N];
struct qwq { int x, y, k; } b[N*N], bk[N*N];

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
int find(int x) {
	return (x == fa[x] ? x : fa[x]=find(fa[x]));
}
void merge(int x, int y) {
	x=find(x), y=find(y);
	fa[x]=y;
}
bool comp(qwq A, qwq B) {
	return a[A.x][A.y] < a[B.x][B.y];
}

signed main() {
	File("prism");
	read(n), read(m);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j) {
			read(a[i][j]);
			for(int o = 0; o < 4; ++o)
				dd[i][j][o]=++cnt, bk[cnt]=qwq {i, j, o},
				fa[cnt]=cnt, cc[i][j][o]=1;
			b[i*m+j-m]=qwq {i, j};
		}
	sort(b+1, b+1+n*m, comp);
	for(int o = 1; o <= n*m; ++o) {
		int i = b[o].x, j = b[o].y, oo = ((cc[i][j][0]^cc[i][j][1]^cc[i][j][2]^cc[i][j][3])&1&a[i][j]);
		t[i][j]=(oo^w[i][j]);
		if(!t[i][j]) {
			merge(dd[i][j][0], dd[i+1][j][0]);
			merge(dd[i][j][1], dd[i][j-1][1]);
			merge(dd[i][j][2], dd[i-1][j][2]);
			merge(dd[i][j][3], dd[i][j+1][3]);
			int op = find(dd[i+1][j][0]);
			// debug(i, j, 0, "->", bk[op].x, bk[op].y, bk[op].k, "?\n");
			cc[bk[op].x][bk[op].y][bk[op].k]^=cc[i][j][0];
			oo=(cc[i][j][0]&a[i][j]&1);
			w[bk[op].x][bk[op].y]^=oo;
			op = find(dd[i][j-1][1]);
			// debug(i, j, 1, "->", bk[op].x, bk[op].y, bk[op].k, "?\n");
			cc[bk[op].x][bk[op].y][bk[op].k]^=cc[i][j][1];
			oo=(cc[i][j][1]&a[i][j]&1);
			w[bk[op].x][bk[op].y]^=oo;
			op = find(dd[i-1][j][2]);
			// debug(i, j, 2, "->", bk[op].x, bk[op].y, bk[op].k, "?\n");
			cc[bk[op].x][bk[op].y][bk[op].k]^=cc[i][j][2];
			oo=(cc[i][j][2]&a[i][j]&1);
			w[bk[op].x][bk[op].y]^=oo;
			op = find(dd[i][j+1][3]);
			// debug(i, j, 3, "->", bk[op].x, bk[op].y, bk[op].k, "?\n");
			cc[bk[op].x][bk[op].y][bk[op].k]^=cc[i][j][3];
			oo=(cc[i][j][3]&a[i][j]&1);
			w[bk[op].x][bk[op].y]^=oo;
		}
		else {
			merge(dd[i][j][0], dd[i][j-1][1]);
			merge(dd[i][j][1], dd[i-1][j][2]);
			merge(dd[i][j][2], dd[i][j+1][3]);
			merge(dd[i][j][3], dd[i+1][j][0]);
			int op = find(dd[i][j-1][1]);
			cc[bk[op].x][bk[op].y][bk[op].k]^=cc[i][j][0];
			oo=(cc[i][j][0]&a[i][j]&1);
			w[bk[op].x][bk[op].y]^=oo;
			op = find(dd[i-1][j][2]);
			cc[bk[op].x][bk[op].y][bk[op].k]^=cc[i][j][1];
			oo=(cc[i][j][1]&a[i][j]&1);
			w[bk[op].x][bk[op].y]^=oo;
			op = find(dd[i][j+1][3]);
			cc[bk[op].x][bk[op].y][bk[op].k]^=cc[i][j][2];
			oo=(cc[i][j][2]&a[i][j]&1);
			w[bk[op].x][bk[op].y]^=oo;
			op = find(dd[i+1][j][0]);
			cc[bk[op].x][bk[op].y][bk[op].k]^=cc[i][j][3];
			oo=(cc[i][j][3]&a[i][j]&1);
			w[bk[op].x][bk[op].y]^=oo;
		}
	}
	for(int i = 1; i <= n; ++i, putchar('\n'))
		for(int j = 1; j <= m; ++j)
			putchar((char) '0'+t[i][j]);
	return 0;
}
