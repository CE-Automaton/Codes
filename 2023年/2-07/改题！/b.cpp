#include <bits/stdc++.h>
using namespace std;
int n, m, x[205], y[205], pd, ans, to[205][205], gs[205], l=1, r, w[205][205], ha[205], vis[205];
int check() {
	int cnt = 1;
	for(int i = 1; i <= n; ++i) vis[i]=0;
	ha[1]=rand()%n+1, vis[ha[1]]=1;
	for(int i = 2; i <= n; ++i) {
		int x;
		do {x=rand()%n+1;} while(vis[x]);
		vis[x]=1;
		int haha = 1;
		for(int j = 1; j <= cnt; ++j)
			if(!to[ha[j]][x]) {
				haha = 0;
				break;
			}
		if(haha) ha[++cnt]=x;
	}
	return (cnt >= m);
}
int main() {
//	freopen("b.in", "r", stdin);
//	freopen("b.out", "w", stdout); 
	srand(time(0));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) 
		scanf("%d%d", &x[i], &y[i]);
	for(int i = 1; i <= n; ++i) 
		for(int j = 1; j < i; ++j) {
			int qaq = (x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
			w[i][j]=w[j][i]=qaq;
			r=max(r, qaq);
		}
	while(l <= r) {
		int mid = (l+r)/2, aaa = 0;
		for(int i = 1; i <= n; ++i) {
			gs[i]=0;
			for(int j = 1; j < i; ++j) 
				to[i][j]=to[j][i]=0;
		}
		for(int i = 1; i <= n; ++i) 
			for(int j = i+1; j <= n; ++j) 
				if(w[i][j] <= mid)
					to[i][j]=to[j][i]=1, ++gs[i], ++gs[j];
		for(int i = 1; i <= n; ++i) 
			aaa+=(gs[i] == n-1);
		for(int i = 1; i <= n; ++i)
			if(gs[i] < m-1)
				for(int j = i+1; j <= n; ++j)
					if(to[i][j])
						to[i][j]=to[j][i]=0, --gs[i], --gs[j];
		if(aaa >= m) {
			r=mid-1, ans=mid;
			continue;
		}
		pd = 0;
		for(int i = 1; i <= 1000; ++i)
			if(check()) {
				pd=1;
				break;
			}
		if(pd) r=mid-1, ans=mid;
		else l=mid+1;
	}
	printf("%.6lf", sqrt(ans));
	return 0;
}
