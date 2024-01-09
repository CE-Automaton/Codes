#include <bits/stdc++.h>
using namespace std;
int n, a[1005][1005], hav[1005], cnt;
long long ans;
struct pnt{
	int x, y;
};
vector <pnt> wz[1000006];
void solve(int col) {
	vector <int> ha[1005];
	int lst = 0;
	cnt = 0;
	for(auto qwq : wz[col]) {
		int x = qwq.x, y = qwq.y;
		if(x != lst) hav[++cnt]=x, lst=x, ha[x].push_back(0);
		int l = 0, r = n+1;
		for(int i = cnt; i >= 1; --i) {
			if(l+1 >= r) break;
			if(ha[hav[i]].size() == 0) continue;
			auto it = lower_bound(ha[hav[i]].begin(), ha[hav[i]].end(), y);
			if(it != ha[hav[i]].end()) r=min(r, *it);
			l=max(l, *prev(it));
			ans=ans+1LL*(y-l)*(hav[i]-hav[i-1])*(r-y)*(n-x+1);
		}
		ha[x].push_back(y);
	}
}
int main() {
	freopen("d.in","r",stdin) ;
	freopen("d.out","w",stdout) ;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			scanf("%d", &a[i][j]), wz[a[i][j]].push_back(pnt{i, j});
	for(int i = 1; i <= n*n; ++i) solve(i);
	printf("%lld\n", ans);
	return 0;
} 
