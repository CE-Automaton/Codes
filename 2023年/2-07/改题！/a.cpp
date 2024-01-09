#include <bits/stdc++.h>
using namespace std;
int n, m, v, id[305];
double p[305][305], e[305], P[305], ans;
int comp(int A, int B) {
	return e[A]*P[B] < e[B]*P[A];
}
int main() {
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			scanf("%d", &v), p[j][i]=v/100.0;
	for(int i = 1; i <= m; ++i) {
		sort(p[i]+1, p[i]+1+n);
		P[i]=1, id[i]=i;
		for(int j = 1; j <= n; ++j)
			e[i]+=P[i], P[i]*=p[i][j];
	}
	sort(id+1, id+1+m, comp);
	double lst = 1;
	for(int i = 1; i <= m; ++i)
		ans+=e[id[i]]*lst, lst*=(1-P[id[i]]);
	printf("%.5lf", ans);
	return 0;
}
