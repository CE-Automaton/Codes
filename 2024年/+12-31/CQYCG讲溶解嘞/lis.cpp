#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int n, v, l[N], r[N], tr[N];

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
	freopen("lis.in", "r", stdin);
	freopen("lis.out", "w", stdout);
    read(n);
	for(int i = 1; i <= n; ++i) 
		read(l[i]), read(r[i]), v=max(v, r[i]);
	for(int i = 1; i <= n; ++i) {
		for(int j = r[i]; j >= l[i]; --j)
			tr[j]=max(tr[j], tr[j-1]+1);
		for(int j = l[i]; j <= v; ++j)
			tr[j]=max(tr[j], tr[j-1]);
	}
	write(tr[v], '\n');
	return 0;
}