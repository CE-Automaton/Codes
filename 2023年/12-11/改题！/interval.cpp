#include <bits/stdc++.h>
using namespace std;
const int N = 5e5+5;
int n, ans;
struct qwq {
	int l, r;
	bool operator <(const qwq &A) const {
		return A.r < r;
	};
}a[N];
struct qqq {
	int l, r;
	bool operator <(const qqq &A) const {
		return a[A.r].r < a[r].r;
	};
};
priority_queue <qwq> q1;
priority_queue <qqq> q2;

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
	if(A.l == B.l)
		return A.r < B.r;
	return A.l < B.l;
}
void qq2(int x) {
	if(q2.empty() || a[q2.top().r].r >= a[x].r)
		q1.push(a[x]);
	else {
		qqq it = q2.top(); q2.pop();
		q2.push(qqq {it.l, x});
		q1.push(a[it.r]);
	}
}
void qq1(int x) {
	if(q1.empty() || q1.top().r >= a[x].l)
		qq2(x);
	else {
		qwq it = q1.top(); q1.pop();
		q2.push(qqq{it.r, x});
		++ans;
	}
}

signed main() {
	freopen("interval.in", "r", stdin);
	freopen("interval.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i].l), read(a[i].r);
	sort(a+1, a+1+n, comp);
	for(int i = 1; i <= n; ++i) 
		qq1(i);
	write(ans, '\n');
	return 0;
}
