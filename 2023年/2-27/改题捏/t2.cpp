#include <bits/stdc++.h>
#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#define inf 200000000000000LL
using namespace std;
const int N = 2e5+5;
int n, a[N], b[N], cnt, to[N], tot;
long long sum, ans=inf, s[N], tr1[N], tr2[N];
struct qwq {
	int s, id;
}c[N];
int comp(qwq A, qwq B) {
	return A.s < B.s;
}
vector <int> az[N];
long long mn(long long x, long long y) {
	return (x < y ? x : y);
}
void add1(int x, long long w) { while(x >= 1) tr1[x]=mn(tr1[x], w), x=x-(x&(-x)); }
long long ask1(int x, long long ret = inf) {
	if(!x) return inf;
	while(x <= cnt) ret=mn(ret, tr1[x]), x=x+(x&(-x));
	return ret;
}
void add2(int x, long long w) { while(x <= cnt) tr2[x]=mn(tr2[x], w), x=x+(x&(-x)); }
long long ask2(int x, long long ret = inf) {
	while(x >= 1) ret=mn(ret, tr2[x]), x=x-(x&(-x));
	return ret;
}
template <class T>
inline void get(T &res)
{
	char ch;
	bool bo = false;
	while (ch = getchar(), !isdigit(ch))
		if (ch == '-') bo = true;
	
	res = ch ^ 48;
	while (ch = getchar(), isdigit(ch))
		res = (res << 1) + (res << 3) + (ch ^ 48);
	
	if (bo) res = ~ res + 1;
	return;
}

template <class T>
inline void _put(T x)
{
	if (x > 9) _put(x / 10);
	putchar(x % 10 + '0');
	return;
}

template <class T>
inline void put(T x, char ch)
{
	if (x < 0)
		putchar('-'), x = ~ x + 1;
	_put(x);
	putchar(ch);
	return;
}
int main() {
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
	get(n);
	for(int i = 1; i <= n; ++i)
		get(a[i]), c[i]=qwq{a[i], i};
	sort(c+1, c+1+n, comp);
	for(int i = 1; i <= n; ++i) {
		if(i == 1 || c[i].s != c[i-1].s)
			b[++cnt]=c[i].s;
		a[c[i].id]=cnt;
	}
	int c = 0;
	for(int i = 1; i <= n; ++i) {
		if(az[a[i]].size() == 0) 
			++c, to[++tot]=i;
		az[a[i]].push_back(i);
		sum+=1LL*i*c;
	}
	for(int i = 1; i <= cnt; ++i) 
		az[i].push_back(n+1);
	for(int i = n; i >= 1; --i)
		s[i]=s[i+1]+i;
//	puts("?");
	for(int i = 1; i <= cnt; ++i)
		tr1[i]=tr2[i]=inf;
	for(int x = tot; x >= 1; --x) {
		ans=mn(ans, ask1(a[to[x]]+1)-b[a[to[x]]]);
		add1(a[to[x]], b[a[to[x]]]-s[to[x]]+s[az[a[to[x]]][1]]);
			
		ans=mn(ans, ask2(a[to[x]]-1)+b[a[to[x]]]);
		add2(a[to[x]], s[az[a[to[x]]][1]]-b[a[to[x]]]-s[to[x]]);
	}
//	cout<<ans<<"\n";
//	puts("?");
	
	for(int i = 1; i <= cnt; ++i)
		tr1[i]=tr2[i]=inf;
	for(int x = 1; x <= tot; ++x) {
		ans=mn(ans, ask1(a[to[x]]+1)-s[to[x]]-b[a[to[x]]]);
		add1(a[to[x]], s[az[a[to[x]]][1]]+b[a[to[x]]]);
			
		ans=mn(ans, ask2(a[to[x]]-1)-s[to[x]]+b[a[to[x]]]);
		add2(a[to[x]], s[az[a[to[x]]][1]]-b[a[to[x]]]);
	}
	put(sum+ans, '\n');
	return 0;
}
