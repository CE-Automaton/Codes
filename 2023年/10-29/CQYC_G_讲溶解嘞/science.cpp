#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int n, a[N], pd[5], ans[N], b[N], lnn[N], tot, c[N], tt[N], l, r;
long long sss;
char s[15];

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
void dfs(int x) {
	if(x == r+1) {
		long long s = 0, now = 0;
		for(int i = l; i <= r; ++i)
			if(tt[i] == 1) {
				s+=now+c[i-1];
				now=b[i];
			}
			else 
				now*=1LL*b[i];
		s+=now+c[tot];
		if(s > sss) {
			sss=s;
			for(int i = l; i <= r; ++i)
				ans[i]=tt[i];
		}
		return ;
	}
	tt[x]=1;//表示直接加
	dfs(x+1);
	tt[x]=0, dfs(x+1);//和前面的连起来 
}

signed main() {
	freopen("science.in", "r", stdin);
	freopen("science.out", "w", stdout);
	puts("\n"); 
	return 0;
}
