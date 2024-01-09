#include <bits/stdc++.h>
using namespace std;
int t, n, a[1005][4], dp[5][255][255], lst[5][255][255];

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

int main() {
    read(t);
    while(t--) {
        read(n);
        for(int i = 0; i < n; ++i)
            read(a[i][0]), read(a[i][1]), read(a[i][2]);
        memset(dp,0,sizeof(dp));
        int l = min(250, n);
        for(int i = 0; i < n; ++i) {
            memcpy(lst,dp,sizeof(dp));
		    memset(dp,0,sizeof(dp));
            for(int o = 0; o <= 2; ++o) 
                for(int p = max(0, i-l); p <= i; ++p)
                    for(int q = max(0, i-l); q <= i; ++q) {
                        int u = i-p ? i-p+1 : 0, v = i-q ? i-q+1 : 0;
                        dp[0][u][v]=max(dp[0][u][v], lst[0][i-p][i-q]+a[i][0]);
                        dp[1][1][v]=max(dp[1][1][v], lst[0][i-p][i-q]+a[i][1]);
                        dp[2][1][u]=max(dp[2][1][u], lst[0][i-p][i-q]+a[i][2]);
                        dp[0][1][v]=max(dp[0][1][v], lst[1][i-p][i-q]+a[i][0]);
                        dp[1][u][v]=max(dp[1][u][v], lst[1][i-p][i-q]+a[i][1]);
                        dp[2][u][1]=max(dp[2][u][1], lst[1][i-p][i-q]+a[i][2]);
                        dp[0][v][1]=max(dp[0][v][1], lst[2][i-p][i-q]+a[i][0]);
                        dp[1][u][1]=max(dp[1][u][1], lst[2][i-p][i-q]+a[i][1]);
                        dp[2][u][v]=max(dp[2][u][v], lst[2][i-p][i-q]+a[i][2]);
                    }
            for(int o = 0; o <= 2; ++o) 
                for(int p = 0; p <= l; ++p)
                    for(int q = 0; q <= l; ++q) 
                        dp[o][p][q]-=p+q;
        }
        int ans = 0;
        for(int i = 0; i <= 2; ++i)
            for(int q = 0; q <= l; ++q)
                for(int p = 0; p <= l; ++p)
                    ans=max(dp[i][p][q], ans);
        write(ans), putchar('\n');
    }
	return 0;
}
