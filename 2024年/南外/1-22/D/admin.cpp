#include<bits/stdc++.h>

using namespace std;
#define ll long long

const int N = 100005;
const ll inf = 1e18;
int n, q, h[N], w[N], ww[N];
ll p[N], ans[N], g[4][N][5], f[4][N][4][3];
struct item{
	int l, r, id;
} a[N], b[N];
int calc(int x){ return x-(x>1);}
int calc2(int x, int i){
	return (x&1)*w[i]+(x>>1&1)*ww[i];
}
void update(ll &x, ll y){ x=min(x, y);}
void solve(int l, int r, int ql, int qr){
	if(l==r){
		for(int i=ql; i<=qr; ++i) ans[a[i].id]=2*(w[l]+h[l]);
		return;
	}
	int mid=(l+r)>>1;
	for(int x=0; x<4; ++x) for(int i=l; i<=r; ++i) for(int t=0; t<3; ++t){
		g[x][i][t]=inf;
		for(int j=0; j<4; ++j) f[x][i][j][t]=inf;
	}
	for(int x=0; x<4; ++x){
		auto F=f[x];
		auto G=g[x];
		F[mid+1][x][0]=calc2(x, mid+1);
		for(int i=mid+2; i<r; ++i) for(int j=0; j<4; ++j) for(int t=0; t<3; ++t)
			for(int k=0; k<4; ++k) for(int s=0; s<4; s+=3) if(t+calc(j^k^s^3)<3)
				update(F[i][j][t+calc(j^k^s^3)], F[i-1][k][t]+calc2(j, i)+(s&1)*min(h[i-1], h[i]));
		F[mid][x][0]=calc2(x, mid);
		for(int i=mid-1; i>l; --i) for(int j=0; j<4; ++j) for(int t=0; t<3; ++t)
			for(int k=0; k<4; ++k) for(int s=0; s<4; s+=3) if(t+calc(j^k^s^3)<3)
				update(F[i][j][t+calc(j^k^s^3)], F[i+1][k][t]+calc2(j, i)+(s&1)*min(h[i+1], h[i]));
		for(int j=0; j<4; ++j) for(int t=0; t<3; ++t){
			for(int i=mid+1; i<r; ++i)
				update(G[i+1][t+calc(j^3)], F[i][j][t]),
				update(G[i+1][t+calc(j)], F[i][j][t]+min(h[i], h[i+1]));
			for(int i=mid; i>l; --i)
				update(G[i-1][t+calc(j^3)], F[i][j][t]),
				update(G[i-1][t+calc(j)], F[i][j][t]+min(h[i], h[i-1]));
		}
	}
	g[0][mid+1][0]=g[0][mid][0]=0;
	int qll=ql-1, qrr=qr+1;
	for(int i=ql; i<=qr; ++i)
		if(a[i].r<=mid) a[++qll]=a[i];
		else if(a[i].l>mid) b[--qrr]=a[i];
		else{
			ll &Ans=ans[a[i].id]=inf;
			for(int x=0; x<4; ++x) for(int j=0; j<3; ++j)
				for(int y=0; y<4; ++y) for(int k=0; k<3; ++k)
					for(int s=0; s<4; s+=3) if(j+k+calc(x^y^s^3)<3)
						update(Ans, g[x][a[i].l][j]+g[y][a[i].r][k]+(s&1)*min(h[mid], h[mid+1]));
			Ans+=p[a[i].r]-p[a[i].l-1]+min(h[a[i].l], h[a[i].l-1]);
		}
	for(int i=qrr; i<=qr; ++i) a[i]=b[i];
	solve(l, mid, ql, qll), solve(mid+1, r, qrr, qr);
}
int main() {
	freopen("huffman.in", "r", stdin);
	freopen("huffman.out", "w", stdout);
	scanf("%d%d", &n, &q);
	for(int i=1; i<=n; ++i) scanf("%d", h+i);
	for(int i=1; i<=n; ++i) scanf("%d", w+i), p[i]=p[i-1]+2*(w[i]+h[i])-min(h[i], h[i-1]);
	for(int i=2; i<n; ++i) ww[i]=w[i]+max(h[i]-h[i-1], 0)+max(h[i]-h[i+1], 0);
	for(int i=1; i<=q; ++i) scanf("%d%d", &a[i].l, &a[i].r), a[i].id=i;
	solve(1, n, 1, q);
	for(int i=1; i<=q; ++i) printf("%lld\n", ans[i]);
	return 0;
}
