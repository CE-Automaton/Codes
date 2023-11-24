#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
const int N = 3e6+5;
int tot, pri[N], vis[N], gs, t, hh[N];
long long n, ans;
struct qwq {
	long long w;
	int cnt;
}zhan[N];

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
void dfs(int x, long long w, int pd, int cn) {
	if(pd) 
		zhan[++gs]=qwq {w, cn};
	if(n/w < 1LL*pri[x]*pri[x]) return ;
	if(x == tot+1) return ;
	dfs(x+1, w, 0, cn);
	dfs(x+1, w*pri[x]*pri[x], 1, cn+1);
}
int comp(qwq A, qwq B) {
	return A.w < B.w;
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}

signed main() {
	freopen("asa.in", "r", stdin);
	freopen("asa.out", "w", stdout);
	hh[1]=1;
	for(int i = 2; i <= 1000000; ++i) {
		hh[i]=-hh[i-1];
		if(!vis[i])
			pri[++tot]=i;
		for(int j = 1; j <= tot && pri[j] <= 1000000/i; ++j) {
			vis[pri[j]*i]=1;
			if(i%pri[j] == 0)
				break;
		}
	}
	n=1000000000000LL;
	dfs(1, 1, 0, 0);
	sort(zhan+1, zhan+1+gs, comp);
	read(t); 
	while(t--) {
		read(n);
		ans=0;
		for(int i = 1; i <= gs && zhan[i].w <= n; ++i) {
			long long m = n/zhan[i].w%mod;
			ans=upd(ans+upd(1LL*m*m%mod*hh[zhan[i].cnt]+mod));
		}
		write(ans, '\n');
	}
	return 0;
}
