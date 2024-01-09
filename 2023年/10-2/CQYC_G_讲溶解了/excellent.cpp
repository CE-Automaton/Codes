#include <bits/stdc++.h>
using namespace std;
const int N = 3e3+5;
int T, n, nxt[N], pd[N][N], ln[N], fa[N], vis[N];
char s[N], t[N<<2];

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
int pdd(int a, int b, int now) {
	if(t[a] == '?') {
		if(vis[a] < now) {
			vis[a]=now;
			fa[a]=b;
			return 1;
		}
		else 
			return (t[fa[a]] == t[b]);//应该没有这种情况吧? 
	}
	if(t[b] == '?') {
		if(vis[b] < now)
			return 1;
		else
			return pdd(a, fa[b]/*有可能fa[b]为'?'*/, now);
	}
	return (t[a] == t[b]);
}

signed main() {
	freopen("excellent.in", "r", stdin);
	freopen("excellent.out", "w", stdout);
	read(T);
	while(T--) {
		scanf("%s", s+1);
		n=strlen(s+1);
		int pd1 = 1, pd2 = 1;
		for(int i = 1; i <= n; ++i)
			pd1&=(s[i] == '?'), pd2&=(s[i] != '?');
		if(pd1 || pd2) {
			for(int o = 1; o <= n; ++o) 
				for(int p = o; p <= n; ++p) 
					pd[o][p]=0;
			for(int o = 1; o <= n; ++o) {
				pd[o][0]=0;
				int len = 0;
				for(int j = o; j <= n; ++j)
					t[++len]=s[j];
				for(int i = 1; i <= len; ++i) nxt[i] = 0;
				nxt[1]=len;
				for(int i = 2, l = 0, r = 0; i <= len; ++i) {
					if(i <= r) nxt[i] = min(nxt[i-l+1], r-i+1);
					while(i+nxt[i] <= len && t[i+nxt[i]] == t[nxt[i]+1]) ++nxt[i];
					if(i+nxt[i]-1 > r) l=i, r=i+nxt[i]-1;
				}
				for(int i = 2; i <= len; ++i) 
					if(nxt[i] >= i-1)
						pd[o][o+2*i-3]=1, ++pd[o][0];
			}
			int ans = 0;
			for(int i = 1; i <= n; ++i)
				for(int j = i+1; j <= n; ++j)
					if(pd[i][j])
						ans+=pd[j+1][0]/*, cout<<i<<" "<<j<<"\n"*/;
			write(ans, '\n');
			continue; 
		}
		for(int o = 1; o <= n; ++o) 
			for(int p = o; p <= n; ++p) 
				pd[o][p]=0;
		for(int o = 1; o <= n; ++o) {
			pd[o][0]=0;
			int len = 0;
			for(int j = o; j <= n; ++j)
				t[++len]=s[j];
			for(int i = 1; i <= len; ++i) nxt[i] = 0, fa[i] = i, vis[i] = 0;
			nxt[1]=len;
			for(int i = 2/*, l = 0, r = 0*/; i <= len; ++i) {
//				if(i == 5)
//					cout<<l<<" "<<r<<"!?\n";
//				if(i <= r) nxt[i] = min(nxt[i-l+1], r-i+1);
				while(i+nxt[i] <= len && pdd(i+nxt[i], nxt[i]+1, i)) ++nxt[i];
//				if(i+nxt[i]-1 > r) l=i, r=i+nxt[i]-1;
			}
//			for(int i = 1; i <= n; ++i)
//				write(nxt[i], ' ');
//			puts("!?!?!?!?");
			for(int i = 2; i <= len; ++i) 
				if(nxt[i] >= i-1)
					pd[o][o+2*i-3]=1, ++pd[o][0];
		}
		int ans = 0;
		for(int i = 1; i <= n; ++i)
			for(int j = i+1; j <= n; ++j)
				if(pd[i][j])
					ans+=pd[j+1][0]/*, cout<<i<<" "<<j<<"\n"*/;
		write(ans, '\n');
	}
	return 0;
}
