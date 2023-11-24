#include <bits/stdc++.h>
using namespace std;
int n, m, nxt[8005], f[2][8005], ans, now;
char s[8005], t[8005];
int main() {
	scanf("%s\n%s", s+1, t+1);
	n = strlen(s+1), m = strlen(t+1);
	for(int i = 2, j = 0; i <= m; ++i) {
		while(j && t[j+1] != t[i]) j=nxt[j];
		if(t[j+1] == t[i]) ++j; nxt[i]=j;
	}
	for(int i = 1; i <= n; ++i) {
		for(int j = 0; j < m; ++j) f[now^1][j]=-1;
		for(int j = 0; j < m; ++j) {
			if(f[now][j] == -1) continue;
			f[now^1][j]=max(f[now^1][j], f[now][j]);
			int k = j;
			while(k && t[k+1] != s[i]) k=nxt[k];
			if(t[k+1] == s[i]) ++k;
			f[now^1][k]=max(f[now^1][k], 1+f[now][j]);
		}
		now^=1;
	}
	for(int i = 0; i < m; ++i)
		ans=max(ans, f[now][i]);
	printf("%d\n", n-ans);
	return 0;
}
