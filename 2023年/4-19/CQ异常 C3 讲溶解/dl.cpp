#include <bits/stdc++.h>
#define inf 1000000007
using namespace std;
int n, k, vis[2005], ans=inf, dp[4005][2];
struct peo {
	int l, r;
}az[2005], bb[4005]; 

template <typename T> void read(T& x) {
	x = 0; int f = 0; char c = getchar();
	while(c < '0' || c > '9') f |= (c == '-'), c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x);
}
int lne; char put[105];
template <typename T> void write(T x, char ch) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
	putchar(ch);
}
int comp(peo A, peo B) {
	return A.l < B.l;
}
void check() {
	for(int i = 1; i <= 2*n; ++i)
		dp[i][0/*关着*/]=dp[i][1/*开着*/]=inf;
	dp[1][0]=dp[1][1]=0;
	for(int i = 1; i <= 2*n-1; ++i) {
		int j = bb[i].r;
		if(az[j].l == i) {
			if(vis[j]) {
				dp[i+1][0]=min(dp[i+1][0], min(dp[i][0], dp[i][1]));
				dp[i+1][1]=min(dp[i+1][1], min(dp[i][0], dp[i][1])+bb[i+1].l-bb[i].l);
			} 
			else {
				dp[i+1][1]=min(dp[i+1][1], min(dp[i][1], dp[i][0])+bb[i+1].l-bb[i].l);
			} 
		}
		else {
			if(vis[j]) {
				dp[i+1][0]=min(dp[i+1][0], min(dp[i][0], dp[i][1]));
				dp[i+1][1]=min(dp[i+1][1], min(dp[i][0], dp[i][1])+bb[i+1].l-bb[i].l);
			} 
			else {
				dp[i+1][0]=min(dp[i+1][0], dp[i][1]);
				dp[i+1][1]=min(dp[i+1][1], dp[i][1]+bb[i+1].l-bb[i].l);
			} 
		}
	}
	int j = bb[2*n].r;
	if(vis[j])
		ans=min(ans, min(dp[2*n][0], dp[2*n][1]));
	else
		ans=min(ans, dp[2*n][1]);
}
void dfs(int x, int s) {
	if(n-x+1 < s) return ;
	if(s == 0) {
		check();
		return ;
	}
	dfs(x+1, s);
	vis[x]=1;
	dfs(x+1, s-1);
	vis[x]=0;
}

signed main() {
	freopen("dl.in", "r", stdin);
	freopen("dl.out", "w", stdout);
	read(n), read(k);
	for(int i = 1; i <= n; ++i)
		read(az[i].l), read(az[i].r), bb[i*2-1]=(peo) {az[i].l, i}, bb[i*2]=(peo) {az[i].r, i};
	sort(bb+1, bb+1+2*n, comp);
	for(int i = 1; i <= 2*n; ++i)
		if(az[bb[i].r].l == bb[i].l)
			az[bb[i].r].l=i;
		else
			az[bb[i].r].r=i;
	sort(az+1, az+1+n, comp);
	dfs(1, k);
	write(ans, '\n');
	return 0;
}
