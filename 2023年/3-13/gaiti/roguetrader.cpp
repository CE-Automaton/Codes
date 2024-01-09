#include <bits/stdc++.h>
char buf[1<<23],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
using namespace std;
int n, v, ans[200005];
long long op, ll;
struct qwq {
	int a, b, c;
}wp[200005];
struct hs {
	long long sum;
	vector <int> s;
	void add(int x, int y) {
		for(int i = v; i >= x; --i)
			sum-=s[i], s[i]=max(s[i], s[i-x]+y), sum+=s[i];
	}
}st;

template <typename T> inline void read(T& s) {
	s=0; char ch = getchar(); while(ch<'0' || ch > '9') ch=getchar();
	while(ch >= '0'&& ch <= '9') s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
}
int lne; char put[105];
template <typename T> void write(T x) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
}
int check(int L, int mid, int R, hs now) {
	for(int i = L; i <= mid; ++i)
		now.add(wp[i].b, wp[i].c);
	for(int i = mid+1; i <= R; ++i)
		now.add(wp[i].a, wp[i].c);
	return (now.sum <= ll);
}
int find(int L, int R, hs now) {
	int ret = n+1;
	while(L <= R) {
		int mid = ((L+R)>>1);
		if(check(L, mid, R, now)) {
			for(int i = mid; i <= R; ++i)
				now.add(wp[i].a, wp[i].c);
			R=mid-1, ret=mid;
		}
		else {
			for(int i = L; i <= mid; ++i)
				now.add(wp[i].b, wp[i].c);
			L=mid+1;
		}
	}
	return ret;
}
void solve(int l, int r, int L, int R, hs now) {
//	cout<<l<<" "<<r<<" "<<L<<" "<<R<<"\n";
	if(l > r || L > R) return ;
	while(L < l)
		now.add(wp[L].a, wp[L].c), ++L;
	hs bf = now;
	int mid = ((l+r)>>1);
	for(int i = l; i < mid; ++i)
		now.add(wp[i].a, wp[i].c);
	for(int i = mid; i <= min(r, L-1); ++i)
		now.add(wp[i].b, wp[i].c);
	ans[mid]=find(max(mid, L), R, now);
	now=bf;
	for(int i = mid; i <= min(r, L-1); ++i)
		now.add(wp[i].b, wp[i].c);
	for(int i = ans[mid]+1; i <= R; ++i)
		now.add(wp[i].a, wp[i].c);
	solve(l, mid-1, L, ans[mid], now);
	if(ans[mid] > n) return ;
	now=bf;
	for(int i = l; i <= min(mid, ans[mid]-1); ++i)
		now.add(wp[i].a, wp[i].c);
	for(int i = max(L, r+1); i < ans[mid]; ++i)
		now.add(wp[i].b, wp[i].c);
	solve(mid+1, r, ans[mid], R, now);
}

signed main() {
	freopen("roguetrader.in", "r", stdin);
    freopen("roguetrader.out", "w", stdout);
	read(n), read(v), read(ll);
	ll=1LL*ll*v;
	for(int i = 1; i <= n; ++i)
		read(wp[i].a), read(wp[i].b), read(wp[i].c), ans[i]=n+1;
	st.sum=0;
	st.s.resize(v+5);
	for(int i = 0; i <= v; i++) 
		st.s[i]=0;
	solve(1, n, 1, n, st);
	for(int i = 1; i <= n; ++i)
		op+=n-ans[i]+1;
	write(op);
	return 0;
}
