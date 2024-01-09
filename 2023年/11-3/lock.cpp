#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int n, m, u, a[N], ans;
char s[N], v;
struct tree {
	int tr[N<<2], sm[2][N<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	void upup(int k) {
		sm[0][k]=sm[0][ls]+sm[0][rs];
		sm[1][k]=sm[1][ls]+sm[1][rs];
		tr[k]=min(tr[ls]+sm[0][rs], tr[rs]+sm[1][ls]);
	}
	void built(int k, int l, int r) {
		if(l == r) {
			sm[a[l]][k]=1;
			tr[k]=0;
			return ;
		}
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
		upup(k);
	}
	void updt(int k, int l, int r, int tt, int w) {
		if(l == r) {
			sm[w][k]=1;
			sm[w^1][k]=0;
			tr[k]=0;
			return ;
		}
		int mid = ((l+r)>>1);
		if(tt <= mid)
			updt(ls, l, mid, tt, w);
		else
			updt(rs, mid+1, r, tt, w);
		upup(k);
	}
}A[27];

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

signed main() {
	scanf("%s", s+1);
	n=strlen(s+1);
	for(int i = 0; i <= 25; ++i) {
		for(int j = 1; j <= n; ++j)
			a[j]=(s[j]-'a' >= i);
		A[i].built(1, 1, n);
		ans+=A[i].tr[1];
	}
	write(ans, '\n');
	read(m);
	for(int i = 1; i <= m; ++i) {
		read(u), scanf(" %c", &v);
		s[u]=v;
		ans=0;
		for(int i = 0; i <= 25; ++i)
			A[i].updt(1, 1, n, u, (s[u]-'a' >= i)), ans+=A[i].tr[1];
		write(ans, '\n');
	}
	return 0;
}
