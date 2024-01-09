#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
typedef long long LL;
using namespace std;
const int N = 1e4+5;
LL n, p[N];
int c, t, m, to[12][12], now[32], cc[32];
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
struct qwq {
	int a[32][32];
	void clear() {
		for(int i = 0; i <= t; ++i)
			for(int j = 0; j <= t; ++j)
				a[i][j]=0;
	}
	qwq operator * (const qwq& A) const {
		qwq ret; ret.clear();
		for(int i = 0; i <= t; ++i)
			for(int k = 0; k <= t; ++k)
				if(a[i][k])
					for(int j = 0; j <= t; ++j)
						if(A.a[k][j])
							ret.a[i][j]=upd(ret.a[i][j]+1LL*a[i][k]*A.a[k][j]%mod);
		return ret;
	}
}w, pw[65];

template <typename T> inline void debug(T x) { cerr<<x<<'\n'; }
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
void add(LL x) {
	if(x <= 0) return ;
	for(int i = 0; i < 60; ++i)
		if((x>>i)&1) {
			// debug(i, "?");
			// for(int j = 0; j <= t; ++j)
			// 	cout<<now[j]<<" ";
			// putchar('\n');
			// for(int j = 0; j <= t; ++j, putchar('\n'))
			// 	for(int k = 0; k <= t; ++k)
			// 		cout<<pw[i].a[j][k]<<" ";
			for(int j = 0; j <= t; ++j)
				cc[j]=now[j], now[j]=0;
			for(int j = 0; j <= t; ++j)
				for(int k = 0; k <= t; ++k)
					if(pw[i].a[j][k])
						now[k]=upd(now[k]+1LL*cc[j]*pw[i].a[j][k]%mod);
		}
}

signed main() {
	File("paper");
	read(n), read(m), read(c);
	for(int i = 1; i <= c; ++i)
		for(int j = 0; j < i; ++j)
			to[i][j]=(++t);
	// cout<<t<<"!?\n";
	w.clear();
	for(int i = 1; i <= c; ++i)
		for(int j = 0; j < i; ++j)
			w.a[to[i][(j-1+i)%i]][to[i][j]]=1;
	pw[0]=w;
	for(int i = 1; i <= c; ++i) {
		++pw[0].a[to[i][i-1]][0];
		for(int j = 1; j <= c; ++j)
			++pw[0].a[to[i][i-1]][to[j][0]];
	}
	for(int i = 1; i < 60; ++i)
		pw[i]=pw[i-1]*pw[i-1];
	for(int i = 1; i <= m; ++i)
		read(p[i]), ++p[i];
	sort(p+1, p+1+m);
	m=unique(p+1, p+1+m)-p-1;
	for(int j = 1; j <= c; ++j)
		now[to[j][0]]=1;
	for(int i = 1; i <= m; ++i) {
		// debug(p[i-1]+1, p[i]-1, "and", p[i], "not!");
		add(p[i]-p[i-1]-1);
		for(int j = 0; j <= t; ++j)
			cc[j]=now[j], now[j]=0;
		for(int j = 0; j <= t; ++j)
			for(int k = 0; k <= t; ++k)
				if(w.a[j][k])
					now[k]=upd(now[k]+1LL*cc[j]*w.a[j][k]%mod);
	}
	add(n-p[m]);
	write(now[0], '\n');
	return 0;
}