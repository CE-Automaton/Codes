#include <bits/stdc++.h>
using namespace std;
const int N = 5e5+5;
int n, ans[N];
int main() {
	freopen("stone.in", "r", stdin);
	freopen("stone.out", "w", stdout);
	scanf("%d", &n);
	if(n%4 > 1) {
		puts("NO");
		return 0;
	}
	puts("YES");
	ans[n/2+1]=n;
	for(int i = 1; i <= n/4; ++i)
		ans[n-i+1]=i, ans[i]=n-i;
	ans[n/4+1]=n/4+1;
	for(int i = n/4+2; i < (n+1)/2+1; ++i)
		ans[n-i+2]=i;
	for(int i = (n+1)/2+1; i <= n-1-n/4; ++i)
		ans[n-i+1]=i;
	for(int i = 1; i <= n; ++i)
		printf("%d %d\n", i, ans[i]);
	return 0;
}
