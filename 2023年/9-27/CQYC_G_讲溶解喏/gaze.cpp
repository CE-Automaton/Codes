#include <bits/stdc++.h>
using namespace std;
const int N = 5e5+5;
int n, m, h[N], tot, cnt, to[N], tr[N];
struct que {
	int opt, a, b;
}pro[N], zhan[N];

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
int comp(que aaa, que bbb) {
	return aaa.a < bbb.a;
}
void add(int x, int w) {
	while(x <= cnt)
		tr[x]+=w, x+=(x&(-x));
}
int ask(int x, int ret = 0) {
	while(x >= 1)
		ret+=tr[x], x-=(x&(-x));
	return ret;
}

signed main() {
	freopen("gaze.in", "r", stdin);
	freopen("gaze.out", "w", stdout);
	read(n), read(m);
	for(int i = 1; i <= n; ++i)
		read(h[i]), zhan[++tot]=que {0, h[i], i};
	for(int i = 1; i <= m; ++i) {
		read(pro[i].opt), read(pro[i].a);
		if(pro[i].opt == 2) read(pro[i].b), zhan[++tot]=que {1, pro[i].b, i}; 
		else zhan[++tot]=que {2, pro[i].a, i};
	}
	sort(zhan+1, zhan+1+tot, comp);
	for(int i = 1; i <= tot; ++i) {
		if(i == 1 || zhan[i].a != zhan[i-1].a)
			++cnt, to[cnt]=zhan[i].a;
		if(zhan[i].opt == 1)
			pro[zhan[i].b].b=cnt;
		else
			if(zhan[i].opt == 0)
				h[zhan[i].b]=cnt;
			else
				pro[zhan[i].b].a=cnt;
	}
	for(int i = 1; i <= n; ++i)
		add(h[i], -1);
	for(int i = 1; i+1 <= n; ++i)
		add(min(h[i], h[i+1]), 1);
	for(int i = 1; i <= m; ++i) {
		if(pro[i].opt == 1) 
			write(1+ask(pro[i].a-1), '\n');
		else {
			add(h[pro[i].a], 1);
			if(pro[i].a != n)
				add(min(h[pro[i].a], h[pro[i].a+1]), -1);
			if(pro[i].a != 1)
				add(min(h[pro[i].a-1], h[pro[i].a]), -1);
			h[pro[i].a]=pro[i].b;
			add(h[pro[i].a], -1);
			if(pro[i].a != n)
				add(min(h[pro[i].a], h[pro[i].a+1]), 1);
			if(pro[i].a != 1)
				add(min(h[pro[i].a-1], h[pro[i].a]), 1);
		}
	}
	return 0;
}
