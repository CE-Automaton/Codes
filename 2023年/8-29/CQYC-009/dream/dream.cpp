#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N = 1e6+5;
int n, fa[N], fat[N], dep[N], sm[N]; 
struct qwq {
	int ls, rs;
}a[N], b[N];

char buf[(1<<21)+5],*p1,*p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
template <typename T> void read(T& x) {
	x = 0; int f = 0; char c = getchar();
	while(!isdigit(c)) f |= (c == '-'), c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x);
}
int lne; char put[105];
template <typename T> void write(T x, char ch) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
	putchar(ch);
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
int ksm(int x, int y, int ret = 1) {
	while(x) {
		if(x&1)
			ret=1LL*ret*y%mod;
		y=1LL*y*y%mod;
		x=(x>>1);
	}
	return ret;
}
void dfs(int x) {
//	cout<<x<<"->"<<b[x].ls<<"\n";
//	cout<<x<<"->"<<b[x].rs<<"\n";
	sm[x]=upd(sm[x]+dep[x]);
	if(b[x].ls)
		dep[b[x].ls]=dep[x]+1, dfs(b[x].ls);
	if(b[x].rs)
		dep[b[x].rs]=dep[x]+1, dfs(b[x].rs);
}
void xz(int now, int faa) {
	if(now == b[faa].ls) {
		b[faa].ls=b[now].rs;
		fat[b[now].rs]=faa;
		fat[now]=fat[faa];
		b[now].rs=faa;
		if(b[fat[faa]].ls == faa)
			b[fat[faa]].ls=now;
		else
			b[fat[faa]].rs=now;
		fat[faa]=now;
	}
	else{
		b[faa].rs=b[now].ls;
		fat[b[now].ls]=faa;
		fat[now]=fat[faa];
		b[now].ls=faa;
		if(b[fat[faa]].ls == faa)
			b[fat[faa]].ls=now;
		else
			b[fat[faa]].rs=now;
		fat[faa]=now;
	}
}

signed main() {
	freopen("dream.in", "r", stdin);
	freopen("dream.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i].ls), read(a[i].rs), fa[a[i].ls]=i, fa[a[i].rs]=i;
	fa[0]=0, fa[1]=0;
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j)
			fat[j]=fa[j], b[j]=a[j];
		int now = i;
		while(fat[now] != 0) {
			int faa = fat[now];
			if(fat[faa] == 0)
				xz(now, fat[now]);
			else
				if((faa == b[fat[faa]].ls && now == b[faa].ls) || (faa == b[fat[faa]].rs && now == b[faa].rs)) 
					xz(faa, fat[faa]), xz(now, fat[now]);
				else
					xz(now, fat[now]), xz(now, fat[now]);
		}
		dep[i]=0;
		dfs(i);
//		puts("!!!");
	}
	for(int i = 1; i <= n; ++i)
		write(sm[i], '\n');
	return 0;
}
