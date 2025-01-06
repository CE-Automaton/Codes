#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e5+5;
int n, m, q, op[N], ll[N], rr[N], vv[N], u[N], v[N], rt, gss;
unsigned long long ans[N];
vector <int> pro[N], orp[N];

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
struct node {//动态开点线段树
	int ls, rs;
	unsigned long long tg, w;
}tr[N*30];
void upup(int k, int l, int r) {
	tr[k].w=1ull*(r-l+1)*tr[k].tg+(tr[k].ls ? tr[tr[k].ls].w : 0)+(tr[k].rs ? tr[tr[k].rs].w : 0);
}
void add(int &k, int l, int r, int lq, int rq, int w) {
	if(!k)
		++gss, k=gss, tr[k]=node {0, 0, 0, 0};
	if(lq <= l && r <= rq) {
		tr[k].w+=1ull*(r-l+1)*w;
		tr[k].tg+=1ull*w;
		return ;
	}
	int mid = ((l+r)>>1);
	if(lq <= mid)
		add(tr[k].ls, l, mid, lq, rq, w);
	if(mid < rq)
		add(tr[k].rs, mid+1, r, lq, rq, w);
	upup(k, l, r);
}
unsigned long long ask(int k, int l, int r, int lq, int rq) {
	if(!k) 
		return 0;
	if(lq <= l && r <= rq) 
		return tr[k].w;
	int mid = ((l+r)>>1);
	unsigned long long ret = 1ull*max(min(rq, r)-max(lq, l)+1, 0)*tr[k].tg;
	if(lq <= mid)
		ret+=ask(tr[k].ls, l, mid, lq, rq);
	if(mid < rq)
		ret+=ask(tr[k].rs, mid+1, r, lq, rq);
	return ret;
}

signed main() {
	File("sakura");
	read(n), read(m), read(q);
	for(int i = 1; i <= m; ++i) {
		read(op[i]), read(ll[i]), read(rr[i]);
		if(op[i] == 1)
			read(vv[i]);
	}
	for(int i = 1; i <= q; ++i) {
		read(u[i]), read(v[i]);
		if(u[i] == 1)
			pro[v[i]].push_back(i);
		else
			orp[u[i]].push_back(i);
	}
	rt=gss=0;
	unsigned long long sum=0;
	for(int j = 1; j <= m; ++j) {
		if(op[j] == 1)
			add(rt, 1, n, ll[j], rr[j], vv[j]);
		else
			sum+=ask(rt, 1, n, ll[j], rr[j]);
		for(int i : pro[j])
			ans[i]=sum;
	}
	rt=gss=0;
	sum=0;
	for(int j = m; j >= 1; --j) {
		if(op[j] == 2)
			add(rt, 1, n, ll[j], rr[j], 1);
		else
			sum+=1ull*ask(rt, 1, n, ll[j], rr[j])*vv[j];
		for(int i : orp[j])
			ans[i]=sum;
	}
	for(int i = 1; i <= q; ++i)
		write(ans[i], '\n');
	return 0;
}