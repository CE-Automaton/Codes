#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int n, m, col[2][N], tot, u, v, ans, nxt[2][N];
char s[2][N];
struct qwq {
	int x, y;
}jp[2][N][25];

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
	freopen("family.in", "r", stdin);
	freopen("family.out", "w", stdout);
	read(n), read(m);
	scanf("%s\n%s", s[0]+1, s[1]+1);
	for(int j = 1; j <= n; ++j) {
		if(s[0][j] == 'X' && s[1][j] == 'X') continue;
		if((s[0][j] == '.' && col[0][j] != 0) || (s[1][j] == '.' && col[1][j] != 0)) {
			int now = (col[0][j] ? col[0][j] : col[1][j]);
			if(s[0][j] == '.') {
				col[0][j]=now;
				if(s[0][j+1] == '.')
					col[0][j+1]=now;
			}
			if(s[1][j] == '.') {
				col[1][j]=now;
				if(s[1][j+1] == '.')
					col[1][j+1]=now;
			}
		}
		else {
			int now = (++tot);
			if(s[0][j] == '.') {
				col[0][j]=now;
				if(s[0][j+1] == '.')
					col[0][j+1]=now;
			}
			if(s[1][j] == '.') {
				col[1][j]=now;
				if(s[1][j+1] == '.')
					col[1][j+1]=now;
			}
		}
	}
//	for(int o = 0; o <= 1; ++o) {
//		for(int j = 1; j <= n; ++j) {
//			cout<<col[o][j]<<" ";
//		}
//		puts("");
//	}
	for(int o = 0; o <= 1; ++o) {
		int lst = 1;
		for(int j = 1; j <= n; ++j) 
			if(s[o][j] == 'X') {
				for(int i = lst; i <= j; ++i) {
					if(s[o^1][i] == 'X')
						jp[o^1][i][0]=qwq {o, j};
					nxt[o][i]=j;
				}
				lst=j+1;
			}
	}
	for(int i = 1; i <= 20; ++i) 
		for(int o = 0; o <= 1; ++o)
			for(int j = 1; j <= n; ++j)
				if(s[o][j] == 'X') {
					qwq az = jp[o][j][i-1];
					jp[o][j][i]=jp[az.x][az.y][i-1];
				}
	for(int i = 1; i <= m; ++i) {
		read(u), read(v);
		qwq ou = qwq {(u-1)/n, (u-1)%n+1}, ov = qwq {(v-1)/n, (v-1)%n+1};
		if(ou.y > ov.y)
			swap(ou, ov);
		if(col[ou.x][ou.y] != col[ov.x][ov.y]) {
			puts("-1");
			continue;
		}
		if(nxt[ou.x][ou.y] > ov.y || nxt[ou.x][ou.y] == 0) {
			if(ou.x != ov.x)
				write(ov.y-ou.y+1, '\n');
			else
				write(ov.y-ou.y, '\n');
		}
		else {
			int gs = 1;
			qwq op = qwq {ou.x, nxt[ou.x][ou.y]};
			for(int i = 20; i >= 0; --i) {
				qwq to = jp[op.x][op.y][i];
//				cout<<to.y<<"!?\n";
				if(to.y != 0 && to.y < ov.y)
					op=to, gs+=(1<<i);
			}
//			cout<<ou.y<<" "<<ov.y<<" "<<gs<<" "<<op.x<<' '<<op.y<<" "<<jp[op.x][op.y][0].y<<"\n";
			if(op.x == ov.x)
				write(ov.y-ou.y+1+gs, '\n');
			else
				write(ov.y-ou.y+gs, '\n');
		}
	}
	return 0;
}
