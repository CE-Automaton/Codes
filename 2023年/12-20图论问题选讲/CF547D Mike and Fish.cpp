#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int n, u, v, lst[N], lstt[N], col[N];
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
void dfs(int x, int cc) {
	col[x]=cc;
	for(int y : to[x])
		if(!col[y])
			dfs(y, cc^1);
}

signed main() {
	read(n);
	for(int i = 1; i <= n; ++i) {
		read(u), read(v);
		if(lst[u])
			to[lst[u]].push_back(i), to[i].push_back(lst[u]), lst[u]=0;
		else
			lst[u]=i;
		if(lstt[v])
			to[lstt[v]].push_back(i), to[i].push_back(lstt[v]), lstt[v]=0;
		else
			lstt[v]=i;
	}
	for(int i = 1; i <= n; ++i)
		if(!col[i])
			dfs(i, 2);
	for(int i = 1; i <= n; ++i)
		putchar(col[i] == 2 ? 'r' : 'b');
	return 0;
}
