#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
typedef tuple<int, int, long long> tiii;
typedef pair<int, long long> pii;
const int len = 575, N = 3e5+500;
const long long inf = 1e15;
int n, q, pro, k, s[N], cnt, l, r, nr[N];
long long lasans, w, dp[N], ky[(N>>9)+5][(N>>9)+5], dis[(N>>9)+5][(N>>9)+5], wm1[N], wm2[N];
vector <tiii> ll[(N>>9)+5], rr[(N>>9)+5];
vector <pii> rs[N+5];
template <typename T> 
void read(T& x) {
	x=0; char c=getchar(); while(c < '0' || c > '9') c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
}
char put[64];
template <typename T> 
void write(T x, int lens = 0) {
    do {put[++lens]=x%10, x=x/10;} while(x);
    while(lens) putchar(put[lens--]^48);
}
struct Solve1 {
	void update(int x, int y, long long z) {
		int lz = (x>>9), rz=(y>>9);
		ll[lz].insert(lower_bound(ll[lz].begin(), ll[lz].end(), tiii{x, y, z}, [](tiii i, tiii j) {
			return get<1>(i) > get<1>(j);//∞¥r≈≈–Ú 
		}), tiii{x, y, z});
		rr[rz].insert(lower_bound(rr[rz].begin(), rr[rz].end(), tiii{x, y, z}, [](tiii i, tiii j) {
			return get<0>(i) < get<0>(j);//∞¥l≈≈–Ú 
		}), tiii{x, y, z});
		for(int i = lz; i <= rz; ++i)
			ky[lz][i]=min(ky[lz][i], z);
	}
	long long ans() {
		for(int i = 1; i <= k; ++i) {
			dp[i]=inf;
			for(int j = 1; j <= k; ++j)
				dis[i][j]=inf;
		}
		for(int i = 1; i <= k; ++i) {
			long long wm = inf; int j = k;
			for(auto qwq : ll[(s[i]>>9)]) {
				int lll, rrr, www;
				tie(lll, rrr, www) = qwq;
				while(j >= i && s[j] > rrr)
					dis[i][j]=min(dis[i][j], wm), --j;
				if(j < i) break;
				if(lll <= s[i] && www < wm) wm=www;
			}
			while(j >= i)
				dis[i][j]=min(dis[i][j], wm), --j;
			
			wm = inf, j = 1;
			for(auto qwq : rr[(s[i]>>9)]) {
				int lll, rrr, www;
				tie(lll, rrr, www) = qwq;
				while(j <= i && s[j] < lll)
					dis[j][i]=min(dis[j][i], wm), ++j;
				if(j > i) break;
				if(s[i] <= rrr && www < wm) wm=www;
			}
			while(j <= i)
				dis[j][i]=min(dis[j][i], wm), ++j;
		}
		for(int i = 1; i <= k; ++i) {
			long long wm = inf; int rz = (s[i]>>9)+1, lz = 0;
			for(int j = 1; j <= i; ++j) {
				while(lz < (s[j]>>9))
					wm=min(wm, ky[lz][rz]), ++lz;
				wm=min(wm, dis[j][i]);
				dp[i]=min(dp[i], dp[j-1]+wm);
			}
		}
		return dp[k];
	}
}A;
struct Solve2 {
	int lent;
	void update(int x, long long www) {
		for(int i = (x>>lent)-1; i >= 0; --i)
			wm2[i]=min(wm2[i], www);
		for(int i = ((x>>lent)<<lent); i <= x; ++i)
			wm1[i]=min(wm1[i], www);
	}
	long long fnd(int x) {
		return min(wm1[x], wm2[(x>>lent)]);
	}
	long long ans() {
		lent=1;
		while((1<<(lent<<1)) < k) ++lent;
		memset(wm2, 0x3f, sizeof wm2);
		memset(wm1, 0x3f, sizeof wm1);
		memset(nr, 0, sizeof nr);
		update(1, 0);
		nr[n+1]=k+1;
		for(int i = 1; i <= k; ++i)
			nr[s[i]]=i;
		for(int i = n; i >= 1; --i)
			if(!nr[i]) nr[i]=nr[i+1];
		for(int rrr = s[1], i = 1; i <= k; ++i) {
			long long an = inf;
			while((i == k || rrr < s[i+1]) && rrr <= n) {
				for(auto qwq : rs[rrr])
					an=min(an, fnd(nr[qwq.first])+qwq.second);
				++rrr;
			}
			if(i == k) return an;
			if(an <= 9e14) update(i+1, an);
		}
		return 0;
	}
}B;
int main() {
	freopen("chaos.in", "r", stdin);
	freopen("chaos.out", "w", stdout);
	read(n), read(q);
	for(int i = 0; i <= (n>>9)+1; ++i)
		for(int j = 0; j <= (n>>9)+1; ++j)
			ky[i][j]=inf;
	while(q--) {
		read(pro);
		lasans%=mod;
		if(pro == 1) {
			++cnt;
			read(l), read(r), read(w);
			l^=lasans, r^=lasans;
			rs[r].push_back(pii{l, w});
			A.update(l, r, w);
		}
		else {
			read(k);
			for(int i = 1; i <= k; ++i) read(s[i]), s[i]^=lasans;
			if(cnt == 0) {
				puts("0");
				continue;
			} 
			sort(s+1, s+1+k);
			if(k <= len) lasans=A.ans();
			else lasans=B.ans();
			if(lasans > 9e14) lasans=0;
			write(lasans), putchar('\n');
		}
	}
	return 0;
} 
