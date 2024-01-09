#include <bits/stdc++.h>
using namespace std;
const int N = 5e2+5, Q = 6e4+5;
int n, q, a[N][N], cnt, ans[Q], now, bit[N][N];
struct node {
	int x, y, w;
}b[N*N];
struct pro {
	int sx, sy, fx, fy, k, id;
}que[Q], aa[Q], bb[Q];

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
int comp(node A, node B) {
	return A.w < B.w;
}
void add(int x, int y, int w) {
	for(int i = x; i <= n; i=i+(i&(-i)))
		for(int j = y; j <= n; j=j+(j&(-j)))
			bit[i][j]+=w;
}
int ask(int x, int y, int ret=0) {
	if(!x || !y)
		return 0;
	for(int i = x; i >= 1; i=i-(i&(-i)))
		for(int j = y; j >= 1; j=j-(j&(-j)))
			ret+=bit[i][j];
	return ret;
}
void solve(int l, int r, int L, int R) {
	if(l > r || L > R) 
		return ;
	int mid = ((l+r)>>1), ll = 0, rr = 0;
	while(now < mid)
		++now, add(b[now].x, b[now].y, 1);
	while(now > mid)
		add(b[now].x, b[now].y, -1), --now;
	for(int i = L; i <= R; ++i) {
		int w = ask(que[i].fx, que[i].fy)-ask(que[i].fx, que[i].sy-1)
		-ask(que[i].sx-1, que[i].fy)+ask(que[i].sx-1, que[i].sy-1);
//		cout<<b[mid].w<<" "<<w<<" "<<que[i].k<<"!?\n";
		if(w >= que[i].k)
			ans[que[i].id]=b[mid].w, aa[++ll]=que[i];
		else
			bb[++rr]=que[i];
	}
	for(int i = 1; i <= ll; ++i)
		que[i+L-1]=aa[i];
	for(int i = 1; i <= rr; ++i)
		que[i+L+ll-1]=bb[i];
	solve(l, mid-1, L, L+ll-1);
	solve(mid+1, r, L+ll, R);
}

signed main() {
	read(n), read(q);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			read(a[i][j]), b[++cnt]=node {i, j, a[i][j]};
	sort(b+1, b+1+cnt, comp);
	for(int i = 1; i <= q; ++i)
		read(que[i].sx), read(que[i].sy), read(que[i].fx), read(que[i].fy), read(que[i].k), que[i].id=i;
	solve(1, cnt, 1, q);
	for(int i = 1; i <= q; ++i)
		write(ans[i], '\n');
	return 0;
}
