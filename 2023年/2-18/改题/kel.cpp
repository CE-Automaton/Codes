#include <bits/stdc++.h>
using namespace std;
int n, L, R, ans[1000005], cnt;
int main() {
	freopen("kel.in", "r", stdin);
	freopen("kel.out", "w", stdout); 
	scanf("%d%d%d", &n, &L, &R);
	int qwq = R-L+1;
	if(1LL*qwq*(qwq+1)+1 >= 1LL*n) {
		for(int u = L; u <= R && n >= 1; ++u) {
			for(int i = u; i <= R && n >= 1; ++i) {
				ans[++cnt]=u;
				--n;
				if(n <= 0) break;
				ans[++cnt]=i;
				--n;
			}
			if(n == 1) 
				--n, ans[++cnt]=L;
		}
		for(int i = 1; i <= cnt; ++i)
			printf("%d\n", ans[i]);
		return 0;
	}
	puts("Shinomiya");
	return 0;
} 
