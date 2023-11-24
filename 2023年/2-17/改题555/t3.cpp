#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5+5;
int n, d, a[N], rr[N][25], ll[N][25], suml[N][25], sumr[N][25], g[25], q, l, r;
signed main() {
	freopen("warinheaven.in", "r", stdin);
	freopen("warinheaven.out", "w", stdout);
	scanf("%lld%lld", &n, &d);
	for(int i = 1; i <= n; ++i)
		scanf("%lld", &a[i]);
	g[0]=1;
	for(int j = 1; j <= 20; ++j) 
		g[j]=g[j-1]+g[j-1];
	for(int i = 1; i <= n; ++i) {
		rr[i][0]=n+1, l=i+1, r=n;
		while(l <= r) {
			int mid = (l+r)/2;
			if(a[mid]-a[i] >= d)
				rr[i][0]=mid, r=mid-1;
			else
				l=mid+1;
		}
		ll[i][0]=0, l=1, r=i-1;
		while(l <= r) {
			int mid = (l+r)/2;
			if(a[i]-a[mid] >= d)
				ll[i][0]=mid, l=mid+1;
			else
				r=mid-1;
		}
	}
	for(int i = 1; i <= n; ++i) {
		suml[i][0]=ll[i][0];
		for(int j = 1; j <= 20; ++j) 
			ll[i][j]=ll[ll[i][j-1]][j-1], 
			suml[i][j]=suml[i][j-1]+suml[ll[i][j-1]][j-1];
	}
	for(int i = n; i >= 1; --i) {
		sumr[i][0]=rr[i][0];
		for(int j = 1; j <= 20; ++j) 
			rr[i][j]=rr[rr[i][j-1]][j-1], 
			sumr[i][j]=sumr[i][j-1]+sumr[rr[i][j-1]][j-1];
	}
	scanf("%lld", &q);
	for(int i = 1; i <= q; ++i) {
		scanf("%lld%lld", &l, &r);
		int ts = 1+r, ss = l, p = l;/*cout<<l<<" ";*/
		for(int j = 20; j >= 0; --j) {
			if(rr[p][j] == n+1 || rr[p][j] == 0 || rr[p][j] > r) continue;
			ss+=sumr[p][j];
			p=rr[p][j];/*cout<<p<<" ";*/
		}/*puts("");*/
		p=r;/*cout<<r<<" ";*/
		for(int j = 20; j >= 0; --j) {
			if(ll[p][j] == n+1 || ll[p][j] == 0 || ll[p][j] < l) continue;
			ts+=suml[p][j], ts+=g[j];
			p=ll[p][j];/*cout<<p<<" ";*/
		}/*puts("");puts("");*/
		printf("%lld\n", r-l+1-ts+ss);
	}
	return 0;
}
