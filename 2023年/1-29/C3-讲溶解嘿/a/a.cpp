#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
int n, k, a[200005], b[200005], ka[300005], kb[300005], suka[300005], sukb[300005], hahaha;
int upd(int x) {
	return (x < 0 ? x+mod : (x >= mod ? x-mod : x));
}
int main() {
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	scanf("%d%d", &n, &k); ++k;
	for(int i = 1; i <= n; ++i)
		scanf("%d", &a[i]), a[i+n]=a[i];
	for(int i = 1; i <= n; ++i)
		scanf("%d", &b[i]), b[i+n]=b[i];
	for(int i = 1; i <= n; ++i)
		ka[i+n+n]=ka[i+n]=ka[i]=upd(a[i+1]-a[i]), kb[i+n+n]=kb[i+n]=kb[i]=upd(b[i+1]-b[i]);
	for(int i = 1; i <= 3*n; ++i)
		suka[i]=upd(suka[i-1]+ka[i]), sukb[i]=upd(sukb[i-1]+kb[i]);
	for(int x = 1; x <= n; ++x) {
		int xh = 1, pd = 0;
//		if(x == 335) {
//		cout<<x<<":\n";
//			int az = upd(a[1]-b[x]);
//			for(int i = 1; i <= n-1; ++i)
//				az = upd(az+upd(ka[i]-kb[i+x-1])), cout<<ka[i]<<" "<<kb[i+x-1]<<"\n";
//			cout<<"???\n";
//		}
		for(; xh <= k; ++xh)
			if(suka[xh] == upd(sukb[x+xh-1]-sukb[x-1])) {
//			cout<<x<<" "<<xh<<"\n";
				int ooo = 1;
				for(int ha = xh; ha <= n+xh; ha+=xh) {
					for(int st = 1; st <= xh; ++st) {
						if(ha+st >= n) break;
						if(upd(suka[ha+st]-upd(sukb[ha+st+x-1]-sukb[x-1])) != 
						   upd(suka[ha+st-xh]-upd(sukb[ha+st+x-1-xh]-sukb[x-1]))) {
//						   cout<<ha<<" "<<st<<" "<<upd(suka[ha+st]-upd(sukb[ha+st+x-1]-sukb[x-1]))<<" "<<upd(suka[ha+st-xh]-upd(sukb[ha+st+x-1-xh]-sukb[x-1]))<<"!!!\n";
							ooo=0;
							ha=mod;
							break;
						}
					}
				}
				pd|=ooo;
			}
		if(pd) {
			printf("%d\n", x-1);
			hahaha = 1;
			break;
		}
	}
	if(!hahaha)
		puts("-1");
	return 0;
}
