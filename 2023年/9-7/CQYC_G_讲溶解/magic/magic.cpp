#include <bits/stdc++.h>
using namespace std;
const int N = 1560;
int n, m, v[N], len[N], cc, to[N];
char t[N], s[N][N], oo[N];
double tt;

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
void dfs(int x) {
	if(x == cc+1) {
		double gs = 0, mgic = 1;
		for(int i = 1; i <= n; ++i) 
			for(int j = 1; j <= m; ++j) {
				if(i+len[j]-1 > n) continue;
				int pdd=1;
				for(int o = 1; o <= len[j]; ++o) {
					if(t[i+o-1] != s[j][o]) {
						pdd=0;
						break;
					}
				}
				if(pdd)
					mgic=1.0*mgic*v[j], ++gs;
			}
		mgic=(double) pow((double) mgic, (double) 1.0/gs);
//		printf("%s %.2lf\n", t+1, mgic);
		if(mgic > tt) {
			for(int i = 1; i <= n; ++i)
				oo[i]=t[i];
			tt=mgic;
		}
		return ;
	}
	for(int i = 0; i <= 9; ++i)
		t[to[x]]=i+'0', dfs(x+1);
}

signed main() {
	freopen("magic.in", "r", stdin);
	freopen("magic.out", "w", stdout);
	read(n), read(m);
	scanf("%s", t+1);
	int pd = 0; 
	for(int i = 1; i <= m; ++i)
		scanf("%s", s[i]+1), read(v[i]), len[i]=strlen(s[i]+1), pd|=(i != 1 && v[i-1] != v[i]); 
	if(pd) {
		for(int i = 1; i <= n; ++i) {
			oo[i]=t[i];
			if(t[i] == '.')
				to[++cc]=i;
		}
		dfs(1);
		printf("%s", oo+1);
		return 0;
	}
	else {
		for(int i = 1; i <= n; ++i) {
			for(int j = 1; j <= m; ++j) {
				if(i+len[j]-1 > n) continue;
				int pdd=1;
				for(int o = 1; o <= len[j]; ++o) {
					if(t[i+o-1] != '.' && t[i+o-1] != s[j][o]) {
						pdd=0;
						break;
					}
				}
				if(pdd) {
					for(int o = 1; o <= len[j]; ++o) 
						t[i+o-1]=s[j][o];
					for(int i = 1; i <= n; ++i) 
						putchar((t[i] == '.' ? '0' : t[i]));
					return 0;
				}
			}
		}
		for(int i = 1; i <= n; ++i) 
			putchar((t[i] == '.' ? '0' : t[i]));
	}
	return 0;
}
