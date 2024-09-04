#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e5+5;
int k, m, n, ln, l, r, xx, ll[N], rr[N], to[N];
char s[N], t[N];
string ans;

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
string ddfs(int lq, int rq, int now) {
	// if(now <= 10)
	// 	debug(lq, rq, now, "???\n");
	if(lq > rq) return "";
	if(now == 0) {
		string ret = "";
		for(int j = lq; j <= rq; ++j)
			ret+=s[j];
		return ret;
	}
	int rrr = to[now]+rr[now]-ll[now];
	if(to[now]+1 > rq)
		return ddfs(lq, rq, now-1);
	if(rrr < lq) 
		return ddfs(lq-rr[now]+ll[now], rq-rr[now]+ll[now], now-1);
	if(to[now]+1 <= lq && rrr >= rq)
		return ddfs(ll[now]+lq-to[now], ll[now]-to[now]+rq, now-1);
	if(to[now]+1 >= lq && to[now]+1 <= rq) {
		int gs = min(rq-to[now], rr[now]-ll[now]);
		return ddfs(lq, to[now], now-1)+ddfs(ll[now]+1, ll[now]+gs, now-1)+ddfs(to[now]+1, rq-gs, now-1);
	}
	if(lq <= rrr && rrr <= rq)
		return ddfs(rr[now]-rrr+lq, rr[now], now-1)+ddfs(to[now]+1, rq-rr[now]+ll[now], now-1);
}

signed main() {
	File("copy");
	read(k), read(m);
	scanf("%s", s+1);
	ln=strlen(s+1);
	read(n);
	if(n <= 2000 && m <= 2000) {
		for(int i = 1; i <= n; ++i) {
			read(l), read(r), read(xx);
			++l, ++xx;
			int now = 1, len = min(m, ln+r-l+1);
			for(int j = 1; j <= len; ++j)
				if(j == xx) {
					for(int op = 1; op <= r-l+1 && j+op-1 <= len; ++op)
						t[j+op-1]=s[l+op-1];
					j+=r-l;
				}
				else
					t[j]=s[now], ++now;
			ln=len;
		}
		for(int i = 1; i <= k; ++i)
			putchar(s[i]);
	}
	else {
		for(int i = 1; i <= n; ++i) 
			read(ll[i]), read(rr[i]), read(to[i]);
		ans=ddfs(1, k, n);
		for(int i = 0; i < k; ++i)
			putchar(ans[i]);
	}
	return 0;
}