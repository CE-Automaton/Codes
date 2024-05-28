#include <bits/stdc++.h>
#define inf 1000000000000000LL
#define int __int128
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e5+5;
int dd, n, t, s[N], siz[N], ss, u, v, w, ww, dp[N], ans, sum, tot, cnt, q[N];
struct qwq {
	int d, w1, w2;
}zhan[N];
struct qwqq {
	int w1, w2;
}ha[N];
vector <qwq> to[N];

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
int comp(qwqq A, qwqq B) {
	if(A.w1 == B.w1) return A.w2 < B.w2;
	return A.w1 < B.w1;
}
bool eqn(qwqq a, qwqq b) {
	return (a.w1 == b.w1);
}
inline __float128 slope(qwqq a, qwqq b) {
	return ((__float128)(b.w2 - a.w2) / (__float128)(b.w1 - a.w1));
}
void dfs(int x, int fa, int www) {
	int mx = 0;
	for(qwq y : to[x]) 
		if(y.d != fa) {
			dfs(y.d, x, y.w1-y.w2-t);
			siz[x]+=siz[y.d];
		}
	for(qwq y : to[x]) 
		if(y.d != fa) 
			mx=max(mx, t*siz[y.d]*(ss-siz[x])+dp[y.d]), 
			sum+=(ss-siz[y.d])*siz[y.d]*y.w1;
	dp[x]=mx+www*siz[x]*(ss-siz[x]);
	tot=0;
	for(qwq y : to[x]) 
		if(y.d != fa) 
			ans=max(ans, dp[y.d]), 
			ha[++tot]=qwqq {siz[y.d], dp[y.d]};
	if(!tot) return ;
	sort(ha+1, ha+tot+1, comp);
	for (int i = 1; i < tot; i++) {
		if (ha[i].w1 == ha[i+1].w1) {
			ans = max(ans, ha[i].w2 + ha[i+1].w2 + t * ha[i].w1 * ha[i+1].w1);
		}
	}
	tot = unique(ha+1, ha+tot+1, eqn) - ha - 1;
	int l = 1, r = 1;
	q[1] = 1;
	for (int i = 2; i <= tot; i++) {
		while (r > l && slope(ha[q[l]], ha[q[l+1]]) > (-t * ha[i].w1)) l++;
		ans = max(ans, ha[i].w2 + ha[q[l]].w2 + t * ha[i].w1 * ha[q[l]].w1);
		while (r > l && slope(ha[q[r]], ha[i]) > slope(ha[q[r-1]], ha[i])) r--;
		q[++r] = i;
	}
	// puts("???");
}

signed main() {
	// File("metro");
	read(dd), read(n), read(t);
	for(int i = 1; i <= n; ++i)
		read(siz[i]), ss+=siz[i];
	for(int i = 2; i <= n; ++i)
		read(u), read(v), read(w), read(ww), 
		to[u].push_back(qwq {v, w, ww}), 
		to[v].push_back(qwq {u, w, ww});
	dfs(1, 1, 0);
	// write(sum, '\n');
	// write(ans, '\n');
	write(sum-ans, '\n');
	return 0;
}