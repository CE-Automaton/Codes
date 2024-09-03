#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
#define inf 1000000007
using namespace std;
typedef long long LL;
const int N = 2e6+5;
int n, gs[2], a[2][N], tp[2], siz[2], b[2][N], anst, nowt[N][2], ans, now[N][2];
char s[N], t[N];

template <typename T> inline void debug(T x) { cerr<<x; }
template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
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
void sswapp(int x, int y, int pd) {
	++ans;
	int xx = (x ? a[0][tp[0]] : 0), yy = (y ? a[1][tp[1]] : 0);
	now[ans][0]=(pd ? siz[0]-xx : xx);
	now[ans][1]=(pd ? siz[1]-yy : yy);
	siz[0]=siz[0]-xx+yy;
	siz[1]=siz[1]-yy+xx;
	if(x)
		++tp[0];
	if(tp[0] > gs[0])
		--tp[0], a[0][tp[0]]=yy;
	else
		a[0][tp[0]]+=yy;
	if(y)
		++tp[1];
	if(tp[1] > gs[1])
		--tp[1], a[1][tp[1]]=xx;
	else
		a[1][tp[1]]+=xx;
}

signed main() {
	File("sort");
	scanf("%s", s+1);
	n=strlen(s+1);
	for(int i = 1; i <= n; ++i) {
		int j = i; 
		while(j+1 <= n && s[j+1] == s[i]) ++j;
		a[0][++gs[0]]=j-i+1;
		b[0][gs[0]]=(s[i] == 'a' ? 0 : 1);
		i=j;
	}
	tp[0]=1;
	siz[0]=n;
	scanf("%s", t+1);
	n=strlen(t+1);
	for(int i = 1; i <= n; ++i) {
		int j = i; 
		while(j+1 <= n && t[j+1] == t[i]) ++j;
		a[1][++gs[1]]=j-i+1;
		b[1][gs[1]]=(t[i] == 'a' ? 0 : 1);
		i=j;
	}

	if(gs[0] == 1 && gs[1] == 1) {
		puts("0");
		return 0;
	}

	tp[1]=1;
	siz[1]=n;
	anst=inf;
	if(b[0][1] == b[1][1]) {
		if(gs[0] < gs[1]) 
			sswapp(0, 1, 0);
		else 
			sswapp(1, 0, 0);
	}
	while(gs[0] != tp[0] || gs[1] != tp[1]) 
		sswapp(1, 1, 0);
	if(ans < anst) {
		anst=ans;
		for(int i = 1; i <= ans; ++i)
			nowt[i][0]=now[i][0], nowt[i][1]=now[i][1];
	}

	n=strlen(s+1);
	reverse(s+1, s+1+n);
	gs[0]=0;
	for(int i = 1; i <= n; ++i) {
		int j = i; 
		while(j+1 <= n && s[j+1] == s[i]) ++j;
		a[0][++gs[0]]=j-i+1;
		b[0][gs[0]]=(s[i] == 'a' ? 0 : 1);
		i=j;
	}
	tp[0]=1;
	siz[0]=n;

	n=strlen(t+1);
	reverse(t+1, t+1+n);
	gs[1]=0;
	for(int i = 1; i <= n; ++i) {
		int j = i; 
		while(j+1 <= n && t[j+1] == t[i]) ++j;
		a[1][++gs[1]]=j-i+1;
		b[1][gs[1]]=(t[i] == 'a' ? 0 : 1);
		i=j;
	}
	tp[1]=1;
	siz[1]=n;

	ans=0;
	if(b[0][1] == b[1][1]) {
		if(gs[0] < gs[1]) 
			sswapp(0, 1, 1);
		else 
			sswapp(1, 0, 1);
	}
	while(gs[0] != tp[0] || gs[1] != tp[1]) 
		sswapp(1, 1, 1);
	if(ans < anst) {
		anst=ans;
		for(int i = 1; i <= ans; ++i)
			nowt[i][0]=now[i][0], nowt[i][1]=now[i][1];
	}
	write(anst, '\n');
	for(int i = 1; i <= anst; ++i)
		write(nowt[i][0], ' '), write(nowt[i][1], '\n');
	return 0;
}