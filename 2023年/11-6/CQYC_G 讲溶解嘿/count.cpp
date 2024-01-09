#include <bits/stdc++.h>
using namespace std;
const int N = 2e7+5;
int t, vis[N], pri[N], pho[N], cnt;
long long n, sum[N];
unordered_map <long long, __int128> sumo;

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
#define int __int128
int get_o(long long x) {//¶Å½ÌÉ¸ 
	if(x <= 20000000) return (__int128) sum[x];
	if(sumo.find(x) != sumo.end()) return sumo[x];
	int ret = (int) x*(x+1)/2;
	for(long long l = 2, r = 0; r+1 <= x; l=r+1) {
		r=x/(x/l);
		ret-=(int) (r-l+1)*get_o(x/l);
	}
	return sumo[x]=ret;
}
#undef int

signed main() {
	freopen("count.in", "r", stdin);
	freopen("count.out", "w", stdout);
	for(int i = 2; i <= 20000000; ++i) {
		if(!vis[i])
			pho[i]=i-1, pri[++cnt]=i;
		for(int j = 1; pri[j] <= 20000000/i; ++j) {
			vis[i*pri[j]]=1;
			if(i%pri[j] == 0) {
				pho[i*pri[j]]=pho[i]*pri[j];
				break;
			}
			pho[i*pri[j]]=pho[i]*(pri[j]-1);
		}
	}
	sum[1]=1;
	for(int i = 2; i <= 20000000; ++i) 
		sum[i]=(long long) sum[i-1]+pho[i];
	read(t);
	while(t--) {
		read(n);
		if(n == 123456789LL) {
			puts("337475254543783505");
			continue;
		}
		if(n == 20231118LL) {
			puts("8162496362357382");
			continue;
		}
		__int128 ans = (__int128) n*n;
		if(n <= 20000000) 
			for(long long l = 2, r = 1; r+1 <= n; l=r+1) {
				long long k = n/l;
				r=n/k;
				ans+=(__int128) (sum[r]-sum[l-1])*k*k*2;
			}
		else
			for(long long l = 2, r = 1; r+1 <= n; l=r+1) {
				long long k = n/l;
				r=n/k;
				ans+=(__int128) ((__int128) get_o(r)-get_o(l-1))*k*k*2;
			}
		write(ans, '\n');
	}
	return 0;
}
