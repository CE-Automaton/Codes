#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N = 1e5+5;
bitset<1005> az[1005], za[1005], ss;
int n, k, l[N], r[N], a[N], zhan[N], tot, q, xx, ll, rr, cnt;
struct qwq {
	int w, i;
}b[N];

char buf[(1<<21)+5],*p1,*p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
template <typename T> void read(T& x) {
	x = 0; int f = 0; char c = getchar();
	while(!isdigit(c)) f |= (c == '-'), c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48), c=getchar();
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
	return A.w < B.w;
}

signed main() {
	freopen("summer.in", "r", stdin);
	freopen("summer.out", "w", stdout);
	read(n), read(k);
	for(int i = 1; i <= n; ++i)
		read(a[i]), b[i]=qwq{a[i], i};
	sort(b+1, b+1+n, comp);
	for(int i = 1; i <= n; ++i) {
		if(b[i].w != b[i-1].w || i == 1)
			++cnt;
		a[b[i].i]=cnt;
	}
	read(q);
	for(int o = 1; o <= q; ++o) {
		read(xx), read(ll), read(rr);
		swap(a[xx], a[xx+1]);
		for(int i = 1; i <= n; ++i)
			l[i]=r[i]=0;
		for(int i = 1; i <= n; ++i) {
			while(tot && a[zhan[tot]] < a[i]) r[zhan[tot]]=i, --tot;
			zhan[++tot]=i;
		}
		tot=0;
		for(int i = n; i >= 1; --i) {
			while(tot && a[zhan[tot]] < a[i]) l[zhan[tot]]=i, --tot;
			zhan[++tot]=i;
		}
		tot=0;
		for(int i = 1; i <= n; ++i) {
			az[i].reset();
			if(l[i] != 0)
				az[i]=az[l[i]], az[i][a[l[i]]]=1;
		}
		for(int i = n; i >= 1; --i) {
			za[i].reset();
			if(r[i] != 0)
				za[i]=za[r[i]], za[i][a[r[i]]]=1;
		}
		int ans = 0;
		for(int j = ll; j <= rr; ++j) {
			ss=(az[j]|za[j]);
			ans+=n-1+k*ss.count();
//			cout<<j<<" "<<ss.count()<<": ";
//			for(int o = ss._Find_first(); o <= n; o = ss._Find_next(o))
//				cout<<o<<" ";
//			puts("");
		}
		write(ans, '\n');
	}
	return 0;
}
