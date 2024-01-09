#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
int t, n;
struct qwq {
    int a[5];
}az, ad[1005], dp[105][105][105];

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
    freopen("codechef.in", "r", stdin);
    freopen("codechef.out", "w", stdout);
    read(t);
    while(t--) {
        read(n);
        az.a[1]=az.a[2]=az.a[3]=0;
        for(int i = 1; i <= n; ++i)
            read(ad[i].a[1]), read(ad[i].a[2]), read(ad[i].a[3]);
        if(n <= 100) {
            for(int i = 1; i <= n; ++i) {
                dp[0][0][0]=az;
                for(int o = 1; o < i; ++o)
                    for(int p = 1; p < i; ++p)
                        dp[o][p][i].a[1]=dp[o][p][i].a[2]=dp[o][p][i].a[3]=0, 
                        dp[p][i][o].a[1]=dp[p][i][o].a[2]=dp[p][i][o].a[3]=0, 
                        dp[i][o][p].a[1]=dp[i][o][p].a[2]=dp[i][o][p].a[3]=0;
                for(int o = 1; o < i; ++o)
                    for(int p = 1; p < i; ++p)
                        for(int q = 1; q < i; ++q) {
                            if(o != i-1 && p != i-1 && q != i-1) continue;
                            qwq ret=dp[o][p][q];
                            ret.a[1]+=ad[i].a[1];
                            ret.a[2]-=i-p;
                            ret.a[2]=max(ret.a[2], 0);
                            ret.a[3]-=i-q;
                            ret.a[3]=max(ret.a[3], 0);
                            if(ret.a[1]+ret.a[2]+ret.a[3] >= dp[i][p][q].a[1]+dp[i][p][q].a[2]+dp[i][p][q].a[3])
                                dp[i][p][q]=ret;
                            
                            ret=dp[o][p][q];
                            ret.a[1]-=i-o;
                            ret.a[1]=max(ret.a[1], 0);
                            ret.a[2]+=ad[i].a[2];
                            ret.a[3]-=i-q;
                            ret.a[3]=max(ret.a[3], 0);
                            if(ret.a[1]+ret.a[2]+ret.a[3] >= dp[i][p][q].a[1]+dp[i][p][q].a[2]+dp[i][p][q].a[3])
                                dp[i][p][q]=ret;

                            ret=dp[o][p][q];
                            ret.a[1]-=i-o;
                            ret.a[1]=max(ret.a[1], 0);
                            ret.a[2]-=i-p;
                            ret.a[2]=max(ret.a[2], 0);
                            ret.a[3]+=ad[i].a[3];
                            if(ret.a[1]+ret.a[2]+ret.a[3] >= dp[i][p][q].a[1]+dp[i][p][q].a[2]+dp[i][p][q].a[3])
                                dp[i][p][q]=ret;
                        }
            }
            int ans = 0;
            for(int o = 1; o < n; ++o)
                for(int p = 1; p < n; ++p) 
                    ans=max(ans, dp[n][o][p].a[1]+dp[n][o][p].a[2]+dp[n][o][p].a[3]), 
                    ans=max(ans, dp[o][n][p].a[1]+dp[o][n][p].a[2]+dp[o][n][p].a[3]), 
                    ans=max(ans, dp[o][p][n].a[1]+dp[o][p][n].a[2]+dp[o][p][n].a[3]);
            write(ans), putchar('\n');
        }
    }
	return 0;
}