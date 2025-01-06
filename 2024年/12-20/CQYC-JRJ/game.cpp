#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
// bool st;
const int N = 1e5+5;
int T, n, gs, kk[N], rt[75], now[75], bk[75][75], mxk;
LL ll[N], rr[N];
struct qwq { LL a, b; };
vector <qwq> dl[35];
struct node {
	int vis[2];
}tr[N*900];

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
void add(int x, LL w) {
	for(int i = 0; i <= 62; ++i) {
		int &to = tr[x].vis[(w>>i)&1];
		if(!to) to=++gs, tr[gs].vis[0]=tr[gs].vis[1]=0;
		x=to;
	}
}
int dfs(int x) {
	if(!tr[x].vis[0] || !tr[x].vis[1]) return 1;
	if(dfs(tr[x].vis[0])^1)
		return 1;
	return (dfs(tr[x].vis[1])^1);
}
int ddfs(int dep) {
	int pd0 = 1, pd1 = 1;
	for(int i = 0; i <= dep; ++i)
		pd0&=(now[i] == 0 || tr[now[i]].vis[0] == 0), pd1&=(now[i] == 0 || tr[now[i]].vis[1] == 0);
	// debug(dep, mxk, pd0, pd1, "???\n");
	if(dep > mxk && (pd0 || pd1)) return 1;
	for(int i = 0; i <= dep; ++i)
		bk[dep][i]=now[i], now[i]=tr[now[i]].vis[0];
	if(ddfs(dep+1)^1) {
		for(int i = 0; i <= dep; ++i)
			now[i]=bk[dep][i];
		return 1;
	}
	for(int i = 0; i <= dep; ++i)
		bk[dep][i]=now[i], now[i]=tr[now[i]].vis[1];
	if(ddfs(dep+1)^1) {
		for(int i = 0; i <= dep; ++i)
			now[i]=bk[dep][i];
		return 1;
	}
	return 0;
}
int find(LL w, int dep) {
	for(int i = 1; i <= n; ++i) {
		if(w > rr[i]) continue;
		LL pp = ((ll[i]-w+(1LL<<dep)-1)>>dep);
		pp=(pp<<dep)+w;
		if(pp <= rr[i])
			return 1;
	}
	return 0;
}
int dddfs(LL w, int dep) {
	if(!find(w, dep+1) || !find(w+(1LL<<dep), dep+1))
		return 1;
	if(dddfs(w, dep+1)^1)
		return 1;
	else
		return (dddfs(w+(1LL<<dep), dep+1)^1);
}
// bool fn;
signed main() {
	File("game");
	// debug("Memory:", (double) (&st-&fn)*1.0/1024/1024, "MB!\n");
	read(T);
	while(T--) {
		read(n);
		gs=0;
		int pd = (n <= 100), pdd = 1, pddd = 1;
		for(int i = 1; i <= n; ++i) {
			read(ll[i]), read(rr[i]);
			pd&=(rr[i] <= 100000);
			pdd&=(ll[i] == rr[i]);
			int j = 0;
			for(j = 62; j >= 0; --j)
				if(((ll[i]>>j)&1)^((rr[i]>>j)&1))
					break;
			kk[i]=j;
			for(; j >= 0; --j)
				pddd&=(!((ll[i]>>j)&1)), 
				pddd&=((rr[i]>>j)&1);
		}
		if(pd || pdd) {
			for(int i = 1; i <= n; ++i) 
				for(LL j = ll[i]; j <= rr[i]; ++j)
					add(0, j);
			if(dfs(0))
				putchar('M');
			else
				putchar('N');
			continue;
		}
		if(pddd) {//不知道能不能过这个sub。。。
			// debug("!!!\n");
			for(int i = 0; i <= 62; ++i)
				rt[i]=++gs, now[i]=rt[i];
			mxk=-1;
			for(int i = 1; i <= n; ++i) 
				add(rt[kk[i]+1], (ll[i]>>(kk[i]+1))), 
				mxk=max(mxk, kk[i]);
			tr[0].vis[0]=tr[0].vis[1]=0;
			if(ddfs(0))
				putchar('M');
			else
				putchar('N');
			continue;
		}
		if(dddfs(0, 0))//看能不能拿点分
			putchar('M');
		else
			putchar('N');
	}
	return 0;
}