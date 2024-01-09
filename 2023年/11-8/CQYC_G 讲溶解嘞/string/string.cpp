#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
const int N = 1e6+5;
int n, s, t[N], o[N], vis[N], pri[N], cnt, ans;
vector <int> to[N];

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
int ksm(int x, int y, int ret = 1) {
	while(y) {
		if(y&1)
			ret=1LL*ret*x%mod;
		x=1LL*x*x%mod;
		y=(y>>1);
	}
	return ret;
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}

signed main() {
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);
	o[1]=1;
	for(int i = 2; i <= 1000000; ++i) {
		if(!vis[i]) pri[++cnt]=i, o[i]=i-1;
		for(int j = 1; j <= cnt && pri[j] <= 1000000/i; ++j) {
			vis[pri[j]*i]=1;
			if(i%pri[j] == 0) {
				o[pri[j]*i]=o[i]*pri[j];
				break;
			}
			o[pri[j]*i]=o[i]*(pri[j]-1);
		}
	}
	read(n), read(s);
	for(int i = 1; i <= n; ++i) 
		for(int j = i+i; j <= n; j+=i)
			to[j].push_back(i); 
	for(int i = 1; i <= n; ++i) {
		t[i]=((i&1) ? 1LL*ksm(s, (i+1)/2)*i%mod : 1LL*i/2*ksm(s, i/2)%mod*(s+1)%mod);
		for(int j : to[i])
			t[i]=upd(t[i]-1LL*o[i/j]*t[j]%mod+mod);
		ans=upd(ans+t[i]);
	}
	write(ans, '\n');
	return 0;
}

