#include <bits/stdc++.h>
using namespace std;
bool st;
int tt, tot, b[10];
__int128 l, r, az[88];
char s[25], t[25];
struct qwq {
	long long w;
	int a[10], gs;
}zhan[4800005];

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
void dfs(int x, int lst) {
	if(2 <= x && x <= 19) {
		++tot;
		long long now = 0;
		for(int i = 1; i <= 9; ++i)
			for(int j = 1; j <= b[i]; ++j)
				now=now*10LL+1LL*i;
		zhan[tot].w=now;
//		write(zhan[tot].w, '\n');
		for(int i = 1; i <= 9; ++i)
			zhan[tot].a[i]=b[i]; 
		zhan[tot].gs=x-1;
	}
	if(x == 19) return ;
	for(int i = lst; i <= 9; ++i) {
		++b[i];
		dfs(x+1, i);
		--b[i];
	}
}
bool fn;

signed main() {
	freopen("statement.in", "r", stdin);
	freopen("statement.out", "w", stdout);
//	cout<<(&st-&fn)*1.0/1024/1024<<"\n";
	dfs(1, 1);
//	write(tot, '\n');
	read(tt);
	while(tt--) {
		scanf("%s %s", s+1, t+1);
		int len = strlen(s+1), len2 = strlen(t+1), ans = 0;
		l=r=0;
		for(int i = 1; i <= len; ++i)
			l=(__int128) l*10+s[i]-'0';
		for(int i = 1; i <= len2; ++i)
			r=(__int128) r*10+t[i]-'0';
		for(int i = 1; i <= tot; ++i) 
			if(zhan[i].w <= r) {
//				write(zhan[i].w, '\n');
				b[0]=0;
				for(int j = 1; j <= 9; ++j)
					b[j]=zhan[i].a[j];
				if(zhan[i].gs > len || l <= zhan[i].w) 
					++ans;
				else {
					b[0]=len-zhan[i].gs;
					__int128 now = 0;
					for(int i = 9; i >= 0; --i)
						for(int j = 1; j <= b[i]; ++j)
							now=(__int128) now*10+i;
					if(now < l) {
						if(zhan[i].gs+1 > len2) 
							continue;
						++b[0];
						now = 0;
						for(int k = 1; k <= 9; ++k)
							if(b[k] != 0) {
								--b[k];
								now=k;
								break;
							}
						for(int k = 0; k <= 9; ++k)
							for(int jj = 1; jj <= b[k]; ++jj)
								now=(__int128) now*10+k;
//						write(now, '!'), puts("");
						if(now <= r)
							++ans; 
					} 
					else {
						now = 0;
						int lst = 0;
						for(int o = 1; o <= len; ++o) {
							int j = s[o]-'0';
							for(; j <= 9; ++j)
								if(b[j] != 0)
									break;
							for(int k = j+1; k <= 9; ++k)
								if(b[k] != 0) {
									lst=o;
									break;
								}
							if(j == 10) {
								for(int p = o-1; p >= lst; --p)
									now=(__int128) (now-az[p])/10, ++b[az[p]];
								j = s[lst]-'0';
								for(; j <= 9; ++j)
									if(b[j] != 0)
										break;
								++j;
								for(; j <= 9; ++j)
									if(b[j] != 0)
										break;
								--b[j];
								now=(__int128) now+j;
								for(int k = 0; k <= 9; ++k)
									for(int jj = 1; jj <= b[k]; ++jj)
										now=(__int128) now*10+k;
								break;
							}
							now=(__int128) now*10+j;
							az[o]=j;
							--b[j];
							if(j != s[o]-'0') {
								for(int k = 0; k <= 9; ++k)
									for(int jj = 1; jj <= b[k]; ++jj)
										now=(__int128) now*10+k;
								break;
							}
						}
//						write(now, '?'), puts("");
						if(now <= r)
							++ans;
					}
				}
			}
		write(ans, '\n');
	}
	return 0;
}
