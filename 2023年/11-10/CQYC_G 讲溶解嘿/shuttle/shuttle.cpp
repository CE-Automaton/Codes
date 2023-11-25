#include <bits/stdc++.h>
#define inf 100000000000000000LL
using namespace std;
const int N = 1e5+5;
int n, m, x[N], h[N], l, r, w;
long long dis[N];
struct qwq {
	int y, w;
};
struct qaq {
	int y, h;
	long long w;
};
vector <qwq> to[N];
queue <qaq> q;

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
void sol(int xx) {
	for(int i = 1; i <= n; ++i)
		dis[i]=inf;
	dis[xx]=0;
	q.push(qaq {xx, 0, 0});
	int cnt = 0;
	while(!q.empty()) {
		qaq it = q.front(); q.pop();
		dis[it.y]=min(dis[it.y], it.w+it.h);
		if(cnt <= 600000) 
			for(qwq yy : to[it.y]) {
				long long ww = (long long) abs(yy.w-it.h)+abs(x[yy.y]-x[it.y])+it.w;
                if(ww >= inf) continue;
				q.push(qaq {yy.y, yy.w, ww}), ++cnt;
			}
	}
}

signed main() {
	 freopen("shuttle.in", "r", stdin);
	 freopen("shuttle.out", "w", stdout);
	read(n), read(m);
	for(int i = 1; i <= n; ++i)
		read(x[i]), read(h[i]);
	for(int i = 1; i <= m; ++i) {
		read(l), read(r), read(w);
        ++l, ++r;
		int lst = 0;
		for(int j = l; j <= r; ++j) 
            if(h[j] >= w) {
                if(lst) 
                    to[lst].push_back(qwq {j, w}), 
                    to[j].push_back(qwq {lst, w});
                lst=j;
            }
	}
	read(l), read(r);
    ++l, ++r;
	sol(l);
	write(dis[r], '\n');
	return 0;
}
