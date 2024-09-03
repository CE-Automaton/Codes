#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e5+5;
int n, q, l, r, tot, op[N], ww[N], mx[N], vis[N], jp[N][21], rr[N][27];
char a[N], zhan[N], pp[N];
vector <int> to[N];

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

signed main() {
	// File("merge");
	scanf("%s", a+1);
	n=strlen(a+1);
	for(int i = n; i >= 1; --i) {
		rr[i][a[i]-'a'+1]=i+1;
		for(int j = a[i]-'a'+2; j <= 27; ++j)
			rr[i][j]=rr[rr[i][j-1]][j-1];
		for(int j = 1; j < a[i]-'a'+1; ++j)
			rr[i][j]=rr[rr[i][27]][j];
		if(rr[i][27])
			vis[i]=1;
	}
	for(int i = n; i >= 1; --i) 
		if(vis[i]) {
			jp[i][0]=rr[i][27];
			for(int j = 1; j <= 19; ++j)
				jp[i][j]=jp[jp[i][j-1]][j-1];
		}
	read(q);
	for(int i = 1; i <= q; ++i) {
		read(l), read(r);
		++r;
		if(!vis[l]) {
			puts("No");
			continue;
		}
		int to = l;
		for(int i = 19; i >= 0; --i)
			if(jp[to][i] && jp[to][i] <= r)
				to=jp[to][i];
		if(to == r)
			puts("Yes");
		else
			puts("No");
	}
	return 0;
}