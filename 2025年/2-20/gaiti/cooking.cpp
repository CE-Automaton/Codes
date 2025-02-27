#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
const int N = 5e5+5;
int n, st;
LL f[N];
struct qwq {
	int a, b;
}aa[N];
struct qvq {
	int a;
	bool operator <(const qvq& A) const {
		return A.a < a;
	}
};
priority_queue <qvq> q;

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
	return A.b < B.b;
}

signed main() {
	File("cooking");
	read(n);
	for(int i = 1; i <= n; ++i)
		read(aa[i].a);
	for(int i = 1; i <= n; ++i)
		read(aa[i].b);
	sort(aa+1, aa+1+n, comp);
	LL stt = 0;
	q.push(qvq {2000000009});
	for(int i = 1; i <= n; ++i) {
		int d = aa[i].b-aa[i-1].b;
		while(d && !q.empty()) {
			int it = q.top().a;
			if(it <= d) {
				stt=stt+it, d-=it;
				f[++st]=stt;
				q.pop();
			}
			else
				stt+=d, it-=d, d=0, q.pop(), q.push(qvq {it});
		}
		q.push(qvq {aa[i].a});
	}
	while(st < n)
		stt+=q.top().a, q.pop(), f[++st]=stt;
	LL ans = 0;
	for(int i = 1; i <= n; ++i)
		ans^=f[i]/*, debug(f[i]), debug('\n')*/;
	write(ans, '\n');
	return 0;
}
