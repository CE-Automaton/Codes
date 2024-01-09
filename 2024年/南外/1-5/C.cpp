#include <bits/stdc++.h>
using namespace std;
const int N = 1e3+5;
int n, la, lb[N], f[N][N], lst[N], nw[N], w[N], op[N], gs[2][N], sum[2][N], ans;
char a[N], b[N][N];

template <typename T> inline void debug(T x) { cerr<<x<<'\n'; }
template <typename T, typename ...T_> inline void debug(T &x, T_ &...p) { cerr<<x<<' ', debug(p...); }
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
int comp(int A, int B) {
	if(op[A] == op[B])
		return lst[A] < lst[B];
	return op[A] < op[B];
}

signed main() {
	freopen("digits.in", "r", stdin);
	freopen("digits.out", "w", stdout);
	scanf("%s", a+1);
	la=strlen(a+1);
	reverse(a+1, a+1+la);
	read(n);
	for(int i = 1; i <= n; ++i) 
		scanf("%s", b[i]+1), lb[i]=strlen(b[i]+1), 
		reverse(b[i]+1, b[i]+1+lb[i]), nw[i]=i;
	for(int i = 0; i <= 9; ++i) 
		read(w[i]);
	memset(f, -0x3f, sizeof f);
	f[0][n]=0;
	for(int i = 1; i <= 1001; ++i) {
		for(int j = 1; j <= n; ++j)
			op[j]=(lb[j] < i ? 0 : b[j][i]-'0');
		int st = 0, fn = 9;
		if(i > la) st=fn=0;
		else if(a[i] != '?') st=fn=a[i]-'0';
		else if(i == la) st=max(st, 1);
		for(int x = st; x <= fn; ++x) {
			for(int k = 1, j = nw[1]; k <= n; ++k, j=nw[k])
				gs[0][k]=gs[0][k-1]+(op[j]+x <= 9), 
				sum[0][k]=sum[0][k-1]+(i <= la || i <= lb[j] ? w[(op[j]+x)%10] : 0);
			for(int k = n, j = nw[n]; k >= 1; --k, j=nw[k])
				gs[1][k]=gs[1][k+1]+(op[j]+x+1 <= 9), 
				sum[1][k]=sum[1][k+1]+w[(op[j]+x+1)%10];
			for(int j = 0; j <= n; ++j)
				f[i][gs[0][j]+gs[1][j+1]]=max(f[i][gs[0][j]+gs[1][j+1]], f[i-1][j]+sum[0][j]+sum[1][j+1]);
		}
		for(int j = 1; j <= n; ++j)
			lst[nw[j]]=j, nw[j]=j;
		sort(nw+1, nw+1+n, comp);
	}
	ans=-0x3f3f3f3f;
	for(int i = 0; i <= n; ++i)
		ans=max(ans, f[1001][i]);
	write(ans, '\n');
	return 0;
}
