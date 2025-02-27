#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 4e3+5;
int n, m, k, u, v, col[N], pd[N][N], vis[N], dep[N], ans;
vector <int> to[N];
queue <int> q;

template <typename T> inline void debug(T x) { cerr<<x; }
template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
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

signed main() {
	File("stone");
	read(n), read(m), read(k);
	for(int i = 1; i <= n; ++i)
		read(col[i]);
	for(int i = 1; i <= m; ++i) {
		read(u), read(v);
		if(col[u] == col[v])
			to[u].push_back(v), to[v].push_back(u), 
			to[u+n].push_back(v+n), to[v+n].push_back(u+n);
		else
			to[u].push_back(v+n), to[v+n].push_back(u), 
			to[u+n].push_back(v), to[v].push_back(u+n);
	}
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n+n; ++j)
			dep[j]=0;
		dep[i]=1;
		q.push(i);
		while(!q.empty()) {
			int it = q.front(); q.pop();
			// debug(it, "???\n");
			for(int i = 0; i < to[it].size(); ++i)
				if(!dep[to[it][i]]) {
					dep[to[it][i]]=dep[it]+1;
					q.push(to[it][i]);
				}
		}
		for(int j = 1; j <= n; ++j) 
			if(dep[j] && dep[j+n]) {
				--dep[j], --dep[j+n];
				if(abs(dep[j]-dep[j+n]) >= k)
					ans=max(ans, min(dep[j], dep[j+n])+k);
				else 
					ans=max(ans, min(dep[j], dep[j+n])+(abs(dep[j]-dep[j+n])+k)/2);
			}
			else if(dep[j] || dep[j+n])
				ans=max(ans, (dep[j] ? dep[j]+k-1 : dep[j+n]+k-1));
	}
	write(ans, '\n');
	return 0;
}
