#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
const int N = 5e5+5;
int n, a[N], tot, q, l, r, zhan[N], tot2, zhan2[N];
LL sum[N];
vector <pii> que[N];
struct qwq {
	LL a; int b;
	bool operator <(const qwq& A) const {
		return 1LL*a*A.b < 1LL*A.a*b;
	}
	void ccc() {
		LL op = __gcd(a, 1LL*b);
		a=a/op, b=1LL*b/op;
	}
}tr[N], ans[N];

namespace FastIO {
	const int SIZE=(1<<21)+1;
	char ibuf[SIZE],obuf[SIZE],*iS,*iT,*oS=obuf,*oT=obuf;
	char* flush(){fwrite(obuf,1,oT-oS,stdout);return oT=obuf;}
	struct Flusher{~Flusher(){flush();}}flusher;
	inline char gc(){return iS==iT && (iT=(iS=ibuf)+fread(ibuf,1,SIZE,stdin),iS==iT)?EOF:*iS++;}
	inline void pc(char c){if(oT==oS+SIZE) flush();*oT++=c;}
	#define getchar gc
	#define putchar pc
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
}
using FastIO::gc;
using FastIO::pc;
using FastIO::read;
using FastIO::write;
void add(int x, qwq w) {
	while(x >= 1) {
		if(tr[x] < w)
			tr[x]=w;
		x=x-(x&(-x));
	}
}
qwq ask(int x, qwq ret = {0, 1}) {
	while(x <= n) {
		if(ret < tr[x])
			ret=tr[x];
		x=x+(x&(-x));
	}
	return ret;
}

signed main() {
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]), sum[i]=sum[i-1]+a[i];
	read(q);
	if(q == 1) {
		read(l), read(r);
		qwq mx = qwq {0, 1};
		for(int i = 1; i <= n; ++i) {
			qwq it = qwq {sum[i]*sum[i], i};
			if(mx < it)
				mx=it;
			while(tot && sum[zhan[tot]] >= sum[i]) 
				--tot;
			for(int j = tot, o = 200; j >= 1 && o >= 1; --j, --o) {
				it = qwq {(sum[i]-sum[zhan[j]])*(sum[i]-sum[zhan[j]]), i-zhan[j]};
				if(mx < it)
					mx=it;
			}
			zhan[++tot]=i;
			while(tot2 && sum[zhan2[tot2]] <= sum[i]) 
				--tot2;
			for(int j = tot2, o = 200; j >= 1 && o >= 1; --j, --o) {
				it = qwq {(sum[i]-sum[zhan2[j]])*(sum[i]-sum[zhan2[j]]), i-zhan2[j]};
				if(mx < it)
					mx=it;
			}
			zhan2[++tot2]=i;
		}
		mx.ccc();
		write(mx.a, ' '), write(mx.b, '\n');
		FastIO::flusher.~Flusher();
		return 0;
	}
	for(int i = 1; i <= q; ++i)
		read(l), read(r), que[r].push_back(make_pair(l, i));
	for(int i = 1; i <= n; ++i)
		tr[i].b=1;
	for(int i = 1; i <= n; ++i) {
		add(1, qwq {sum[i]*sum[i], i});
		while(tot && sum[zhan[tot]] >= sum[i]) 
			/*add(zhan[tot], qwq {(sum[i]-sum[zhan[tot]])*(sum[i]-sum[zhan[tot]]), i-zhan[tot]}), */--tot;
		for(int j = tot, o = 200; j >= 1 && o >= 1; --j, --o)
			add(zhan[j]+1, qwq {(sum[i]-sum[zhan[j]])*(sum[i]-sum[zhan[j]]), i-zhan[j]});
		zhan[++tot]=i;
		while(tot2 && sum[zhan2[tot2]] <= sum[i]) 
			/*add(zhan2[tot2], qwq {(sum[i]-sum[zhan2[tot2]])*(sum[i]-sum[zhan2[tot2]]), i-zhan2[tot2]}), */--tot2;
		for(int j = tot2, o = 200; j >= 1 && o >= 1; --j, --o)
			add(zhan2[j]+1, qwq {(sum[i]-sum[zhan2[j]])*(sum[i]-sum[zhan2[j]]), i-zhan2[j]});
		zhan2[++tot2]=i;
		for(pii y : que[i])
			ans[y.second]=ask(y.first);
	}
	for(int i = 1; i <= q; ++i)
		ans[i].ccc(), write(ans[i].a, ' '), write(ans[i].b, '\n');
	FastIO::flusher.~Flusher();
	return 0;
}
/*o这个变量用来卡常的，不保证正确性*/