#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5+5;
int n, l, typ, dp[200005], pp[3005][15], p[15], anss[3005];
struct qwq {
    int a, b;
}c[N];

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
void add(int x, int y, int a) {
    for(int i = 0; i <= 10; ++i)
        p[i]=pp[y][i];
    for(int j = 10; j >= 0; --j)
        if((1LL<<j)&a)
            if(p[j]) a^=p[j];
            else { p[j]=a; break; }
    int ans = 0;
    for(int j = 10; j >= 0; --j)
		if((p[j]^ans) > ans) 
            ans=(ans^p[j]);
    if(ans > anss[x]) {
        for(int i = 0; i <= 10; ++i)
            pp[x][i]=p[i];
        anss[x]=ans;
    }
}

signed main() {
	freopen("chain.in", "r", stdin);
	freopen("chain.out", "w", stdout);
    read(n), read(l), read(typ);
    for(int i = 1; i <= n; ++i)
        read(c[i].a), read(c[i].b);
    if(typ == 0) {
        for(int i = 1; i <= n; ++i) 
            for(int j = (1<<10)-1; j >= 0; --j)
                dp[j|c[i].a]=max(dp[j|c[i].a], dp[j]+c[i].b);
        int ans = 0;
        for(int j = l; j >= 0; --j)
            ans=max(ans, dp[j]);
        write(ans, '\n');
    }
    else {
        int ans = 0;
        for(int i = 1; i <= n; ++i) {
            for(int j = (1<<10)-1; j >= 0; --j) 
                add(j|c[i].a, j, c[i].b);
            for(int j = l; j >= 0; --j)
                ans=max(ans, anss[j]);
        }
        for(int j = l; j >= 0; --j)
            ans=max(ans, anss[j]);
        write(ans, '\n');
    }
	return 0;
}