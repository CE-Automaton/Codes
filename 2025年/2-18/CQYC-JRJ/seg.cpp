#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 6e5+5;
int n, kkk, ans[N], ss, tt, ww[N], cnt, 
dp[75][75][75];
double ll[N], rr[N];
vector <int> to[N];
struct qwq {
	int l, r;
}ls[75][75][75], now;
struct qvq {
	int l, r, pd;
}a[N], b[N];

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
int compp(qvq A, qvq B) {
	return A.l < B.l;
}
int comp(qvq A, qvq B) {
	if(A.l == B.l)
		return A.r < B.r;
	return A.l < B.l;
}

signed main() {
	File("seg");
	read(n);
	for(int i = 1; i <= n; ++i) 
		scanf("%lf %lf", &ll[i], &rr[i]), 
		a[i].l=ll[i]*1000000, a[i].r=rr[i]*1000000, a[i].pd=i,
		ss=(a[i].l == 0 ? i : ss), 
		tt=(a[i].r == 1000000 ? i : tt);
	if(a[ss].r-a[ss].l >= 650000) {
		puts("1");
		write(ss, '\n');
		return 0;
	}
	if(a[tt].r-a[tt].l >= 650000) {
		puts("1");
		write(tt, '\n');
		return 0;
	}
	if(a[ss].r-a[ss].l+a[tt].r-a[tt].l-max(0, a[ss].r-a[tt].l)*2 >= 650000) {
		puts("2");
		write(ss, ' ');
		write(tt, '\n');
		return 0;
	}
	// debug("?????\n");
	for(int i = 1; i <= n; ++i)
		++a[i].l, 
		b[(i<<1)-1]=qvq {a[i].l, i, 0}, 
		b[(i<<1)]=qvq {a[i].r, i, 1};
	sort(b+1, b+1+n+n, compp);
	for(int i = 1; i <= n+n; ++i) {
		if(i == 1 || b[i].l != b[i-1].l)
			ww[++cnt]=b[i].l;
		if(b[i].pd)
			a[b[i].r].r=cnt;
		else
			a[b[i].r].l=cnt;
	}
	if(n <= 35) {
		sort(a+1, a+1+n, comp);
		for(int i = 1; i <= n; ++i) {
			for(int j = 1; j <= cnt; ++j)
				for(int k = 0; k <= j; ++k)
					dp[i][j][k]=dp[i-1][j][k], 
					ls[i][j][k]=qwq {j, k};
			if(ww[a[i].r]-ww[a[i].l]+1 >= dp[i][a[i].r][0])
				dp[i][a[i].r][0]=ww[a[i].r]-ww[a[i].l]+1, 
				ls[i][a[i].r][0]=qwq {0, 0};
			for(int j = 0; j <= a[i].r; ++j)
				for(int k = 0; k <= j; ++k) 
					if(a[i].l <= j) {
						int op = dp[i-1][j][k]+ww[a[i].r]-ww[j]-ww[j]+max(ww[k], ww[a[i].l]-1);
						if(op > dp[i][a[i].r][max(k, a[i].l)])
							dp[i][a[i].r][max(k, a[i].l)]=op, 
							ls[i][a[i].r][max(k, a[i].l)]=qwq {j, k};
					}
					else {
						int op = dp[i-1][j][k]+ww[a[i].r]-ww[a[i].l]+1;
						if(op > dp[i][a[i].r][0])
							dp[i][a[i].r][0]=op, 
							ls[i][a[i].r][0]=qwq {j, k};
					}
		}
		for(int i = 1; i <= cnt; ++i)
			for(int j = 0; j <= i; ++j)
				if(dp[n][i][j] >= dp[n][now.l][now.r])
					now=qwq {i, j};
		// debug(ww[now.l], ww[now.r], "????\n");
		for(int i = n; i >= 1; --i) {
			qwq it = ls[i][now.l][now.r];
			if(it.l != now.l)
				ans[++kkk]=a[i].pd;
			now=it;
		}
		write(kkk, '\n');
		for(int i = 1; i <= kkk; ++i)
			write(ans[i], ' ');
		return 0;
	}
	sort(a+1, a+1+n, comp);
	write(n, '\n');
	for(int i = 1; i <= n; ++i)
		write(a[i].pd, ' ');
	return 0;
}
