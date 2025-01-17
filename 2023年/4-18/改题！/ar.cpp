#include <bits/stdc++.h>
#define uLL unsigned long long
using namespace std;
const int N = 5e5+5;
const uLL base = 1000000007;
int n, cnt;
struct qwq {
	int a, b;
	bool operator <(const qwq& A) const {
		if(a == A.a)
			return b > A.b;
		return a > A.a;
	}
}pro[N];
vector <qwq> xi[N];
priority_queue <qwq> q;

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
int p_d(int l) {
	while(!q.empty()) q.pop();
	for(int i = 1; i <= n; ++i) {
		for(auto j : xi[i])
			q.push(j);
		if(i < l) continue;
		if(q.empty()) 
			return 0;
		qwq it = q.top();
		q.pop();
		if(it.a < i) 
			return 0;
		if(!q.empty() && q.top().a < i) 
			return 0;
	}
	if(!q.empty()) return 0;
	return 1;
}

signed main() {
	freopen("ar.in", "r", stdin);
	freopen("ar.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i)
		read(pro[i].a), read(pro[i].b), xi[pro[i].a].push_back(qwq {pro[i].b, i});
	if(p_d(0) == 0) {
		puts("-1");
		return 0;
	}
	
	return 0;
}
