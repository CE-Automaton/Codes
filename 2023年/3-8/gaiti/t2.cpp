#include <bits/stdc++.h>
#define tplt template <typename T>
using namespace std;
const int N = 2e5+5, B = 4050;
int n, m, a, b, cc, op, xx, yy, fa[N], len[N], bg[N], vis[N], pd[N], tot;
unordered_map<int, long long> ans[N];
unordered_set<int> s[N];
unordered_map<int, int> t[N];

tplt inline void read(T& x) {
	x=0; char c=getchar(); while(c < '0' || c > '9') c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
}
int lne; char put[105]; 
tplt inline void write(T x) {
	lne=0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
}
int find(int x) {
	return (x == fa[x] ? x : fa[x]=find(fa[x]));
}
inline void updt(int qwq) {
	for(int i = 1; i <= tot; ++i) {
		if(vis[i] || i == qwq) continue;
		long long sum = 0;
        int aa = i, bb = qwq;
		if(t[aa].size() > t[bb].size()) swap(aa, bb);
		for(auto it : t[aa]) {
			if(t[bb].count(it.first) == 0) continue;
			if(a == 0)
				++sum;
			else
				sum+=1LL*it.first;
		}
		if(b == 0)
			sum=(sum == 0 ? 0 : 1);
		ans[i][qwq]=sum;
		ans[qwq][i]=sum;
	}
}
inline void upd(int xxx, int yyy) {
	for(int o = 1; o <= tot; ++o) {
		if(vis[o] || o == bg[xxx]) continue;
		if(t[o].count(yyy) == 0) continue;
		long long ooo = ans[o][bg[xxx]];
		if(a == 0) 
			++ooo;
		else
			ooo+=1LL*yyy;
		if(b == 0)
			ooo=(ooo == 0 ? 0 : 1);
		ans[o][bg[xxx]]=ans[bg[xxx]][o]=ooo;
	}
}

signed main() {
	freopen("plasticmemories.in", "r", stdin);
	freopen("plasticmemories.out", "w", stdout);
	read(n), read(m), read(a), read(b);
	for(int i = 1; i <= n; ++i) 
		read(cc), s[i].insert(cc), fa[i]=i, len[i]=1;
	for(int i = 1; i <= m; ++i) {
		read(op), read(xx), read(yy);
		if(op == 1) {
			xx=find(xx);
			if(bg[xx]) {
				t[bg[xx]][yy]=1;
				if(len[xx] != t[bg[xx]].size()) {
					len[xx]=t[bg[xx]].size();
					upd(xx, yy); 
				}
			}
			else {
				s[xx].insert(yy);
				len[xx]=s[xx].size();
				if(len[xx] == B) {
					bg[xx]=++tot;
					for(auto it : s[xx])
						t[tot][it]=1;
					updt(tot);
				}
			}
		}
		if(op == 2) {
			xx=find(xx), yy=find(yy);
			if(len[xx] > len[yy]) swap(xx, yy);
			fa[xx]=yy;
			if(bg[xx]) {
				vis[bg[xx]]=1;
				for(auto it : t[bg[xx]]) {
					if(t[bg[yy]].count(it.first) != 0) continue;
					t[bg[yy]][it.first]=1;
					upd(yy, it.first);
				}
				len[yy]=t[bg[yy]].size();
			}
			else {
				if(bg[yy]) {
					for(auto it : s[xx]) {
						if(t[bg[yy]].count(it) != 0) continue;
						t[bg[yy]][it]=1;
						upd(yy, it);
					}
					len[yy]=t[bg[yy]].size();
				}
				else {
					for(auto it : s[xx])
						s[yy].insert(it);
					len[yy]=s[yy].size();
					if(len[yy] >= B) {
						bg[yy]=++tot;
						for(auto it : s[yy])
							t[tot][it]=1;
						updt(tot);
					}
				}
			}
		}
		if(op == 3) {
			xx=find(xx), yy=find(yy);
			if(bg[xx] && bg[yy]) {
				write(ans[bg[xx]][bg[yy]]);
				putchar('\n');
			}
			else
				if(bg[xx]) {
					long long sum = 0;
					for(auto it : s[yy]) {
						if(t[bg[xx]].count(it) == 0) continue;
						if(a == 0) ++sum;
						else sum+=1LL*it;
					}
					if(b == 0)
						sum=(sum == 0 ? 0 : 1);
					write(sum);
					putchar('\n');
					continue;
				}
				else
					if(bg[yy]) {
						long long sum = 0;
						for(auto it : s[xx]) {
							if(t[bg[yy]].count(it) == 0) continue;
							if(a == 0) ++sum;
							else sum+=1LL*it;
						}
						if(b == 0)
							sum=(sum == 0 ? 0 : 1);
						write(sum);
						putchar('\n');
						continue;
					}
					else {
						long long sum = 0;
						for(auto it : s[yy]) 
							pd[it]=1;
						for(auto it : s[xx]) {
							if(pd[it] == 0) continue;
							if(a == 0) ++sum;
							else sum+=1LL*it;
						}
						for(auto it : s[yy]) 
							pd[it]=0;
						if(b == 0)
							sum=(sum == 0 ? 0 : 1);
						write(sum);
						putchar('\n');
						continue;
					}
		}
	}
	return 0;
}
