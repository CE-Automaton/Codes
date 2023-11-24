#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5+5, UP = 100, AZ = 700;
int n, q, m, s[N], tmp[N], tmpp[UP+5][UP+5], sum[UP+5][UP+5], wtfs[AZ+5];
struct cz {
	int ot, l, r, k, x;
}pro[AZ+5];
template<typename T> void read(T& x) {
	x = 0; int f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
	while (isdigit(ch)) x = (x<<1) + (x<<3) + ch - '0', ch = getchar();
	x = (f ? -x : x);
}
int __stk[100], __tp;
template<typename T> void put(T x) {
	if (x < 0) putchar('-'), x = -x;
	do { __stk[++__tp] = x % 10, x /= 10; } while (x);
	while (__tp) putchar(__stk[__tp--] + '0');
}
void solve() {
	int t = 0;
	for(int i = 1; i <= m; ++i) {
		if(pro[i].ot == 1) {
			wtfs[++t]=i;
			continue;
		}
		int ans = s[pro[i].r]-s[pro[i].l-1];
		for(int o = 1, j = 0; o <= t; ++o) {
			j = wtfs[o];
			int gsl = pro[i].l/pro[j].k, gsr = pro[i].r/pro[j].k;
			if(gsl+1 < gsr)
				ans+=(gsr-gsl-1)*pro[j].x*(pro[j].r-pro[j].l+1);
			if(gsl == gsr)
				ans+=pro[j].x*max(0LL, min(pro[j].r, pro[i].r%pro[j].k)-max(pro[i].l%pro[j].k, pro[j].l)+1);
			else
				ans+=pro[j].x*(max(0LL, pro[j].r-max(pro[j].l, pro[i].l%pro[j].k)+1)+
							   max(0LL, min(pro[j].r, pro[i].r%pro[j].k)-pro[j].l+1));
		}
		for(int j = 1; j <= UP; ++j) {
			int gsl = pro[i].l/j, gsr = pro[i].r/j, qwq = sum[j][j-1];
			if(gsl+1 < gsr)
				ans+=qwq*(gsr-gsl-1);
			if(gsl == gsr)
				ans+=sum[j][pro[i].r%j]-(pro[i].l%j ? sum[j][pro[i].l%j-1] : 0);
			else
				ans+=sum[j][pro[i].r%j]+qwq-(pro[i].l%j ? sum[j][pro[i].l%j-1] : 0);
		}
		put(ans), putchar('\n');
	}
	for(int o = 1, i = 0; o <= t; ++o) {
		i=wtfs[o];
		if(pro[i].k > UP) {
			int l = pro[i].l, r = pro[i].r;
			while(l <= n) {
				tmp[l]+=pro[i].x;
				if(r+1 <= n) tmp[r+1]-=pro[i].x;
				l+=pro[i].k;
				r+=pro[i].k;
			}
		}
		else
			tmpp[pro[i].k][pro[i].l]+=pro[i].x, tmpp[pro[i].k][pro[i].r+1]-=pro[i].x;
	}
	for(int i = 1; i <= n; ++i)
		tmp[i]+=tmp[i-1];
	tmp[0]=0;
	for(int i = 1; i <= n; ++i)
		tmp[i]+=tmp[i-1], s[i]+=tmp[i];
	for(int i = 1; i <= n; ++i)
		tmp[i]=0;
	for(int i = 1; i <= UP; ++i) {
		for(int j = 1; j < i; ++j)
			tmpp[i][j]+=tmpp[i][j-1];
		for(int j = 1; j < i; ++j)
			tmpp[i][j]+=tmpp[i][j-1];
		for(int j = 0; j < i; ++j)
			sum[i][j]+=tmpp[i][j], tmpp[i][j]=0;
	}
}
signed main() {
	freopen("sorrow.in", "r", stdin);
	freopen("sorrow.out", "w", stdout);
	read(n), read(q);
	for(int i = 1; i <= n; ++i)
		read(s[i]), s[i]+=s[i-1];
	while(q--) {
		read(pro[++m].ot);
		if(pro[m].ot == 1)
			read(pro[m].k), read(pro[m].l), read(pro[m].r), read(pro[m].x);
		else read(pro[m].l), read(pro[m].r);
		if(m == AZ) 
			solve(), m=0;
	}
	if(m) solve(), m=0;
	return 0;
} 
