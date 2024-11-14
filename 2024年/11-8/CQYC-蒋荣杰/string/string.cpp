#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
const int N = 1e6+5;
int n, gs[5], gss[5], xxx[N], yyy[N], ans;
char s[N], t[N], ttt[N];
map <pii, int> qwq, viss[5];

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
int sol() {
	ans=0;
	int aa = 0, bb = 0, a = 0, b = 0;
	char A = 'A', B = 'B', C = 'C';
	if(gs[1] < n) 
		A='B', B='C', C='A', aa = gs[2]-n, bb = gs[3]-n;
	if(gs[2] < n)
		A='A', B='C', C='B', aa = gs[1]-n, bb = gs[3]-n;
	if(gs[3] < n)
		A='A', B='B', C='C', aa = gs[1]-n, bb = gs[2]-n;
	qwq.clear();
	qwq[pii{0,0}]=0;
	for(int i = 1; i <= n+n+n; ++i) {
		if(s[i] == A)
			++a;
		if(s[i] == B)
			++b;
		if(qwq.find(pii {a-aa, b-bb}) != qwq.end()) {
			++ans;
			xxx[ans]=qwq[pii{a-aa, b-bb}]+1;
			yyy[ans]=i;
			ttt[ans]=C;
			return 1;
		}
		qwq[pii{a,b}]=i;
	}
	return 0;
}
int cccnt(int xx, int yy, int zz) {
	return (xx >= n)+(yy >= n)+(zz >= n);
}

