#include <bits/stdc++.h>
#define int long long
using namespace std;
const signed N = 1e5+5;
int n, m, vis[N], tot, v, ans, sum, a, ww[N<<2];
struct az {
	int a, c;
	bool operator <(const az& A) const {
		return A.a > a;
	}
}t[N<<2], zhan[N<<2];
priority_queue <az> q;
struct qwq {
	int pd, d;
	int c, w;
}b[N<<2];

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
int comp(qwq A, qwq B) {
	if(A.w*B.c == B.w*A.c)
		return A.c < B.c;
	return A.w*B.c > B.w*A.c;
}

signed main() {
	freopen("king.in", "r", stdin);
	freopen("king.out", "w", stdout);
	read(n), read(m);
	for(int i = 1; i <= n; ++i)
		read(a), b[i]=qwq {0, 0, 1, a};
	for(int i = 1; i <= m; ++i)
		read(t[i].a), b[i*2-1+n]=qwq {1, i, 1, t[i].a}, 
		read(t[i].c), b[i*2+n]=qwq {1, i, 2, t[i].c};
	read(v);
	sort(b+1, b+1+n+m+m, comp);
	n=n+m+m;
	for(int i = 1; i <= n && v >= 1; ++i) {
		while(v >= 1 && !q.empty() && q.top().a*b[i].c > q.top().c*b[i].w) 
			--v, ans+=q.top().a, vis[q.top().c]=2, q.pop();//1换成2 
		if(v == 0) break;
		if(!b[i].pd) 
			v-=b[i].c, ans+=b[i].w, zhan[++tot]=az {b[i].w, 0};
		else {
			if(vis[b[i].d]) 
				continue;
			if(b[i].c > v/*代价为2*/) {
//				cout<<"!?\n";
				while(tot && zhan[tot].c != 0 && vis[zhan[tot].c] == 2)
					--tot;
				if(tot)
					sum=max(sum, ans-zhan[tot].a+b[i].w);
			}
			else {
				v-=b[i].c, ans+=b[i].w;
				if(b[i].c == 1)
					zhan[++tot]=az {b[i].w, b[i].d}, vis[b[i].d]=1, 
					q.push(az {t[b[i].d].c-b[i].w, b[i].d});
				else
					vis[b[i].d]=2;
			}
		}
//		cout<<b[i].pd<<" "<<b[i].w<<" "<<b[i].c<<"\n";
	}
	if(v >= 1) {
		tot=0;
		for(int i = 1; i <= m; ++i)
			if(vis[i] == 1)
				ww[++tot]=t[i].c-t[i].a;
		sort(ww+1, ww+1+tot);
		for(int i = tot; i >= 1; --i) 
			if(v && ww[i] >= 0)
				--v, ans+=ww[i];
	}
	sum=max(sum, ans);
	write(sum, '\n');
	return 0;
}
