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
int jmp(int x, int y) {
	for(int i = 0; i <= 19; ++i)
		if((y>>i)&1)
			x=jp[x][i];
	return x;
}

signed main() {
	File("merge");
	scanf("%s", a+1);
	n=strlen(a+1);
	for(int i = n; i >= 1; --i) {
		tot=0;
		pp[++tot]=a[i];
		for(int j = i+1; j <= n; ++j) {
			if(pp[tot] < a[j]) {
				if(vis[j] == 1) {
					j=rr[j][pp[tot]-'a'+1];
					continue;
				}
				else
					break;
			}
			pp[++tot]=a[j];
			while(tot >= 2 && pp[tot] == pp[tot-1]) {
				--tot;
				if(pp[tot] == 'z') --tot;
				else pp[tot]=pp[tot]+1;
			}
			if(!tot) {
				ww[i]=j, vis[i]=1;
				for(int k = 1; k <= 26; ++k)
					rr[i][k]=n+1;
				if(vis[j+1]) 
					for(int k = 1; k <= 26; ++k)
						rr[i][k]=rr[j+1][k];
				if(j+1 <= n)
					for(int k = a[j+1]-'a'+1; k <= 26; ++k)
						rr[i][k]=j;
				break;
			}
		}
	}
	for(int i = n; i >= 1; --i) 
		if(vis[i]) {
			jp[i][0]=ww[i]+1;
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
		int ll = 1, rr = n, to = n+1;
		while(ll <= rr) {
			int mid = ((ll+rr)>>1), too = jmp(l, mid);
			if(!too || too >= r)
				to=too, rr=mid-1;
			else
				ll=mid+1;
		}
		if(to == r)
			puts("Yes");
		else
			puts("No");
	}
	return 0;
}