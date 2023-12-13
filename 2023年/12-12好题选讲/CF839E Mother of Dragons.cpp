#include <bits/stdc++.h>
using namespace std;
const int N = 45;
int n, k;
long long a[N];
unordered_map <long long, int> v, p;

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
int dfs(long long x) {
	if(!x) return 0;
	if(v.find(x) != v.end()) return v[x];
	long long oo = (x&(-x));
	return v[x]=max(dfs(x-oo), dfs(x&a[p[oo]])+1);
}

signed main() {
	read(n), read(k);
	for(int i = 0; i < n; ++i) 
		for(int j = 0, p = 0; j < n; ++j) {
			read(p); if(p) a[i]|=(1LL<<j);
		}
	for(int i = 0; i < n; ++i) 
		p[(1LL<<i)]=i;
	long double ans=dfs((1LL<<n)-1);
	// cout<<dfs((1LL<<n)-1)<<"\n";
	ans=(long double) k*k/ans*(ans-1)/2;
	printf("%.10Lf\n", ans);
	return 0;
}
