#include <bits/stdc++.h>
using namespace std;
int n, m, b[5], to[5], ans[1005][1005];
char pro[100005];
struct qwq {
	int c[5];
}a[1005][1005];
int main() {
	freopen("mat.in", "r", stdin);
	freopen("mat.out", "w", stdout); 
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			scanf("%d", &a[i][j].c[3]), a[i][j].c[1]=i, a[i][j].c[2]=j;
	to[1]=1, to[2]=2, to[3]=3;
	scanf("%s", pro+1);
	for(int i = 1; i <= m; ++i) {
		if(pro[i] == 'R') 
			++b[to[2]];
		else if(pro[i] == 'L')
			--b[to[2]];
		else if(pro[i] == 'D')
			++b[to[1]];
		else if(pro[i] == 'U')
			--b[to[1]];
		else if(pro[i] == 'I') 
			swap(to[2], to[3]);
		else if(pro[i] == 'C')
			swap(to[1], to[3]);
	}
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j) {
			for(int o = 1; o <= 3; ++o) {
				if(b[o] == 0) continue;
				a[i][j].c[o]=(a[i][j].c[o]%n+b[o]-1+100000*n/*防止变成负数哈哈哈*/)%n+1;
			}
			ans[a[i][j].c[to[1]]][a[i][j].c[to[2]]]=a[i][j].c[to[3]];
		}
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) 
			printf("%d ", ans[i][j]);
		putchar('\n');
	}
	return 0;
} 
