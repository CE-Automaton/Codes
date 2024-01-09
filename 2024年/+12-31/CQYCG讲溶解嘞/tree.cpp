#include <bits/stdc++.h>
using namespace std;
int n, az[15], fa[15], ww[15], vis[15], ans;
struct qwq {
    int u, v;
}a[15];

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
int find(int x) {
    return (fa[x] == x ? x : fa[x]=find(fa[x]));
}
void dfs(int xx) {
    if(xx == n+1) {
        if(ww[find(1)] == 1)
            ans^=1;
        return ;
    }
    int aa[15], bb[15];
    for(int i = 1; i <= n; ++i)
        aa[i]=fa[i], bb[i]=ww[i];
    for(int i = 2; i <= n; ++i)
        if(!vis[i]) {
            vis[i]=1;
            int x = find(a[i].u), y = find(a[i].v);
            ww[x]=(!(ww[x]&ww[y]));
            fa[y]=x;
            dfs(xx+1);
            vis[i]=0;
            for(int j = 1; j <= n; ++j)
                fa[j]=aa[j], ww[j]=bb[j];
        }
}

signed main() {
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
    read(n);
    for(int i = 2; i <= n; ++i)
        read(a[i].u), read(a[i].v);
    for(int i = 1; i <= n; ++i)
        read(ww[i]), fa[i]=i;
    dfs(2);
    write(ans, '\n');
	return 0;
}