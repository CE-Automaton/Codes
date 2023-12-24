#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int n, m, p[2], q[2], u, v, P[2][N], Q[2][N]; 
long long ans;

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
int comp(int A, int B) {
	return A > B;
}

signed main() {
	freopen("derby.in", "r", stdin);
	freopen("derby.out", "w", stdout);
	read(n), read(m);
	for(int i = 1; i <= n; ++i) 
		read(u), read(v), P[u][++p[u]]=v;
	for(int i = 1; i <= m; ++i) 
		read(u), read(v), Q[u][++q[u]]=v;
	if(p[0])
		sort(P[0]+1, P[0]+1+p[0], comp);
	if(p[1])
		sort(P[1]+1, P[1]+1+p[1], comp);
	if(q[0])
		sort(Q[0]+1, Q[0]+1+q[0], comp);
	if(q[1])
		sort(Q[1]+1, Q[1]+1+q[1], comp);
	for(int i = 1, l = 1; i <= q[0]; ++i) 
		if(l <= p[1] && P[1][l] > Q[0][i])//l是目前的P的最大值,若是最大值都和Q相等则一定没有更大的 
			ans+=1LL*(P[1][l]+Q[0][i]), ++l;
	for(int i = 1, l = 1; i <= p[0]; ++i) 
		if(l <= q[1] && Q[1][l] > P[0][i])//l是目前的Q的最大值,若是最大值都和P相等则一定没有更大的 
			ans+=1LL*(Q[1][l]+P[0][i]), ++l;
	write(ans, '\n');
	return 0;
}
