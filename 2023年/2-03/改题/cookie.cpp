#include <bits/stdc++.h>
using namespace std;
int t, n, b[1005], k, ans[505][1005][2], mx;
struct qwq {
	int x, id;
}a[1005];
long long sum;
int comp(qwq A, qwq B) {
	return A.x > B.x;
}
void solve() {
	sort(a+1, a+1+n, comp);
	if(a[1].x == 0) return ;
	++k;
	if(a[3].x == 0) 
		a[1].x=0, a[2].x=0, sum = 0;
	sum-=a[1].x;
	if(a[2].x < sum-a[2].x) {
		int qwq = min((sum-a[2].x)-a[2].x, 1LL*a[1].x);
		a[1].x-=qwq;
		for(int i = n; i > 2; --i) {
			int haha = min(a[i].x, qwq);
			a[i].x-=haha, qwq-=haha, sum-=haha;
		}
	}
	if(a[2].x > sum-a[2].x) {
		int qwq = min(a[2].x-(sum-a[2].x), 1LL*a[1].x);
		a[1].x-=qwq;
		a[2].x-=qwq;
		sum-=qwq;
	}
	if(a[2].x == sum-a[2].x) {
		int qwq = a[1].x/2;
		a[2].x-=qwq; a[1].x=0;
		sum-=qwq+qwq;
		for(int i = 3; i <= n; ++i) {
			int haha = min(a[i].x, qwq);
			a[i].x-=haha, qwq-=haha;
		}
	}
	for(int i = 1; i <= n; ++i)
		ans[k][a[i].id][0]=ans[k-1][a[i].id][1]-a[i].x, ans[k][a[i].id][1]=a[i].x;
	solve();
}
int main() {
//	freopen("cookie.in", "r", stdin);
//	freopen("cookie.out", "w", stdout);
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		sum = mx = k = 0;
		memset(ans, 0, sizeof ans);
		for(int i = 1; i <= n; ++i)
			scanf("%d", &a[i].x), sum=sum+1LL*a[i].x, mx = max(mx, a[i].x), 
			a[i].id=i, ans[0][i][1]=a[i].x;
		if(sum%2 == 1 || mx > sum-mx) {
			puts("NO");
			continue;
		}
		puts("YES");
		solve();
		printf("%d\n", k);
		for(int i = 1; i <= k; ++i) {
			for(int j = 1; j <= n; ++j)
				printf("%d ", ans[i][j][0]);
			printf("\n");
		}
	}
	return 0;
} 
