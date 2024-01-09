#include <bits/stdc++.h>
#define inf 1000000007
using namespace std;
int n, m, bj, vis[65], zt[65][2], dp[65][65][65];
char l[65], q, r[65];
int get(char A) {
	if('A' <= A && A <= 'Z') return A-'A'+1;
	if('a' <= A && A <= 'z') return A-'a'+27;
	return A-'0'+53;
}
int dfs(int a, int b, int c) {
	if(a+b+c == 0) return -inf;
	if(dp[a][b][c] >= 0) return dp[a][b][c];
	int ret=inf;
	for(int a1 = 0; a1 <= a; ++a1)
		for(int a2 = 0; a2 <= a-a1; ++a2)
			if(a2 <= a1)
				for(int b1 = 0; b1 <= b; ++b1)
					for(int b2 = 0; b2 <= b-b1; ++b2)
						for(int c1 = 0; c1 <= c; ++c1)
							for(int c2 = 0; c2 <= c-c1; ++c2) {
								if(n-a-b-c < abs(a1+b1+c1-a2-b2-c2) || (a1+b1+c1 == 0 && a2+b2+c2 == 0))
									continue;
								int az = -inf;
								if(a-a1-a2 != a || b-b1-b2 != b || c-c1-c2 != c)
									az=max(az, dfs(a-a1-a2, b-b1-b2, c-c1-c2));
								if(a != 0 || b2+a2 != b || c1+a1 != c)
									az=max(az, dfs(0, b2+a2, c1+a1));
								if(a != 0 || b1+a1 != b || c2+a2 != c)
									az=max(az, dfs(0, b1+a1, c2+a2));
								if(az >= 0) ret=min(ret, az+1);
							}
	dp[a][b][c]=dp[a][c][b]=ret;
	return ret; 
}
int main() {
	freopen("coin.in", "r", stdin);
	freopen("coin.out", "w", stdout);
	scanf("%d%d", &n, &m);
	memset(dp, 0xc0, sizeof dp);
	dp[0][1][0]=dp[0][0][1]=0, dp[1][0][0]=1;
	for(int i = 1; i <= m; ++i) {
		scanf("%s %c %s", l+1, &q, r+1);
		int len = strlen(l+1);
		if(q != '=') {
			for(int i = 1; i <= n; ++i)
				vis[i]=0;
			for(int i = 1; i <= len; ++i)
				vis[get(l[i])]=1, vis[get(r[i])]=1;
			for(int i = 1; i <= n; ++i)
				if(!vis[i])
					zt[i][0]=zt[i][1]=1;
		}
		for(int i = 1; i <= len; ++i) {
			if(q == '=')
				zt[get(l[i])][0]=zt[get(l[i])][1]=1, zt[get(r[i])][0]=zt[get(r[i])][1]=1;
			if(q == '<')
				zt[get(l[i])][0]=1, zt[get(r[i])][1]=1;
			if(q == '>')
				zt[get(l[i])][1]=1, zt[get(r[i])][0]=1;
		}
	}
	int a=0, b=0, c=0;
	for(int i = 1; i <= n; ++i)
		if(!zt[i][0] && !zt[i][1])
			++a;
		else
			if(!zt[i][1])
				++b;
			else
				if(!zt[i][0])
					++c;
//	cout<<a<<" "<<b<<" "<<c<<"\n";
	printf("%d\n", dfs(a, b, c));
	return 0;
}
