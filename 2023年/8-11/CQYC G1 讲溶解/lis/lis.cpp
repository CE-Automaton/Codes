#include <bits/stdc++.h>
using namespace std;
const int N = 5e5+5;
int n, ans=N, zhan[N], w[N], u, v, pd[N], sum;
vector <int> to[N];

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
void dfs(int x, int fa, int siz) {
	int wz = 0, yb = 0, pdd = 0;
	if(siz == 0 || w[x] > zhan[siz]) {
		zhan[++siz]=x;
		pdd=1;
	}
	else {
		int l = 1, r = siz;
		while(l <= r) {
			int mid = ((l+r)>>1);
			if(zhan[mid] >= w[x])
				wz=mid, r=mid-1;
			else
				l=mid+1;
		}
		yb=zhan[wz];
		zhan[wz]=w[x];
	}
	sum=max(sum, siz);
	for(int y : to[x])
		if(pd[y] == 0 && y != fa)
			dfs(y, x, siz);
	if(pdd)
		zhan[siz]=0;
	else
		zhan[wz]=yb;
}

signed main() {
	freopen("lis.in", "r", stdin);
	freopen("lis.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n-1; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	for(int j = 1; j <= n; ++j) 
		read(w[j]);
	for(int j = 1; j <= n; ++j) {
		pd[j]=1;
		sum=0;
		for(int i = 1; i <= n; ++i)
			if(i != j)
				dfs(i, 0, 0);
		ans=min(ans, sum);
		pd[j]=0;
	}
	write(ans, '\n');
	return 0;
}