signed main() {
	File("string");
	read(n);
	scanf("%s", s+1);
	write(n, '\n');
	for(int i = 1; i <= n+n+n; ++i)
		++gs[s[i]-'A'+1], putchar(s[i]);
	putchar('\n');
	int op = 0;
	for(int i = 1; i <= 3; ++i)
		op+=(gs[i] >= n);
	if(op == 3) {
		puts("0");
		return 0;
	}
	if(op == 2 && sol()) {
		puts("1");
		write(xxx[1], ' '), write(yyy[1], ' '), putchar(ttt[1]), putchar('\n');
		return 0;
	}
	// if(n <= 3000) {
	// 	for(int i = 1; i <= n+n+n; ++i) {
	// 		++gss[s[i]-'A'+1];
	// 		if(cccnt(gs[1]+gss[2]+gss[3], gs[2]-gss[2], gs[3]-gss[3]) == 2) {
	// 			for(int j = 1; j <= i; ++j)
	// 				t[j]='A', swap(t[j], s[j]);
	// 			gs[1]=gs[1]+gss[2]+gss[3], gs[2]-=gss[2], gs[3]-=gss[3];
	// 			if(sol()) {
	// 				puts("2");
	// 				write(1, ' '), write(i, ' ');
	// 				putchar('A'), putchar('\n');
	// 				write(xxx[1], ' '), write(yyy[1], ' '), putchar(ttt[1]), putchar('\n');
	// 				return 0;
	// 			}
	// 			for(int j = 1; j <= i; ++j)
	// 				swap(t[j], s[j]);
	// 			gs[1]-=gss[2]+gss[3], gs[2]+=gss[2], gs[3]+=gss[3];
	// 		}
	// 		if(cccnt(gs[1]-gss[1], gs[2]+gss[1]+gss[3], gs[3]-gss[3]) == 2) {
	// 			for(int j = 1; j <= i; ++j)
	// 				t[j]='B', swap(t[j], s[j]);
	// 			gs[1]-=gss[1], gs[2]=gs[2]+gss[1]+gss[3], gs[3]-=gss[3];
	// 			if(sol()) {
	// 				puts("2");
	// 				write(1, ' '), write(i, ' ');
	// 				putchar('B'), putchar('\n');
	// 				write(xxx[1], ' '), write(yyy[1], ' '), putchar(ttt[1]), putchar('\n');
	// 				return 0;
	// 			}
	// 			for(int j = 1; j <= i; ++j)
	// 				swap(t[j], s[j]);
	// 			gs[1]+=gss[1], gs[2]-=gss[1]+gss[3], gs[3]+=gss[3];
	// 		}
	// 		if(cccnt(gs[1]-gss[1], gs[2]-gss[2], gs[3]+gss[2]+gss[1]) == 2) {
	// 			for(int j = 1; j <= i; ++j)
	// 				t[j]='C', swap(t[j], s[j]);
	// 			gs[1]-=gss[1], gs[2]-=gss[2], gs[3]=gs[3]+gss[2]+gss[1];
	// 			if(sol()) {
	// 				puts("2");
	// 				write(1, ' '), write(i, ' ');
	// 				putchar('C'), putchar('\n');
	// 				write(xxx[1], ' '), write(yyy[1], ' '), putchar(ttt[1]), putchar('\n');
	// 				return 0;
	// 			}
	// 			for(int j = 1; j <= i; ++j)
	// 				swap(t[j], s[j]);
	// 			gs[1]+=gss[1], gs[2]+=gss[2], gs[3]-=gss[2]+gss[1];
	// 		}
	// 	}
	// 	gss[1]=gss[2]=gss[3]=0;
	// }
	viss[0][pii{0,0}]=n+n+n+1;
	viss[1][pii{0,0}]=n+n+n+1;
	viss[2][pii{0,0}]=n+n+n+1;
	for(int i = n+n+n; i >= 1; --i) {
		++gss[s[i]-'A'+1];
		if(viss[0].find(pii{gss[1], gss[2]}) == viss[0].end())
			viss[0][pii{gss[1], gss[2]}]=i;
		if(viss[1].find(pii{gss[1], gss[3]}) == viss[1].end())
			viss[1][pii{gss[1], gss[3]}]=i;
		if(viss[2].find(pii{gss[2], gss[3]}) == viss[2].end())
			viss[2][pii{gss[2], gss[3]}]=i;
	}
	gss[1]=gss[2]=gss[3]=0;
	for(int i = 1; i <= n+n+n; ++i) {
		++gss[s[i]-'A'+1];
		if(cccnt(gs[1]+gss[2]+gss[3], gs[2]-gss[2], gs[3]-gss[3]) == 3) {
			puts("1");
			write(1, ' '), write(i, ' '), putchar('A'), putchar('\n');
			return 0;
		}
		if(cccnt(gs[1]-gss[1], gs[2]+gss[1]+gss[3], gs[3]-gss[3]) == 3) {
			puts("1");
			write(1, ' '), write(i, ' '), putchar('B'), putchar('\n');
			return 0;
		}
		if(cccnt(gs[1]-gss[1], gs[2]-gss[2], gs[3]+gss[2]+gss[1]) == 3) {
			puts("1");
			write(1, ' '), write(i, ' '), putchar('C'), putchar('\n');
			return 0;
		}
		if(cccnt(gs[1]+gss[2]+gss[3], gs[2]-gss[2], gs[3]-gss[3]) == 2) {
			gs[1]=gs[1]+gss[2]+gss[3], gs[2]-=gss[2], gs[3]-=gss[3];
			if(gs[1] < n && viss[2].find(pii {gs[2]-n, gs[3]-n}) != viss[2].end() && viss[2][pii {gs[2]-n, gs[3]-n}] > i) {
				puts("2");
				write(1, ' '), write(i, ' '), putchar('A'), putchar('\n');
				write(viss[2][pii {gs[2]-n, gs[3]-n}], ' '), write(n+n+n, ' '), putchar('A'), putchar('\n');
				return 0;
			}
			if(gs[2] < n && viss[1].find(pii {gs[1]-n, gs[3]-n}) != viss[1].end() && viss[1][pii {gs[1]-n, gs[3]-n}] > i) {
				puts("2");
				write(1, ' '), write(i, ' '), putchar('A'), putchar('\n');
				write(viss[1][pii {gs[1]-n, gs[3]-n}], ' '), write(n+n+n, ' '), putchar('B'), putchar('\n');
				return 0;
			}
			if(gs[3] < n && viss[0].find(pii {gs[1]-n, gs[2]-n}) != viss[0].end() && viss[0][pii {gs[1]-n, gs[2]-n}] > i) {
				puts("2");
				write(1, ' '), write(i, ' '), putchar('A'), putchar('\n');
				write(viss[0][pii {gs[1]-n, gs[2]-n}], ' '), write(n+n+n, ' '), putchar('C'), putchar('\n');
				return 0;
			}
			gs[1]=gs[1]-gss[2]-gss[3], gs[2]+=gss[2], gs[3]+=gss[3];
		}

		if(cccnt(gs[1]-gss[1], gs[2]+gss[1]+gss[3], gs[3]-gss[3]) == 2) {
			gs[1]-=gss[1], gs[2]+=gss[1]+gss[3], gs[3]-=gss[3];
			if(gs[1] < n && viss[2].find(pii {gs[2]-n, gs[3]-n}) != viss[2].end() && viss[2][pii {gs[2]-n, gs[3]-n}] > i) {
				puts("2");
				write(1, ' '), write(i, ' '), putchar('B'), putchar('\n');
				write(viss[2][pii {gs[2]-n, gs[3]-n}], ' '), write(n+n+n, ' '), putchar('A'), putchar('\n');
				return 0;
			}
			if(gs[2] < n && viss[1].find(pii {gs[1]-n, gs[3]-n}) != viss[1].end() && viss[1][pii {gs[1]-n, gs[3]-n}] > i) {
				puts("2");
				write(1, ' '), write(i, ' '), putchar('B'), putchar('\n');
				write(viss[1][pii {gs[1]-n, gs[3]-n}], ' '), write(n+n+n, ' '), putchar('B'), putchar('\n');
				return 0;
			}
			if(gs[3] < n && viss[0].find(pii {gs[1]-n, gs[2]-n}) != viss[0].end() && viss[0][pii {gs[1]-n, gs[2]-n}] > i) {
				puts("2");
				write(1, ' '), write(i, ' '), putchar('B'), putchar('\n');
				write(viss[0][pii {gs[1]-n, gs[2]-n}], ' '), write(n+n+n, ' '), putchar('C'), putchar('\n');
				return 0;
			}
			gs[1]+=gss[1], gs[2]-=gss[1]+gss[3], gs[3]+=gss[3];
		}

		if(cccnt(gs[1]-gss[1], gs[2]-gss[2], gs[3]+gss[2]+gss[1]) == 2) {
			gs[1]-=gss[1], gs[2]-=gss[2], gs[3]+=gss[2]+gss[1];
			if(gs[1] < n && viss[2].find(pii {gs[2]-n, gs[3]-n}) != viss[2].end() && viss[2][pii {gs[2]-n, gs[3]-n}] > i) {
				puts("2");
				write(1, ' '), write(i, ' '), putchar('C'), putchar('\n');
				write(viss[2][pii {gs[2]-n, gs[3]-n}], ' '), write(n+n+n, ' '), putchar('A'), putchar('\n');
				return 0;
			}
			if(gs[2] < n && viss[1].find(pii {gs[1]-n, gs[3]-n}) != viss[1].end() && viss[1][pii {gs[1]-n, gs[3]-n}] > i) {
				puts("2");
				write(1, ' '), write(i, ' '), putchar('C'), putchar('\n');
				write(viss[1][pii {gs[1]-n, gs[3]-n}], ' '), write(n+n+n, ' '), putchar('B'), putchar('\n');
				return 0;
			}
			if(gs[3] < n && viss[0].find(pii {gs[1]-n, gs[2]-n}) != viss[0].end() && viss[0][pii {gs[1]-n, gs[2]-n}] > i) {
				puts("2");
				write(1, ' '), write(i, ' '), putchar('C'), putchar('\n');
				write(viss[0][pii {gs[1]-n, gs[2]-n}], ' '), write(n+n+n, ' '), putchar('C'), putchar('\n');
				return 0;
			}
			gs[1]+=gss[1], gs[2]+=gss[2], gs[3]-=gss[2]+gss[1];
		}
	}
	puts("3");
	write(1, ' '), write(n, ' '), putchar('A'), putchar('\n');
	write(n+1, ' '), write(n+n, ' '), putchar('B'), putchar('\n');
	write(n+n+1, ' '), write(n+n+n, ' '), putchar('C'), putchar('\n');
	debug("si le miao.");
	return 0;
	for(int i = 1; i <= n+n+n; ++i) {
		++gss[s[i]-'A'+1];
		if(cccnt(gs[1]+gss[2]+gss[3], gs[2]-gss[2], gs[3]-gss[3]) == 2) {
			for(int j = 1; j <= i; ++j)
				t[j]='A', swap(t[j], s[j]);
			gs[1]=gs[1]+gss[2]+gss[3], gs[2]-=gss[2], gs[3]-=gss[3];
			if(sol()) {
				puts("2");
				write(1, ' '), write(i, ' ');
				putchar('A'), putchar('\n');
				write(xxx[1], ' '), write(yyy[1], ' '), putchar(ttt[1]), putchar('\n');
				return 0;
			}
			for(int j = 1; j <= i; ++j)
				swap(t[j], s[j]);
			gs[1]-=gss[2]+gss[3], gs[2]+=gss[2], gs[3]+=gss[3];
		}
		if(cccnt(gs[1]-gss[1], gs[2]+gss[1]+gss[3], gs[3]-gss[3]) == 2) {
			for(int j = 1; j <= i; ++j)
				t[j]='B', swap(t[j], s[j]);
			gs[1]-=gss[1], gs[2]=gs[2]+gss[1]+gss[3], gs[3]-=gss[3];
			if(sol()) {
				puts("2");
				write(1, ' '), write(i, ' ');
				putchar('B'), putchar('\n');
				write(xxx[1], ' '), write(yyy[1], ' '), putchar(ttt[1]), putchar('\n');
				return 0;
			}
			for(int j = 1; j <= i; ++j)
				swap(t[j], s[j]);
			gs[1]+=gss[1], gs[2]-=gss[1]+gss[3], gs[3]+=gss[3];
		}
		if(cccnt(gs[1]-gss[1], gs[2]-gss[2], gs[3]+gss[2]+gss[1]) == 2) {
			for(int j = 1; j <= i; ++j)
				t[j]='C', swap(t[j], s[j]);
			gs[1]-=gss[1], gs[2]-=gss[2], gs[3]=gs[3]+gss[2]+gss[1];
			if(sol()) {
				puts("2");
				write(1, ' '), write(i, ' ');
				putchar('C'), putchar('\n');
				write(xxx[1], ' '), write(yyy[1], ' '), putchar(ttt[1]), putchar('\n');
				return 0;
			}
			for(int j = 1; j <= i; ++j)
				swap(t[j], s[j]);
			gs[1]+=gss[1], gs[2]+=gss[2], gs[3]-=gss[2]+gss[1];
		}
	}
	puts("3");
	write(1, ' '), write(n, ' '), putchar('A'), putchar('\n');
	write(n+1, ' '), write(n+n, ' '), putchar('B'), putchar('\n');
	write(n+n+1, ' '), write(n+n+n, ' '), putchar('C'), putchar('\n');
	return 0;
}