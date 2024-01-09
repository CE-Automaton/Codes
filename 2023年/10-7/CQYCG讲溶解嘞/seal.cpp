#include <bits/stdc++.h>
#define inf 1000000007
using namespace std;
const int N = 2e3+5;
int n, m, t, l[N], r[N], to[N], dp[N], dpp[N], f[N][2], ff[N][2], nxt[N], pd[N], sum;
struct qwq {
	int w, d, t;
}b[N<<1];

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
bool comp(qwq A, qwq B) {
	return A.w < B.w;
}

signed main() {
	freopen("seal.in", "r", stdin);
	freopen("seal.out", "w", stdout);
	read(n), read(t), read(m);
	for(int i = 1; i <= n; ++i)
		read(l[i]), read(r[i]), b[i*2-1]=qwq {l[i], i, 0}, b[i*2]=qwq {r[i], i, 1};
	sort(b+1, b+1+n+n, comp);
	for(int i = 1; i <= n+n; ++i) 
		if(b[i].t) r[b[i].d]=i;
		else l[b[i].d]=i;
	for(int i = 1; i <= n; ++i) {
		int ll = b[r[i]-1].d;
		if(ll != i && b[r[i]-1].t == 0)
			nxt[i]=ll, pd[ll]=1;
	}
	for(int i = 1; i <= n; ++i) 
		dp[i]=inf;
	for(int i = 1; i <= n; ++i) {
		if(pd[i]) continue;
		if(nxt[i] == 0) {
			int ww = (l[i]+1 == r[i] ? b[r[i]].w-b[l[i]].w : b[r[i]].w-b[r[i]-1].w+b[l[i]+1].w-b[l[i]].w);
			for(int j = 0; j <= n; ++j)
				dpp[j]=inf;
			for(int j = 0; j <= n; ++j)
				dpp[j]=min(dpp[j], dp[j]+ww), 
				dpp[j+1]=min(dpp[j+1], dp[j]);
			++sum;
			for(int j = 0; j <= n; ++j)
				dp[j]=dpp[j];
		}
		else {
			int now = i, gs = 0;
			for(int j = 0; j <= n; ++j) 
				f[j][0]=f[j][1]=inf;
			f[0][0]=0;
			while(now) {
				for(int j = 0; j <= n; ++j) 
					ff[j][0]=ff[j][1]=inf;
				for(int k = 0; k <= gs; ++k)
					for(int p = 0; p <= 1; ++p)
						ff[k+1][0]=min(ff[k+1][0], f[k][p]), 
						ff[k][1]=min(ff[k][1], f[k][p]+b[r[now]].w-b[r[now]-1].w+(p == 0 ? b[l[now]+1].w-b[l[now]].w : 0));
				++gs;
				now=nxt[now];
				for(int k = 0; k <= n; ++k)
					f[k][0]=ff[k][0], f[k][1]=ff[k][1];
			}
			for(int j = 0; j <= n; ++j)
				dpp[j]=inf;
			for(int k = 0; k <= gs; ++k) {
				int ww = min(f[k][0], f[k][1]);
				for(int j = 0; j <= sum; ++j)
					dpp[j+k]=min(dpp[j+k], dp[j]+ww);
			}
			sum+=gs;
			for(int j = 0; j <= n; ++j)
				dp[j]=dpp[j];
		}
	}
	write(t-dp[m], '\n');
	return 0;
}
