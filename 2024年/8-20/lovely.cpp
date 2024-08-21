#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5, M = 2205;
int n, vis[M], cnt, pri[M], tot, ans, viss[N];
LL a, priii[M], ops[N];
vector <LL> hs[N];
unordered_map <LL, int> to, gs;

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
	for(int i = 2; i <= 2153; ++i) {
		if(!vis[i])
			pri[++cnt]=i;
		for(int j = 1; j <= cnt && pri[j] <= 2153/i; ++j) {
			vis[pri[j]*i]=1;
			if(i%pri[j] == 0) break;
		}
	}
	for(int i = 1; i <= cnt; ++i)
		priii[i]=1LL*pri[i]*pri[i]*pri[i];
	read(n);
	int pd = 0;
	ans=n;
	for(int i = 1; i <= n; ++i) {
		read(a);
		LL pp = 1, po = 1, oo = 10000000000LL;
		for(int j = 1; j <= cnt; ++j) {
			while(a%priii[j] == 0)
				a/=priii[j];
			if(a%pri[j] == 0) {
				a/=pri[j], pp=pp*pri[j], po=po*pri[j], oo/=pri[j];
				if(a%pri[j] == 0)
					a/=pri[j], pp=pp*pri[j];
				else 
					po=po*pri[j], oo/=pri[j];
			}
		}
		if(pp == 1 && a == 1) {//最多选1个完全立方数
			if(pd == 1)
				--ans;
			pd=1;
			continue;
		}
		if(oo == 0) po=-1;//补成立方数需要的数过大
		if(to.find(pp) == to.end())
			to[pp]=++tot;
		hs[to[pp]].push_back(a);//此时a最多为两个大质数相乘
		ops[to[pp]]=po;//互补的那一组
	}
	for(int i = 1; i <= tot; ++i) 
		if(!viss[i] && to.find(ops[i]) != to.end()) {
			int j = to[ops[i]];
			// debug(i, j, "???\n");
			viss[j]=viss[i]=1;
			sort(hs[i].begin(), hs[i].end());
			sort(hs[j].begin(), hs[j].end());
			if(i != j) {//挂分10分原因：只含两个大质数相乘或一个大质数时i会等于j,不能重复算！！！
				gs.clear();
				for(int l = 0; l < hs[i].size(); ++l) 
					if(gs.find(hs[i][l]) == gs.end())
						gs[hs[i][l]]=1;
					else
						++gs[hs[i][l]];
				for(int l = 0; l < hs[j].size(); ++l) {
					LL op = (LL) floor(sqrt((double) 1.0*hs[j][l]));
					if(op*op == hs[j][l] && gs.find(op) != gs.end()) {
						int r = l; 
						while(r+1 < hs[j].size() && hs[j][r+1] == hs[j][l])
							++r;
						ans-=min(r-l+1, gs[op]);
						l=r;
						continue;
					}
				}
			}
			gs.clear();
			for(int l = 0; l < hs[j].size(); ++l) 
				if(hs[j][l] != 1)
					if(gs.find(hs[j][l]) == gs.end())
						gs[hs[j][l]]=1;
					else
						++gs[hs[j][l]];
			for(int l = 0; l < hs[i].size(); ++l) {
				LL op = (LL) floor(sqrt((double) 1.0*hs[i][l]));
				if(op*op == hs[i][l] && gs.find(op) != gs.end()) {
					int r = l; 
					while(r+1 < hs[i].size() && hs[i][r+1] == hs[i][l])
						++r;
					ans-=min(r-l+1, gs[op]);
					l=r;
					continue;
				}
			}
		}
	write(ans, '\n');
	return 0;
}