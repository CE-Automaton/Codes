#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int n, h[N], r[N], R[N], zhan[N], tot;
long double st[N], ans;

template <typename T> void read(T& x) {
	x = 0; int f = 0; char c = getchar();
	while(c < '0' || c > '9') f |= (c == '-'), c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x);
}
long double dis(int x, int y) {//y放x，y底距离x底
	// if(R[x] == r[y] || R[x] == R[y] || r[x] == R[y] || r[x] == r[y]) puts("@");
	if(r[y] >= R[x])
		return (long double) h[x];
	if(R[y] <= r[x]) 
		return 0;
	long double fr = 0, 
	aa=(long double) 1.0*(R[x]-r[x])/2, bb=(long double) 1.0*(R[y]-r[y])/2;
	if((long double) h[x] > (long double) 1.0*h[y]*aa/bb) {
		if(R[y] <= R[x]) {
			fr=(long double) 1.0*h[x]*(R[y]-r[x])/(R[x]-r[x]);
			if((long double) h[y] > fr) {
				// debug("?");
				return 0;
			}
			return (long double) fr-h[y];
		}
		else {
			fr = (long double) 1.0*h[y]*(R[x]-r[y])/(R[y]-r[y]);
			if((long double) h[x] < fr) {
				// debug("?");
				return 0;
			}
			return (long double) h[x]-fr;
		}
	}
	else 
		return (r[y] <= r[x] ? 0 : (long double) 1.0*h[x]*(r[y]-r[x])/(R[x]-r[x]));
}

signed main() {
	File("wan");
	read(n);
	for(int i = 1; i <= n; ++i)
		read(h[i]), read(r[i]), read(R[i]);
	ans=(long double) h[1];
	zhan[tot=1]=1;
	for(int i = 2; i <= n; ++i) {
		if(n <= 3000)
			for(int j = 1; j < i; ++j) 
				st[i]=max(st[i], st[j]+dis(j, i));
		else {
			for(int j = i-6; j < i; ++j) 
				st[i]=max(st[i], st[j]+dis(j, i));
		}
		ans=max(ans, (long double) st[i]+h[i]);
	}
	printf("%.12Lf", ans);
	return 0;
}
