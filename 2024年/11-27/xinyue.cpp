#include <bits/stdc++.h>
#define rrr 200000
#define inf 1000000000000000007LL
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e5+5;
int n, a, mxa, aa[N], hh[N];
vector <int> ah[N];
LL ans, ret, dp[N];
struct qwq { int k; LL b; };
deque <qwq> tr[N<<2];

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
#define ls (k<<1)
#define rs (ls|1)
int check(qwq A, qwq B, qwq C) {
	return (1LL*(B.b-A.b)*(A.k-C.k) >= 1LL*(C.b-A.b)*(A.k-B.k));
}
void updt(int k, int l, int r, int to, qwq w) {
	while(tr[k].size() > 1 && check(*(++tr[k].rbegin()), *tr[k].rbegin(), w))//注意不要写反了!
		tr[k].pop_back();
	tr[k].push_back(w);
	if(l == r)
		return ;
	int mid = ((l+r)>>1);
	if(to <= mid)
		updt(ls, l, mid, to, w);
	else
		updt(rs, mid+1, r, to, w);
}
LL www(qwq w, int xx) {
	return 1LL*xx*w.k+w.b;
}
void ask(int k, int l, int r, int lq, int rq, int xx) {
	if(lq <= l && r <= rq) {
		while(tr[k].size() > 1 && www(*tr[k].begin(), xx) >= www(*(++tr[k].begin()), xx))
			tr[k].pop_front();
		if(!tr[k].empty())
			ret=min(ret, www(*tr[k].begin(), xx));
		return;
	}
	int mid = ((l+r)>>1);
	if(lq <= mid)
		ask(ls, l, mid, lq, rq, xx);
	if(mid < rq)
		ask(rs, mid+1, r, lq, rq, xx);
}

signed main() {
	read(n), read(a), mxa=a;
	for(int i = 1; i <= n; ++i)
		read(aa[i]), read(hh[i]), mxa=max(mxa, aa[i]), ah[aa[i]].push_back(hh[i]);
	for(int i = 1; i <= n; ++i)
		ans+=1LL*(hh[i]-1)/mxa*aa[i];
	for(int i = mxa; i >= a; --i) {
		ret=(i == mxa ? 0 : inf);
		for(int xx = 0, l = 1, r = i; l <= rrr; ++xx, l+=i, r+=i)
			ask(1, 1, rrr, l, min(rrr, r), xx);
		dp[i]=ret;
		for(int j = 0; j < ah[i].size(); ++j)
			updt(1, 1, rrr, ah[i][j], qwq {i, dp[i]-1LL*(ah[i][j]-1)/mxa*i});
	}
	// debug(ans, "???\n");
	write(dp[a]+ans, '\n');
	return 0;
}
/*
4 1
3 2
4 4
5 6
1 6
9
*/