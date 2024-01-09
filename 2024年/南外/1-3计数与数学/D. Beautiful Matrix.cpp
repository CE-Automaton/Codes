#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
const int N = 2e3+5;
int n, a[N][N], f[N][N], pw[N], ans, u[N], v[N];
struct bit {
	int tr[N];
	void add(int x, int w = -1) {
		while(x <= n) tr[x]+=w, x=x+(x&(-x));
	}
	void built() {
		memset(tr, 0, sizeof tr);
		for(int i = 1; i <= n; ++i) add(i, 1);
	}
	int ask(int x, int ret = 0) {
		while(x >= 1) ret+=tr[x], x=x-(x&(-x));
		return ret;
	}
}t1, t2;

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
int upd(int x) {
	return (x >= mod ? x-mod : x);
}

signed main() {
	read(n);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			read(a[i][j]);
	f[0][0]=1;
	for(int i = 1; i <= n; ++i) {
		for(int j = 0; j < i; ++j)
			f[i][j]=upd(1LL*(i-j)*f[i-1][j]%mod+(j == 0 ? 0 : 1LL*j*f[i-1][j-1]%mod));
		f[i][i]=1LL*(i-1)*upd(f[i-1][i-1]+(i == 1 ? 0 : f[i-2][i-2]))%mod;
	}
	pw[0]=1;
	for(int i = 1; i <= n; ++i)
		pw[i]=1LL*pw[i-1]*f[n][n]%mod;
	t1.built();
	for(int i = 1; i <= n; ++i) {
		t1.add(a[1][i]);
		ans=upd(ans+1LL*t1.ask(a[1][i]-1)*f[n-i][0]%mod);
	}
	ans=1LL*ans*pw[n-1]%mod;
	for(int i = 2; i <= n; ++i) {
		t1.built(), t2.built();
		memset(u, 0, sizeof u);
		memset(v, 0, sizeof v);
		int sum = 0;
		for(int j = 1; j < n; ++j) {
			if(!v[a[i-1][j]]) t2.add(a[i-1][j]);
			u[a[i-1][j]]=1;
			if(j != 1 && !u[a[i][j-1]]) t2.add(a[i][j-1]);
			v[a[i][j-1]]=1;
			int l = t2.ask(n), l1 = t1.ask(a[i][j]-1), l2 = t2.ask(a[i][j]-1);
			if(a[i-1][j] < a[i][j] && !v[a[i-1][j]]) --l1;
			sum=upd(sum+1LL*(l1-l2)*f[n-j][l]%mod);
			if(l >= 1)
				sum=upd(sum+1LL*l2*f[n-j][l-1]%mod);
			t1.add(a[i][j]);
		}
		ans=upd(ans+1LL*sum*pw[n-i]%mod);
	}
	write(ans, '\n');
	return 0;
}
