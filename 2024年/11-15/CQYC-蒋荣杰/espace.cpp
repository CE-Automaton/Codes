#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5;
int n, k, gs, gss, tot, now;
char s[N], t[N], zhan[N];

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
int pd(char A, char B, char C) {
	return ((A == 'A' && B == 'B' && C == 'C') || (A == 'B' && B == 'C' && C == 'A') || (A == 'C' && B == 'A' && C == 'B'));
}

signed main() {
	File("espace");
	read(n);
	scanf("%s", s+1);
	for(int i = 1; i <= n; ++i) {
		zhan[++tot]=s[i];
		while(tot >= 3 && pd(zhan[tot-2], zhan[tot-1], zhan[tot]))
			tot-=3, ++gs;
	}
	now=tot;
	for(int i = 1; i <= tot; ++i)
		s[i]=zhan[i];
	read(k);
	while(k--) {
		scanf("%s", t+1);
		gss=tot=0;
		for(int i = 1; i <= n; ++i) {
			zhan[++tot]=t[i];
			while(tot >= 3 && pd(zhan[tot-2], zhan[tot-1], zhan[tot]))
				tot-=3, ++gss;
		}
		int ans = (gss == gs);
		if(!ans) {
			puts("no");
			continue;
		}
		for(int i = 1; i <= tot; ++i)
			ans&=(zhan[i] == s[i]);
		if(!ans) 
			puts("no");
		else
			puts("yes");
	}
	return 0;
}