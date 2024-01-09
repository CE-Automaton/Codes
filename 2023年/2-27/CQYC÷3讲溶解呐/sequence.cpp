#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int n, a[N], b[N], cnt, top[N], to[N], tot;
long long sum, ans;
struct qwq {
	int s, id;
}c[N];
int comp(qwq A, qwq B) {
	return A.s < B.s;
}
vector <int> az[N];
int main() {
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", &a[i]), c[i]=qwq{a[i], i};
	sort(c+1, c+1+n, comp);
	for(int i = 1; i <= n; ++i) {
		if(i == 1 || c[i].s != c[i-1].s)
			b[++cnt]=c[i].s;
		a[c[i].id]=cnt;
	}
	int c = 0;
	for(int i = 1; i <= n; ++i) {
		if(az[a[i]].size() == 0) {
			++c;
			to[++tot]=i;
		}
		az[a[i]].push_back(i);
		sum+=1LL*i*c;
	}
	if(n == 1) {
		printf("%lld\n", sum);
		return 0;
	}
	int st = 1;
	if(n <= 5000) {
		top[a[1]]=1;
//		for(int i = 1; i <= tot; ++i)
//			cout<<to[i]<<"\n";
		for(int i = 2; i <= n; ++i) {
			if(i != az[a[i]][0]) continue;
			for(int j = st; j <= tot; ++j) {
				if(to[j] < i) {
					int v = to[j], o = a[v];
					while(top[o] < az[o].size() && az[o][top[o]] <= i)
						++top[o];
					int r = n;
					if(top[o] < az[o].size()) 
						r=az[o][top[o]]-1;
//					cout<<v<<" "<<b[o]<<" "<<i<<" "<<r<<"\n";
					ans=max(ans, (long long) 1LL*(r+i)*(r-i+1)/2-abs(b[a[i]]-b[o]));
				}
			}
		}
		printf("%lld\n", sum-ans);
		return 0;
	}
	int pd = 0;
	for(int i = 1; i <= n; ++i) {
		if(az[i].size() <= 1) continue;
		pd=1;
	}
	if(!pd)
		ans=1LL*(n+2)*(n-1)/2;
	else 
		for(int i = 1; i <= n; ++i) {
			if(az[i].size() <= 1) continue;
			int ooo = 1;
			for(int j = 0; j < az[i].size()-1; ++j) {
				int l = az[i][j], r = az[i][j+1]-1;
				while(ooo <= tot && to[ooo] <= l) ++ooo;
				if(ooo > tot) break;
				if(to[ooo] > r) continue;
				while(ooo <= tot && to[ooo] <= r)
					ans=max(ans, (long long) 1LL*(r+to[ooo])*(r-to[ooo]+1)/2-abs(b[i]-b[a[to[ooo]]])), 
					++ooo;
			}
		}
	printf("%lld\n", sum-ans);
	return 0;
}
