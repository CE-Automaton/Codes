#include <bits/stdc++.h>
#define inf 1000000000000000007LL
#define int long long
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int t, n, w, nxt[N], tot, brd[N], mst[N], lst, ll[N<<1], az[N<<1], op, ans, lq, rq, que[N<<1];
char s[N];

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
void work(int d, int lx, int md) {
	int cnt = __gcd(d, md);
	if(lx == -2) {
		for(int i = 0; i < d; ++i) ll[i]=mst[i];
		for(int i = 0; i < md; ++i) mst[i]=inf;
		for(int i = 0; i < d; ++i)
			mst[ll[i]%md]=min(mst[ll[i]%md], ll[i]);
		for(int i = 0; i < cnt; ++i) {
			op=0;
			int now = i;
			do ll[++op]=now, now=(now+d)%md; while(now != i);
			for(int j = 1; j <= op; ++j)
				ll[j+op]=ll[j];
			op<<=1;
			for(int j = 2; j <= op; ++j)
				mst[ll[j]]=min(mst[ll[j]], mst[ll[j-1]]+d);
		}
		return ;
	}
	work(lst, -2, md);
	lst=md;
	if(d < 0) return ;
	for(int i = 0; i < cnt; ++i) {
		op=0;
		int now = i, st = 1;
		do az[++op]=now, now=(now+d)%md; while(now != i);
		for(int j = 1; j <= op; ++j) {
			if(mst[az[st]] > mst[az[j]]) st=j;
			az[j+op]=az[j];
		}
		for(int j = st; j <= op; ++j)
			ll[j-st+1]=az[j];
		for(int j = 1; j < st; ++j)
			ll[op-st+1+j]=az[j];
		lq=1, rq=0;
		for(int j = 1; j <= op; ++j) {
			while(lq <= rq && que[lq]+lx < j)
				++lq;
			if(lq <= rq)
				mst[ll[j]]=min(mst[ll[j]], mst[ll[que[lq]]]+(j-que[lq])*d+md);
			while(lq <= rq && mst[ll[que[rq]]]-que[rq]*d > mst[ll[j]]-j*d)
				--rq;
			que[++rq]=j;
		}
	}
}

signed main() {
	read(t);
	while(t--) {
		read(n), read(w);
		w-=n;
		scanf("%s", s+1);
		for(int i = 2, j = 0; i <= n; ++i) {
			while(j && s[j+1] != s[i]) j=nxt[j];
			if(s[j+1] == s[i]) ++j;
			nxt[i]=j;
		}
		tot=0, lst=n;
		memset(brd, 0, sizeof brd);
		int nw = nxt[n];
		while(nw) brd[++tot]=n-nw, nw=nxt[nw];
		brd[++tot]=n;
		for(int i = 0; i < n; ++i)
			mst[i]=inf;
		mst[0]=0;
		for(int l = 1, r = l, d = 0; l <= tot; l = r) {
			r = l, d = brd[l+1]-brd[l];
			while(brd[r+1]-brd[r] == d) ++r;
			work(d, r-l-1, brd[l]);
		}
		ans=0;
		for(int i = 0; i < n; ++i)
			if(mst[i] <= w)
				ans=ans+(w-mst[i])/n+1;
		write(ans, '\n');
	}
	return 0;
}