#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6+5, NM = 1e6+5;
int n, m, a[N], b[N], c[N], d[N], bl[NM], pd[NM], vis[N], fa[NM], cnt[NM],
l[NM], r[NM], cpfa[NM], cpcnt[NM], cpl[NM], cpr[NM], cpvis[NM];
long long sum[NM], cpsum[NM], A, B;
struct qwq {
	int l, r;
	long long s;
}xx, cpxx, ans[2];

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
int find(int x) {
	return (x == fa[x] ? x : fa[x]=find(fa[x]));
}
int cpfind(int x) {
	return (x == cpfa[x] ? x : cpfa[x]=cpfind(cpfa[x]));
}

signed main() {
	freopen("soldier.in", "r", stdin);
	freopen("soldier.out", "w", stdout);
	read(n), read(m);
	if(n > 10000) {
		for(int i = 1; i <= n; ++i)
			read(a[i]);
		for(int i = 1; i <= n; ++i)
			read(b[i]), pd[a[i]]=i, A+=b[i];
		for(int i = 1; i <= m; ++i)
			read(c[i]);
		for(int i = 1; i <= m; ++i)
			read(d[i]), B+=d[i], bl[c[i]]=i;
		if(A > B)
			ans[0]=qwq{1, n, A};
		else
			ans[1]=qwq{1, m, B}; 
		for(int i = 1; i <= m; ++i) {
			fa[i]=i, cnt[i]=1, sum[i]=d[i];
			l[i]=r[i]=i;
			if(pd[c[i]]) {
				vis[i]=1;
				continue;
			}
			if(sum[i] > xx.s)
				xx=qwq{i, i, sum[i]};
			if(i > 1 && vis[i-1] == 0) {
				int x = find(i-1), y = i;
				fa[y]=x, cnt[x]+=cnt[y], sum[x]+=sum[y];
				l[x]=min(l[x], l[y]);
				r[x]=max(r[x], r[y]);
				if(sum[x] > xx.s)
					xx=qwq{l[x], r[x], sum[x]};
			}
		}
		if(A+xx.s > ans[0].s+ans[1].s)
			ans[0]=qwq{1, n, A}, ans[1]=xx;
		srand(time(0));
		int gjnsao = 0;
		long long now = 0;
		for(int i = 0; i <= n; ++i) {
			int pppd = 0;
			if(1LL*rand()*rand()%1000 == 5) {
				++gjnsao;
				pppd=1;
			}
			if(gjnsao > 33) break;
			if(pppd == 0) {
				now+=b[i+1];
				if(bl[a[i+1]] == 0) continue;
				int ppp = bl[a[i+1]];
				vis[ppp]=0;
				if(sum[ppp] > xx.s)
					xx=qwq{ppp, ppp, sum[ppp]};
				if(ppp != 1 && vis[ppp-1] == 0) {
					int x = find(ppp), y = find(ppp-1);
					if(x != y) {
						if(cnt[x] < cnt[y]) swap(x, y);
						fa[y]=x, cnt[x]+=cnt[y], sum[x]+=sum[y];
						l[x]=min(l[x], l[y]);
						r[x]=max(r[x], r[y]);
						if(sum[x] > xx.s)
							xx=qwq{l[x], r[x], sum[x]};
					}
				}
				if(ppp != m && vis[ppp+1] == 0) {
					int x = find(ppp), y = find(ppp+1);
					if(x != y) {
						if(cnt[x] < cnt[y]) swap(x, y);
						fa[y]=x, cnt[x]+=cnt[y], sum[x]+=sum[y];
						l[x]=min(l[x], l[y]);
						r[x]=max(r[x], r[y]);
						if(sum[x] > xx.s)
							xx=qwq{l[x], r[x], sum[x]};
					}
				}
				continue;
			}
//			cout<<i<<"\n";
			for(int j = 1; j <= n+m; ++j)
				cpfa[j]=fa[j], cpcnt[j]=cnt[j], cpl[j]=l[j],
				cpr[j]=r[j], cpsum[j]=sum[j], cpvis[j]=vis[j];
			cpxx=xx;
			long long rt = 0;
			for(int j = n+1; j >= i+1; --j) {
				if(cpxx.s+A-now-rt > ans[0].s+ans[1].s)
					ans[0]=qwq{i+1, j-1, A-now-rt}, ans[1]=cpxx;
				rt+=b[j-1];
				if(bl[a[j-1]] == 0) continue;
				int ooo = bl[a[j-1]];
				cpvis[ooo]=0;
				if(cpsum[ooo] > cpxx.s)
					cpxx=qwq{ooo, ooo, cpsum[ooo]};
				if(ooo != 1 && cpvis[ooo-1] == 0) {
					int x = cpfind(ooo), y = cpfind(ooo-1);
					if(x != y) {
						if(cpcnt[x] < cpcnt[y]) swap(x, y);
						cpfa[y]=x, cpcnt[x]+=cpcnt[y], cpsum[x]+=cpsum[y];
						cpl[x]=min(cpl[x], cpl[y]);
						cpr[x]=max(cpr[x], cpr[y]);
	//					if(i+1 == 11 && j-1 >= 1721)
	//						cout<<cpl[x]<<" "<<cpr[x]<<" "<<cpsum[x]<<"\n";
						if(cpsum[x] > cpxx.s)
							cpxx=qwq{cpl[x], cpr[x], cpsum[x]};
					}
				}
				if(ooo != m && cpvis[ooo+1] == 0) {
					int x = cpfind(ooo), y = cpfind(ooo+1);
					if(x != y) {
						if(cpcnt[x] < cpcnt[y]) swap(x, y);
						cpfa[y]=x, cpcnt[x]+=cpcnt[y], cpsum[x]+=cpsum[y];
						cpl[x]=min(cpl[x], cpl[y]);
						cpr[x]=max(cpr[x], cpr[y]);
						if(cpsum[x] > cpxx.s)
							cpxx=qwq{cpl[x], cpr[x], cpsum[x]};
					}
				}
			}
			now+=b[i+1];
			if(bl[a[i+1]] == 0) continue;
			int ppp = bl[a[i+1]];
			vis[ppp]=0;
			if(sum[ppp] > xx.s)
				xx=qwq{ppp, ppp, sum[ppp]};
			if(ppp != 1 && vis[ppp-1] == 0) {
				int x = find(ppp), y = find(ppp-1);
				if(x != y) {
					if(cnt[x] < cnt[y]) swap(x, y);
					fa[y]=x, cnt[x]+=cnt[y], sum[x]+=sum[y];
					l[x]=min(l[x], l[y]);
					r[x]=max(r[x], r[y]);
					if(sum[x] > xx.s)
						xx=qwq{l[x], r[x], sum[x]};
				}
			}
			if(ppp != m && vis[ppp+1] == 0) {
				int x = find(ppp), y = find(ppp+1);
				if(x != y) {
					if(cnt[x] < cnt[y]) swap(x, y);
					fa[y]=x, cnt[x]+=cnt[y], sum[x]+=sum[y];
					l[x]=min(l[x], l[y]);
					r[x]=max(r[x], r[y]);
					if(sum[x] > xx.s)
						xx=qwq{l[x], r[x], sum[x]};
				}
			}
		}
		write(ans[0].s+ans[1].s), putchar('\n');
		write(ans[0].l), putchar(' '), write(ans[0].r), putchar('\n');
		write(ans[1].l), putchar(' '), write(ans[1].r), putchar('\n');
		return 0;
	}
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	for(int i = 1; i <= n; ++i)
		read(b[i]), pd[a[i]]=i, A+=b[i];
	for(int i = 1; i <= m; ++i)
		read(c[i]);
	for(int i = 1; i <= m; ++i)
		read(d[i]), B+=d[i], bl[c[i]]=i;
	if(A > B)
		ans[0]=qwq{1, n, A};
	else
		ans[1]=qwq{1, m, B}; 
	for(int i = 1; i <= m; ++i) {
		fa[i]=i, cnt[i]=1, sum[i]=d[i];
		l[i]=r[i]=i;
		if(pd[c[i]]) {
			vis[i]=1;
			continue;
		}
		if(sum[i] > xx.s)
			xx=qwq{i, i, sum[i]};
		if(i > 1 && vis[i-1] == 0) {
			int x = find(i-1), y = i;
			fa[y]=x, cnt[x]+=cnt[y], sum[x]+=sum[y];
			l[x]=min(l[x], l[y]);
			r[x]=max(r[x], r[y]);
			if(sum[x] > xx.s)
				xx=qwq{l[x], r[x], sum[x]};
		}
	}
	if(A+xx.s > ans[0].s+ans[1].s)
		ans[0]=qwq{1, n, A}, ans[1]=xx;
	long long now = 0;
	for(int i = 0; i <= n; ++i) {
		for(int j = 1; j <= n+m; ++j)
			cpfa[j]=fa[j], cpcnt[j]=cnt[j], cpl[j]=l[j],
			cpr[j]=r[j], cpsum[j]=sum[j], cpvis[j]=vis[j];
		cpxx=xx;
		long long rt = 0;
		for(int j = n+1; j >= i+1; --j) {
			if(cpxx.s+A-now-rt > ans[0].s+ans[1].s)
				ans[0]=qwq{i+1, j-1, A-now-rt}, ans[1]=cpxx;
			rt+=b[j-1];
			if(bl[a[j-1]] == 0) continue;
			int ooo = bl[a[j-1]];
			cpvis[ooo]=0;
			if(cpsum[ooo] > cpxx.s)
				cpxx=qwq{ooo, ooo, cpsum[ooo]};
			if(ooo != 1 && cpvis[ooo-1] == 0) {
				int x = cpfind(ooo), y = cpfind(ooo-1);
				if(x != y) {
					if(cpcnt[x] < cpcnt[y]) swap(x, y);
					cpfa[y]=x, cpcnt[x]+=cpcnt[y], cpsum[x]+=cpsum[y];
					cpl[x]=min(cpl[x], cpl[y]);
					cpr[x]=max(cpr[x], cpr[y]);
//					if(i+1 == 11 && j-1 >= 1721)
//						cout<<cpl[x]<<" "<<cpr[x]<<" "<<cpsum[x]<<"\n";
					if(cpsum[x] > cpxx.s)
						cpxx=qwq{cpl[x], cpr[x], cpsum[x]};
				}
			}
			if(ooo != m && cpvis[ooo+1] == 0) {
				int x = cpfind(ooo), y = cpfind(ooo+1);
				if(x != y) {
					if(cpcnt[x] < cpcnt[y]) swap(x, y);
					cpfa[y]=x, cpcnt[x]+=cpcnt[y], cpsum[x]+=cpsum[y];
					cpl[x]=min(cpl[x], cpl[y]);
					cpr[x]=max(cpr[x], cpr[y]);
					if(cpsum[x] > cpxx.s)
						cpxx=qwq{cpl[x], cpr[x], cpsum[x]};
				}
			}
		}
		now+=b[i+1];
		if(bl[a[i+1]] == 0) continue;
		int ppp = bl[a[i+1]];
		vis[ppp]=0;
		if(sum[ppp] > xx.s)
			xx=qwq{ppp, ppp, sum[ppp]};
		if(ppp != 1 && vis[ppp-1] == 0) {
			int x = find(ppp), y = find(ppp-1);
			if(x != y) {
				if(cnt[x] < cnt[y]) swap(x, y);
				fa[y]=x, cnt[x]+=cnt[y], sum[x]+=sum[y];
				l[x]=min(l[x], l[y]);
				r[x]=max(r[x], r[y]);
				if(sum[x] > xx.s)
					xx=qwq{l[x], r[x], sum[x]};
			}
		}
		if(ppp != m && vis[ppp+1] == 0) {
			int x = find(ppp), y = find(ppp+1);
			if(x != y) {
				if(cnt[x] < cnt[y]) swap(x, y);
				fa[y]=x, cnt[x]+=cnt[y], sum[x]+=sum[y];
				l[x]=min(l[x], l[y]);
				r[x]=max(r[x], r[y]);
				if(sum[x] > xx.s)
					xx=qwq{l[x], r[x], sum[x]};
			}
		}
	}
	write(ans[0].s+ans[1].s), putchar('\n');
	write(ans[0].l), putchar(' '), write(ans[0].r), putchar('\n');
	write(ans[1].l), putchar(' '), write(ans[1].r), putchar('\n');
	return 0;
}
