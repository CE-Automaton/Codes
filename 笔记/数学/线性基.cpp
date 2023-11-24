#include <bits/stdc++.h>
using namespace std;
int n;
long long a, p[105], ans;
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%lld", &a);
		for(int j = 50; j >= 0; --j)
			if((1LL<<j)&a)
				if(p[j]) a^=p[j];
				else { p[j]=a; break; }
	} 
	for(int j = 50; j >= 0; --j)
		if((p[j]^ans) > ans) ans=(ans^p[j]);
	printf("%lld\n", ans);
	return 0;
} 
