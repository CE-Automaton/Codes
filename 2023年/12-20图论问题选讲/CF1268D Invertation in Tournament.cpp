#include <bits/stdc++.h>
using namespace std;
const int N = 2e3+3, M = 4e6+5;
int n, cnt=1, fir[N], to[M], nxt[M], val[M], mn=7, ans, 
vis[N], gs, pp[15], ll, pdd[15], out[N], a[N];
char s[N][N];

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
void edge(int x, int y, int w) {
	nxt[++cnt]=fir[x], val[cnt]=w, to[cnt]=y, fir[x]=cnt, out[x]+=w;
	nxt[++cnt]=fir[y], val[cnt]=(w^1), to[cnt]=x, fir[y]=cnt, out[y]+=(w^1);
}
int sol() {
	for(int i = 1; i <= n; ++i)
		a[i]=out[i];
	sort(a+1, a+1+n);
	for(int i = 1, j = 0; i < n; ++i) {
		j+=a[i];
		if(j == i*(i-1)/2)
			return 0;
	}
	return 1;
}
void cl(int x) {
	for(int i = fir[x]; i; i=nxt[i])
		out[x]-=val[i], val[i]^=1, out[x]+=val[i], 
		out[to[i]]-=val[i^1], val[i^1]^=1, out[to[i]]+=val[i^1];
}

signed main() {
	read(n);
	for(int i = 1; i <= n; ++i)
		scanf("%s", s[i]+1);
	for(int i = 1; i <= n; ++i)
		for(int j = i+1; j <= n; ++j)
			edge(i, j, s[i][j]-'0');
	if(sol()) {
		write(0, ' ');
		write(1, '\n');
		return 0;
	}
	if(n <= 6) {
		for(int i = 1; i <= (1<<n)-1; ++i) {
			ll=0;
			for(int j = 0; j <= n-1; ++j)
				if((i>>j)&1)
					pp[++ll]=j+1;
			if(ll > mn) continue;
			for(int j = 1; j <= ll; ++j)
				cl(pp[j]);
			int rt = sol();
			for(int j = 1; j <= ll; ++j)
				cl(pp[j]);
			if(!rt) continue;
			for(int j = 2; j <= ll;	++j)
				rt*=j;
			if(mn == ll) 
				ans+=rt;
			else 
				mn=ll, ans=rt;
		}
		if(mn == 7) {
			puts("-1");
			return 0;
		}
		write(mn, ' ');
		write(ans, '\n');
		return 0;
	}
	mn=1;
	for(int i = 1; i <= n; ++i)
		cl(i), ans+=sol(), cl(i);
	if(ans == 0) {
		puts("-1");
		return 0;
	}
	write(mn, ' ');
	write(ans, '\n');
	return 0;
}
