#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
int n, f, ans[505][505], az[505][505], op[505][505], jc[505], inv[505], siz[505], zhan[505], tot;
vector <int> to[505];

template <typename T> void read(T& x) {
	x = 0; int f = 0; char c = getchar();
	while(c < '0' || c > '9') f |= (c == '-'), c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x);
}
int lne; char put[105];
template <typename T> void write(T x) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
}
void dfs(int x) {
    siz[x]=1;
    ans[1][1]=1LL*ans[1][1]*jc[to[x].size()]%mod;
    for(auto j : to[x]) 
        dfs(j), siz[x]+=siz[j];
}
void solve(int x) {
    tot=0;
    for(auto j : to[x]) 
        zhan[++tot]=j;
    for(int i = 0; i <= n; ++i)
        for(int j = 0; j <= tot; ++j)
            az[i][j]=0;
    for(int i = 1; i <= n-1; ++i)
        az[i+1][0]=1LL*ans[x][i]*inv[tot]%mod;
    for(int i = 1; i <= tot; ++i)
        for(int j = i-1; j >= 0; --j) 
            for(int o = siz[zhan[i]]+1; o <= n; ++o)
                (az[o][j+1]+=1LL*az[o-siz[zhan[i]]][j]*inv[tot-j-1]%mod*(j+1)%mod)%=mod;
    for(int i = 1; i <= tot; ++i) {
        for(int j = tot; j >= 0; --j)
            for(int o = 0; o <= n; ++o)
                op[o][j]=az[o][j];
        for(int j = 0; j <= tot-1; ++j)
            for(int o = 1; o <= n-siz[zhan[i]]; ++o) 
                op[o+siz[zhan[i]]][j+1]=(op[o+siz[zhan[i]]][j+1]-1LL*op[o][j]*inv[tot-j-1]%mod*(j+1)%mod +mod)%mod;
        for(int j = 0; j <= tot; ++j)
            for(int o = 1; o <= n; ++o)
                ans[zhan[i]][o]=(ans[zhan[i]][o]+op[o][j])%mod;
    }
    for(auto j : to[x]) 
        solve(j);
}

int main() {
    freopen("intestine.in", "r", stdin);
    freopen("intestine.out", "w", stdout);
    read(n);
    jc[0]=jc[1]=inv[1]=1;
    for(int i = 2; i <= n; ++i)
        read(f), to[f].push_back(i), inv[i]=1LL*(mod-mod/i)*inv[mod%i]%mod, jc[i]=1LL*jc[i-1]*i%mod;
    ans[1][1]=1;
    dfs(1);
    solve(1);
    for(int i = 1; i <= n; ++i, putchar('\n'))
        for(int j = 1; j <= n; ++j) 
            write(ans[i][j]), putchar(' ');
	return 0;
}