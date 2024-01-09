#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N = 5e6+5;
int n, m, p[N], a[N], l[N], r[N], to[N], nxt[N], ans, zhan[N], sum;

template <typename T> void read(T& x) {
	x = 0; int f = 0; char c = getchar();
	while(c < '0' || c > '9') f |= (c == '-'), c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x);
}
int lne; char put[105];
template <typename T> void write(T x) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
int check(int j, int i, int pd) {
	int x=p[j];
	if(!pd) {
		if(l[x] && p[i-j+l[x]] >= p[i]) return 0;
		if(r[x] && p[i-j+r[x]] <= p[i]) return 0;
	}
	else {
		if(l[x] && a[i-j+l[x]] >= a[i]) return 0;
		if(r[x] && a[i-j+r[x]] <= a[i]) return 0;
	}
	return 1;
}

int main() {
	read(n), read(m);
	for(int i = 1; i <= n; ++i)
		read(to[i]), p[to[i]]=i;
	for(int i = 1; i <= m; ++i)
		read(a[i]);
	for(int i = 0; i <= n+1; ++i)
		l[i]=i-1, r[i]=i+1;
	for(int i = n; i >= 1; --i) 
		r[l[p[i]]]=r[p[i]], l[r[p[i]]]=l[p[i]];
	for(int i = 1; i <= n; ++i)
		l[i]=to[l[i]], r[i]=to[r[i]]/*, cout<<i<<"-"<<l[i]<<"-"<<r[i]<<"\n"*/;
	for(int i = 2, j = 0; i <= n; ++i) {
		while(j && !check(j+1, i, 0)) j=nxt[j];
		if(check(j+1, i, 0)) ++j;
//		cout<<i<<"-"<<j<<"\n";
		nxt[i]=j;
	}
	for(int i = 1, j = 0; i <= m; ++i) {
		while(j && !check(j+1, i, 1)) j=nxt[j];
		if(check(j+1, i, 1)) ++j;
//		cout<<i<<" "<<j<<"\n";
		if(j == n) zhan[++ans]=i-n+1, j=nxt[j];
	}
	for(int i = 1, j = 1; i <= ans; ++i)
		sum=upd(sum+1LL*zhan[i]*j%mod), j = 233LL*j%mod;
	write(sum);
	return 0;
}
