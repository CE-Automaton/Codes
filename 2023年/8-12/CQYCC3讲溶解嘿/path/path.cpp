#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+5;
int n, m, s, t, a, trxl[N], trxr[N], tryl[N], tryr[N], sum;
struct qwq {
	int x, y;
}pnt[N];

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
void add_trxl(int x, int w) {
	while(x <= m)
		trxl[x]=max(trxl[x], w), x+=(x&(-x));
}
void add_trxr(int x, int w) {
	while(x >= 1)
		trxr[x]=min(trxr[x], w), x-=(x&(-x));
}
void add_tryl(int x, int w) {
	while(x <= n)
		tryl[x]=max(tryl[x], w), x+=(x&(-x));
}
void add_tryr(int x, int w) {
	while(x >= 1)
		tryr[x]=min(tryr[x], w), x-=(x&(-x));
}

int ask_trxl(int x, int ret = 0) {
	while(x >= 1)
		ret=max(trxl[x], ret), x-=(x&(-x));
	return ret;
}
int ask_trxr(int x, int ret = N) {
	while(x <= m)
		ret=min(trxr[x], ret), x+=(x&(-x));
	return ret;
}
int ask_tryl(int x, int ret = 0) {
	while(x >= 1)
		ret=max(tryl[x], ret), x-=(x&(-x));
	return ret;
}
int ask_tryr(int x, int ret = N) {
	while(x <= n)
		ret=min(tryr[x], ret), x+=(x&(-x));
	return ret;
}

signed main() {
	freopen("path.in", "r", stdin);
	freopen("path.out", "w", stdout);
	read(n), read(m);
	if(n == 1 || m == 1) {
		write(n*m, '\n');
		return 0;
	}
	for(int i = 1; i <= n; ++i) 
		for(int j = 1; j <= m; ++j) {
			read(a), pnt[a]=qwq {i, j};
			if(i == 1 && j == 1)
				s=a;
			if(i == n && j == m)
				t=a;
		}
	for(int i = 1; i <= n; ++i)
		tryr[i]=N;
	for(int i = 1; i <= m; ++i)
		trxr[i]=N;
	add_trxl(1, pnt[s].x);
	add_trxr(1, pnt[s].x);
	add_tryl(1, pnt[s].y);
	add_tryr(1, pnt[s].y);
	
	add_trxl(m, pnt[t].x);
	add_trxr(m, pnt[t].x);
	add_tryl(n, pnt[t].y);
	add_tryr(n, pnt[t].y);
	for(int ans = 0; ans <= n*m-1; ++ans) {
		if(ans == s || ans == t) continue;
		int xl = ask_trxl(pnt[ans].y), xr = ask_trxr(pnt[ans].y), 
		yl = ask_tryl(pnt[ans].x), yr = ask_tryr(pnt[ans].x), pd = 1;
//		cout<<xl<<" "<<xr<<" "<<yl<<" "<<yr<<" "<<ans<<"? "<<pnt[ans].x<<" "<<pnt[ans].y<<"\n";
		if((xl > xr && xr <= pnt[ans].x && pnt[ans].x <= xl) || (xl == pnt[ans].x && xr == xl)) 
			pd=0;
		if((yl > yr && yr <= pnt[ans].y && pnt[ans].y <= yl) || (yl == pnt[ans].y && yr == yl)) 
			pd=0;
		if(pd)
			sum=max(sum, ans);
		xl = ask_trxl(pnt[ans].y-1), xr = ask_trxr(pnt[ans].y+1), 
		yl = ask_tryl(pnt[ans].x-1), yr = ask_tryr(pnt[ans].x+1);
//		cout<<xl<<" "<<xr<<" "<<yl<<" "<<yr<<" "<<ans<<"? "<<pnt[ans].x<<" "<<pnt[ans].y<<"\n";
		if(xl > pnt[ans].x || pnt[ans].x > xr || yl > pnt[ans].y || pnt[ans].y > yr)
			break;
//		cout<<ans<<"!\n";
		add_trxl(pnt[ans].y, pnt[ans].x);
		add_trxr(pnt[ans].y, pnt[ans].x);
		add_tryl(pnt[ans].x, pnt[ans].y);
		add_tryr(pnt[ans].x, pnt[ans].y);
	}
	write(sum, '\n');
	return 0;
}
