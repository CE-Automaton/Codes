#include <bits/stdc++.h>
using namespace std;
const int N = 2e6+5;
int n, q, a[N], cnt, to[N], gs[N], tr[N], rr;
struct qwq {
	int u, v;
}b[N], pro[N];

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
	return A.u < B.u;
}
void addd(int x, int w) {
	while(x <= cnt)
		tr[x]+=w, x=x+(x&(-x));
}
int ask(int x, int ret = 0) {
	while(x >= 1)
		ret=ret+tr[x], x=x-(x&(-x));
	return ret;
}
void add(int x, int w) {
	int pd1 = (gs[x] == 0);
	gs[x]+=w;
	int pd2 = (gs[x] == 0);
	if(x > rr) return ;
	if(pd1)
		addd(x, 1)/*, cout<<x<<"!?\n"*/;
	if(pd2) 
		addd(x, -1)/*, cout<<x<<"?!\n"*/;
}

signed main() {
	read(n), read(q);
	for(int i = 1; i <= n; ++i)
		read(a[i]), b[i]=qwq{a[i], i}; 
	for(int i = 1; i <= q; ++i)
		read(pro[i].u), read(pro[i].v), b[i+n]=qwq{pro[i].v, i+n};
	sort(b+1, b+1+n+q, comp);
	for(int i = 1; i <= n+q; ++i) {
		if(i == 1 || b[i].u != b[i-1].u)
			to[++cnt]=b[i].u;
		if(b[i].v <= n)
			a[b[i].v]=cnt;
		else
			pro[b[i].v-n].v=cnt;
	}
	if(to[1] != 0)
		rr=0;
	else {
		rr=cnt;
		for(int i = 2; i <= cnt; ++i)
			if(to[i] != to[i-1]+1) {
				rr=i-1;
				break;
			}
	}
	for(int i = 1; i <= n; ++i)
		add(a[i], 1);
	for(int i = 1; i <= q; ++i) {
		add(a[pro[i].u], -1);
		add(pro[i].v, 1);
		a[pro[i].u]=pro[i].v;
		int l = 1, r = rr, rtt = 0, ans = 0;
		while(l <= r) {
			int mid = ((l+r)>>1);
			if(ask(mid) == mid)
				rtt=mid, l=mid+1;
			else
				r=mid-1;
		}
//		cout<<rtt<<"!!!!\n";
		if(rtt >= 1) {
//			cout<<rtt<<" "<<to[rtt]<<"\n";
			if(to[1] != 0)
				ans=0;
			else
				ans=to[rtt]+1;
		}
		else
			ans=0;
		write(ans, '\n'); 
	}
	return 0;
}
