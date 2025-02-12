#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e5+5;
int n, m, q, vv[N], ww[N], dd[N], tr[N], u, v, fx[10][2]={{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
LL ans[N];
struct qwq {
	int x, y, xx, yy;
}a[N], fr[N];
struct qvq { int x, y, w; };
vector <qvq> add[N];
struct akk { int y, d; };
vector <akk> qury[N];

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
void addd(int x, int w) {
	while(x <= 250000)
		tr[x]+=w, x+=(x&(-x));
}
int ask(int x, int ret = 0) {
	while(x)
		ret+=tr[x], x-=(x&(-x));
	return ret;
}

signed main() {
	File("paint");
	read(n), read(m), read(q);
	for(int i = 1; i <= n; ++i)
		read(a[i].x), read(a[i].y), read(a[i].xx), read(a[i].yy), 
		add[a[i].x].push_back(qvq {a[i].y, a[i].yy, 1}), 
		add[a[i].xx+1].push_back(qvq {a[i].y, a[i].yy, -1});
	for(int i = 1; i <= m; ++i) {
		read(vv[i]), read(ww[i]), read(dd[i]);
		fr[i]=a[ww[i]];
		a[ww[i]].x+=fx[vv[i]][0]*dd[i];
		a[ww[i]].y+=fx[vv[i]][1]*dd[i];
		a[ww[i]].xx+=fx[vv[i]][0]*dd[i];
		a[ww[i]].yy+=fx[vv[i]][1]*dd[i];
		vv[i]=(vv[i]+4)%8;//reverse
		--dd[i];
	}
	for(int i = 1; i <= q; ++i) {
		read(u), read(v);
		qury[u].push_back(akk {v, i});
		for(int j = 1; j <= m; ++j) {
			u+=fx[vv[j]][0], v+=fx[vv[j]][1];
			if(vv[j] == 0 && fr[j].y <= v && v <= fr[j].yy) 
				ans[i]+=max(0, min(u+dd[j], fr[j].xx)-max(u, fr[j].x)+1);
			if(vv[j] == 2 && fr[j].x <= u && u <= fr[j].xx) 
				ans[i]+=max(0, min(v+dd[j], fr[j].yy)-max(v, fr[j].y)+1);
			if(vv[j] == 4 && fr[j].y <= v && v <= fr[j].yy) 
				ans[i]+=max(0, min(u, fr[j].xx)-max(u-dd[j], fr[j].x)+1);
			if(vv[j] == 6 && fr[j].x <= u && u <= fr[j].xx) 
				ans[i]+=max(0, min(v, fr[j].yy)-max(v-dd[j], fr[j].y)+1);
			if(vv[j] == 1) {
				int l = max(u, fr[j].x), r = min(u+dd[j], fr[j].xx), ll = max(v, fr[j].y), rr = min(v+dd[j], fr[j].yy);
				ans[i]+=max(0, min(r, rr)-max(l, ll)+1);
			}
			if(vv[j] == 3) {
				int l = max(u-dd[j], fr[j].x), r = min(u, fr[j].xx), ll = max(v, fr[j].y), rr = min(v+dd[j], fr[j].yy);
				ans[i]+=max(0, min(r, rr)-max(l, ll)+1);
			}
			if(vv[j] == 5) {
				int l = max(u-dd[j], fr[j].x), r = min(u, fr[j].xx), ll = max(v-dd[j], fr[j].y), rr = min(v, fr[j].yy);
				ans[i]+=max(0, min(r, rr)-max(l, ll)+1);
			}
			if(vv[j] == 7) {
				int l = max(u, fr[j].x), r = min(u+dd[j], fr[j].xx), ll = max(v-dd[j], fr[j].y), rr = min(v, fr[j].yy);
				ans[i]+=max(0, min(r, rr)-max(l, ll)+1);
			}
			u-=fx[vv[j]][0], v-=fx[vv[j]][1];
		}
		// debug(ans[i], "???\n");
	}
	for(int i = 1; i <= 250000; ++i) {
		for(auto j : add[i])
			addd(j.x, j.w), addd(j.y+1, -j.w);
		for(auto j : qury[i])
			ans[j.d]+=ask(j.y);
	}
	for(int i = 1; i <= q; ++i)
		write(ans[i], '\n');
	return 0;
}
