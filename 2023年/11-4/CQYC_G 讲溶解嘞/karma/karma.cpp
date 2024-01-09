#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int n;
long long ans;
char s[N];
struct qwq {
	int a, b;
}a[N];

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
	if(1LL*A.b*B.a == 1LL*B.b*A.a)
		return A.b < B.b;
	return 1LL*A.b*B.a < 1LL*B.b*A.a;
}

signed main() {
	freopen("karma.in", "r", stdin);
	freopen("karma.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i) {
		scanf("%s", s+1);
		int m = strlen(s+1), gs = 0;
		for(int j = 1; j <= m; ++j)
			ans+=1LL*gs*((s[j]-'0')^1), gs+=s[j]-'0';
		a[i]=qwq {m-gs, gs};
	}
	sort(a+1, a+1+n, comp);
	int gs = 0;
	for(int i = 1; i <= n; ++i)
		ans+=1LL*gs*a[i].a, gs+=a[i].b;
	write(ans, '\n');
	return 0;
}
