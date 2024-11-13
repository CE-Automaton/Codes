#include <bits/stdc++.h>
#define inf 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e5+5, V = 1e3+5;
int n, s[N], a[N], l[N], r[N], ans[N];
vector <int> to[V];
struct qwq {
	int s, d;
}b[N];

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
int comp(qwq A, qwq B) {
	if(A.s == B.s)
		return a[A.d] < a[B.d];
	return A.s < B.s;
}
void sol() {
	int sum = 0;
	for(int i = r[0], j = 1; i <= n; i=r[i], ++j) 
		sum+=a[b[i].d], ans[j]=min(ans[j], sum+2*b[i].s);
}

signed main() {
	File("sales");
	read(n);
	for(int i = 1; i <= n; ++i)
		read(s[i]), b[i]=qwq {s[i], i};
	for(int i = 1; i <= n; ++i)
		read(a[i]), to[a[i]].push_back(i);
	sort(b+1, b+1+n, comp);
	for(int i = 1; i <= n; ++i)
		s[b[i].d]=i, r[i]=i+1, l[i]=i-1, ans[i]=inf;
	r[0]=1;
	for(int i = 1000; i >= 0; --i) {
		sol();
		for(int j : to[i])
			l[r[s[j]]]=l[s[j]], r[l[s[j]]]=r[s[j]];
	}
	for(int i = 1; i <= n; ++i)
		write(ans[i], '\n');
	return 0;
}