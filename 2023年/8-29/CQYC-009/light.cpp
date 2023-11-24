#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N = 405;
int n, u, v, pd[N], vis[N], zhan[N];
long long ans, a[N], b[N];
vector <int> to[N];

char buf[(1<<21)+5],*p1,*p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
template <typename T> void read(T& x) {
	x = 0; int f = 0; char c = getchar();
	while(!isdigit(c)) f |= (c == '-'), c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x);
}
int lne; char put[105];
template <typename T> void write(T x, char ch) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
	putchar(ch);
}
void dfs(int x) {
	if(x == n+1) {
		for(int i = 1; i <= n; ++i)
			vis[i]=b[i]=0;
		long long sum = 0;
		for(int o = 1; o <= n; ++o) {
			int i = zhan[o];
			sum+=a[i]+b[i];
			for(int j : to[i])
				if(vis[j] == 0)
					b[j]+=a[i]+b[i];
		}
		ans=max(sum, ans);
		return ;
	}
	for(int i = 1; i <= n; ++i) 
		if(pd[i] == 0) {
			zhan[x]=i;
			pd[i]=1;
			dfs(x+1);
			pd[i]=0;
		}
}

signed main() {
	freopen("light.in", "r", stdin);
	freopen("light.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	dfs(1);
	write(ans, '\n');
	return 0;
}
