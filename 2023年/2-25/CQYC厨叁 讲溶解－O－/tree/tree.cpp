#include <bits/stdc++.h>
#define uLL unsigned long long
using namespace std;
const uLL inmyhead = 10007;
int t, n, u[10005], v[10005], gs[2], ds[10005], dp[2][10005];
char s[10005];
vector <int> to[10005];
unordered_map <uLL, int> NASA;
int dfs(int x, int now) {//now为1则C先,为0则R先,返回值为1则先手必胜,值为0则先手必输 
	if(x == 3) {
		int c = 0, r = 0;
//		for(int i = 1; i <= n; ++i) 
//			if(ds[i] != 0) cout<<i<<" "<<s[i]<<" "<<ds[i]<<"\n";
		for(int i = 1; i <= n; ++i) {
			if(ds[i] == 2) {
				if((s[i] == 'C' ? 1 : 0) != now)
					return 0;
			}
			if(ds[i] == 1)
				if(s[i] == 'C') ++c;
				else ++r;
		}
//		cout<<c<<" "<<r<<"!?\n\n";
		if(now == 1 && c == 0) return 0;
		if(now == 0 && r == 0) return 0;
		return 1;
	}
	int ret = 0;
	for(int i = 1; i <= n; ++i)
		if(ds[i] == 1) {
			--ds[i];
			int o = 0;
			for(int j = 0; j < to[i].size(); ++j)
				if(ds[to[i][j]] >= 1)
					o=to[i][j];
			--ds[o];
			ret|=((dfs(x-1, now^1))^1);
			++ds[i];
			++ds[o];
			if(ret == 1) return 1;
		}
	return 0;
}
int needy(int x, int now) {//now为1则C先,为0则R先,返回值为1则先手必胜,值为0则先手必输 
	uLL thankunext = 0;
	for(int i = 1; i <= n; ++i)
		thankunext=thankunext*inmyhead+ds[i]+1;
	if(NASA.find(thankunext) != NASA.end()) return NASA[thankunext];
	int& ret = NASA[thankunext];
	if(x == 3) {
		int c = 0, r = 0;
//		for(int i = 1; i <= n; ++i) 
//			if(ds[i] != 0) cout<<i<<" "<<s[i]<<" "<<ds[i]<<"\n";
		for(int i = 1; i <= n; ++i) {
			if(ds[i] == 2) {
				if((s[i] == 'C' ? 1 : 0) != now)
					return (ret = 0);
			}
			if(ds[i] == 1)
				if(s[i] == 'C') ++c;
				else ++r;
		}
//		cout<<c<<" "<<r<<"!?\n\n";
		if(now == 1 && c == 0) return (ret = 0);
		if(now == 0 && r == 0) return (ret = 0);
		return (ret = 1);
	}
	ret=0;
	for(int i = 1; i <= n; ++i)
		if(ds[i] == 1) {
			--ds[i];
			int o = 0;
			for(int j = 0; j < to[i].size(); ++j)
				if(ds[to[i][j]] >= 1)
					o=to[i][j];
			--ds[o];
			ret|=((needy(x-1, now^1))^1);
			++ds[i];
			++ds[o];
			if(ret == 1) return (ret = 1);
		}
	return (ret = 0);
}
int main() {
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	scanf("%d", &t);
	while(t--) {
		scanf("%d\n%s", &n, s+1);
		if(n == 1) {
			puts((s[1] == 'C' ? "Clash" : "Royale"));
			continue;
		}
		int pd1 = 1, pd2 = 1;
		for(int i = 1; i <= n-1; ++i) {
			scanf("%d%d", &u[i], &v[i]);
			if(min(u[i], v[i]) != 1) pd1=0;
			if(abs(u[i]-v[i]) != 1) pd2=0;
		}
		if(n == 2) {
			if(s[1] == s[2]) {
				puts((s[1] == 'C' ? "Clash" : "Royale"));
				continue;
			}
			puts("Clash");
			continue;
		}
		if(pd1) {
			if(n%2 != (s[1] == 'C' ? 1 : 0)) {
				puts((s[1] == 'C' ? "Clash" : "Royale"));
				continue;
			}
			gs[0]=gs[1]=0;
			for(int i = 2; i <= n; ++i)
				++gs[(s[i] == 'C' ? 0 : 1)];
			int c=gs[0]-(n-3)/2, r=gs[1]-(n-2)/2;
//			cout<<s[1]<<" "<<c<<" "<<r<<"\n";
			if(n%2 == 1) {
				if(s[1] == 'C' && c == 0)
					puts("Royale");
				else
					puts("Clash");
				continue;
			}
			else {
				if(s[1] == 'R' && r == 0)
					puts("Clash");
				else
					puts("Royale");
				continue;
			} 
		}
		if(pd2) {
			for(int i = 1; i+2 <= n; ++i) {
				int c = 0, r = 0;
				dp[0][i] = 0;
				if((s[i+1] == 'C' ? 1 : 0) != n%2)
					dp[0][i]=0;
				else {
					if(s[i] == 'C') ++c;
					else ++r;
					if(s[i+2] == 'C') ++c;
					else ++r;
					if(n%2 == 1 && c == 0) dp[0][i] = 0;
					else if(n%2 == 0 && r == 0) dp[0][i] = 0;
					else dp[0][i] = 1;
				}
			}
			int ooo=1;
			for(int len = 4; len <= n; ++len, ooo^=1) {
				for(int i = 1; i+len-1 <= n; ++i)
					dp[ooo][i]=0;
				for(int i = 1; i+len-1 <= n; ++i)
					dp[ooo][i]|=(dp[ooo^1][i]^1), dp[ooo][i]|=(dp[ooo^1][i+1]^1);
			}
			ooo^=1;
			puts((dp[ooo][1] == 1 ? "Clash" : "Royale"));
			continue;
		}
		if(n <= 1) {
			for(int i = 1; i <= n; ++i)
				to[i].clear(), ds[i]=0;
			for(int i = 1; i <= n-1; ++i)
				to[u[i]].push_back(v[i]), to[v[i]].push_back(u[i]), 
				++ds[u[i]], ++ds[v[i]];
			int qwq = dfs(n, 1); 
			if(qwq) 
				puts("Clash");
			else
				puts("Royale");
			continue;
		}
		else {
			NASA.clear();//哈哈哈哈哈哈哈哈哈哈哈哈,记搜记搜MLEMLEMLEMLE哈哈哈哈哈哈哈哈哈哈哈太开心啦哈哈哈哈哈哈哈哈哈哈哈哈哈 
			for(int i = 1; i <= n; ++i)
				to[i].clear(), ds[i]=0;
			for(int i = 1; i <= n-1; ++i)
				to[u[i]].push_back(v[i]), to[v[i]].push_back(u[i]), 
				++ds[u[i]], ++ds[v[i]];
			int qwq = needy(n, 1); 
			if(qwq) 
				puts("Clash");
			else
				puts("Royale");
			continue;
		}
	}
	return 0;
} 
