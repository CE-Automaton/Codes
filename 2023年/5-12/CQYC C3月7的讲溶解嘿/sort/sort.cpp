#include <bits/stdc++.h>
using namespace std;
int n, a[105], to[105], m, x;
struct qwq {
	int l, r;
}ans[40005]; 

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

signed main() {
	freopen("sort.in", "r", stdin);
	freopen("sort.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]), to[a[i]]=i;
	x=3;
	for(int i = 1; i <= n; ++i) 
		for(int j = to[i]; j >= i; ) {
			if(j == i) break;
			if(j-i+1 <= 3) {
				ans[++m]=qwq {j-1, j};
				swap(a[j-1], a[j]);
				to[a[j-1]]=j-1;
				to[a[j]]=j;
				j=j-1;
			}
			else {
				ans[++m]=qwq {j-3, j};
				swap(a[j-3], a[j]);
				swap(a[j-2], a[j-1]);
				to[a[j-3]]=j-3;
				to[a[j-2]]=j-2;
				to[a[j-1]]=j-1;
				to[a[j]]=j;
				j=j-3;
			}
		}
	write(x, '\n');
	write(m, '\n');
	for(int i = 1; i <= m; ++i)
		write(ans[i].l, ' '), write(ans[i].r, '\n');
	return 0;
}
