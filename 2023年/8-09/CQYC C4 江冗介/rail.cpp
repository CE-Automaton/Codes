#include <bits/stdc++.h>
using namespace std;
const int N = 1e7+5;
int n, nxt[N], tot;
char s[N], t[N];

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
	freopen("rail.in", "r", stdin);
	freopen("rail.out", "w", stdout);
	read(n);
	scanf("%s", s+1);
	for(int i = 2, j = 0; i <= n; ++i) {
		while(j && s[j+1] != s[i])
			j=nxt[j];
		if(s[j+1] == s[i])
			++j;
		nxt[i]=j;
	}
//	for(int i = 1; i <= n; ++i) 
//		write(nxt[i], ' ');
	int now = nxt[n], ans = 0;
	while(now > n/2)
		now=nxt[now];
	ans=now;
	for(int i = now+1; i+now <= n; ++i)
		t[++tot]=s[i];
//	cout<<"\n"<<t+1<<"\n";
	for(int i = 2, j = 0; i <= tot; ++i) {
		while(j && t[j+1] != t[i])
			j=nxt[j];
		if(t[j+1] == t[i])
			++j;
		nxt[i]=j;
	}
//	for(int i = 1; i <= tot; ++i) 
//		write(nxt[i], ' ');
	now=nxt[tot];
	while(ans+now > n/2)
		now=nxt[now];
	write(ans+now, '\n');
	return 0;
}
