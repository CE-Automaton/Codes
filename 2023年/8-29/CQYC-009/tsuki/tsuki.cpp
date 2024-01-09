#include <bits/stdc++.h>
#define mod 147744151
using namespace std;

const int N = 1e3+5, mx = 35;
int n, m, p, q, x, y, xx, yy, a[N][N], len, bl[N], gs, sm[N][mx], sml[N][N], smr[N][N], az[N], to[mx][mx], cnt, tl[N], trr[N], pd[N][N], ans;
struct tree {
	int tr[N<<2];
	#define ls (k<<1)
	#define rs ((k<<1)|1)
	void built(int k, int l, int r) {
		if(l == r) {
			tr[k]=az[l];
			return ;
		}
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
		tr[k]=1LL*tr[ls]*tr[rs]%p;
	}
	int ask(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq)
			return tr[k];
		int mid = ((l+r)>>1), ret = 1;
		if(lq <= mid)
			ret=1LL*ret*ask(ls, l, mid, lq, rq)%p;
		if(mid+1 <= rq)
			ret=1LL*ret*ask(rs, mid+1, r, lq, rq)%p;
		return ret;
	}
	#undef ls
	#undef rs
}A[19504];

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
int upd(int x) {
	return (x >= mod ? x-mod : x);
}

signed main() {
	freopen("tsuki.in", "r", stdin);
	freopen("tsuki.out", "w", stdout);
	read(n), read(m), read(p);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			read(a[i][j]), sml[i][j]=smr[i][j]=1;
	len = m/((int) sqrt(m)), gs = m/len+(m%len != 0);
	for(int i = 1, j = 1; i <= m; ++i)
		bl[i]=j, j+=(i%len == 0);
//	write(len, ' '), write(gs, '\n');
	for(int i = 1; i <= gs; ++i)
		for(int j = 1; j <= n; ++j)
			sm[j][i]=1;
	for(int i = 1; i <= n; ++i) {
		int lst = 0, ss = 0;
		for(int j = 1; j <= m; ++j) {
			sm[i][bl[j]]=1LL*sm[i][bl[j]]*a[i][j]%p;
			if(bl[j] == lst)
				ss=1LL*ss*a[i][j]%p;
			else
				lst=bl[j], ss=a[i][j];
			sml[i][j]=ss;
		}
		lst = 0, ss = 0;
		for(int j = m; j >= 1; --j) {
			if(bl[j] == lst)
				ss=1LL*ss*a[i][j]%p;
			else
				lst=bl[j], ss=a[i][j];
			smr[i][j]=ss;
		}
	}
	cnt=0;
	for(int l = 1; l <= gs; ++l) {
		for(int i = 1; i <= n; ++i)
			az[i]=1;
		for(int r = l; r <= gs; ++r) {
			for(int i = 1; i <= n; ++i)
				az[i]=1LL*az[i]*sm[i][r]%p;
			A[++cnt].built(1, 1, n);
			to[l][r]=cnt;
		}
	}
	for(int j = 1; j <= m; ++j) {
		for(int i = 1; i <= n; ++i)
			az[i]=sml[i][j];
		A[++cnt].built(1, 1, n);
		tl[j]=cnt;
		for(int i = 1; i <= n; ++i)
			az[i]=smr[i][j];
		A[++cnt].built(1, 1, n);
		trr[j]=cnt;
	}
	for(int l = 1; l <= m; ++l) {
		for(int i = 1; i <= n; ++i) 
			az[i]=1;
		for(int r = l; r <= m && bl[l] == bl[r]; ++r) {
			for(int i = 1; i <= n; ++i) 
				az[i]=1LL*az[i]*a[i][r]%p;
			A[++cnt].built(1, 1, n);
			pd[l][r]=cnt;
		}
	}
//	cout<<cnt<<"???\n";
	read(q);
	for(int i = 1; i <= q; ++i) {
		read(x), read(y), read(xx), read(yy);
		if(bl[y] == bl[yy]) 
			ans=upd((i^A[pd[y][yy]].ask(1, 1, n, x, xx))%mod+ans);
		else 
			if(bl[y]+1 == bl[yy]) 
				ans=upd((i^(1LL*A[trr[y]].ask(1, 1, n, x, xx)*A[tl[yy]].ask(1, 1, n, x, xx)%p))%mod+ans);
			else {
				int sss=1LL*A[trr[y]].ask(1, 1, n, x, xx)*A[tl[yy]].ask(1, 1, n, x, xx)%p*A[to[bl[y]+1][bl[yy]-1]].ask(1, 1, n, x, xx)%p;
				ans=upd(ans+(i^sss)%mod);
			}
	}
	write(ans, '\n');
	return 0;
}
