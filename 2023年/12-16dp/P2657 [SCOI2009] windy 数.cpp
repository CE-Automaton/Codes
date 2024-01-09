#include <bits/stdc++.h>
using namespace std;
int l, r, pw[15], dp[15][15][2];

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
int ddp(int x, int ret = 0) {
	if(!x) return 0;
	memset(dp, 0, sizeof dp);
	int pd = 0;
	//1表示顶满,0表示随便选
	for(int i = 9; i >= 0; --i) {
		int xx = x/pw[i]%10;
		for(int y = 0; y <= 9; ++y)
			for(int now = 0; now <= 9; ++now)
				if(abs(now-y) >= 2) {
					if(now <= xx)
						dp[i][now][(now == xx)]+=dp[i+1][y][1];
					dp[i][now][0]+=dp[i+1][y][0];
				}
		if(pd) {
			for(int now = 1; now <= 9; ++now)
				dp[i][now][0]+=1;
		}
		else
			if(xx) {
				pd=1;
				for(int now = 1; now <= xx; ++now)
					dp[i][now][(now == xx)]+=1;
			}
	}
	for(int i = 0; i <= 9; ++i)
		ret+=dp[0][i][0]+dp[0][i][1];
	return ret;
}

signed main() {
	pw[0]=1;
	for(int i = 1; i <= 9; ++i)
		pw[i]=pw[i-1]*10;
	read(l), read(r);
	write(ddp(r)-ddp(l-1), '\n');
	return 0;
}
