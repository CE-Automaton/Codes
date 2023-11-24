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
	freopen("max.in", "r", stdin);
	freopen("max.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	scanf("%s", s+1);
	int ln = strlen(s+1);
	for(int i = 1; i <= ln; ++i) {
		if(s[i] == '+')
			pd[1]=1;
		if(s[i] == '*')
			pd[2]=1;
		if(s[i] == '-')
			pd[3]=1;
	}
	if(ln == 1) {
		for(int i = 1; i <= n-1; ++i)
			write(a[i]), putchar((pd[1] ? '+' : (pd[2] ? '*' : '-')));
		write(a[n]);
		putchar('\n');
	}
	else {
		if(pd[2] == 0 || pd[1] == 0) {
			for(int i = 1; i <= n-1; ++i) 
				write(a[i]), putchar((a[i+1] == 0 ? '-' : (pd[1] ? '+' : '*')));
			write(a[n]);
			putchar('\n');
		}
		else {
			for(int i = 1; i <= n; ) {
				if(a[i] == 0) {
					b[++tot]=0;
					++i;
					continue;
				}
				int j = i, now = a[i];
				while(j+1 <= n && a[j+1] != 1 && a[j+1] != 0)
					++j, now=min(1000000LL, 1LL*a[j]*now);
				b[++tot]=now;
				lnn[tot]=j-i+1;
				i=j+1;
				while(i <= n && a[i] == 1)
					++c[tot], ++i;
			}
			int sum = 0;
			for(int i = 1; i <= tot; ++i) {
				if(b[i] == 0) {
					putchar('0');
					++sum;
					if(sum != n)
						putchar('+');
				}
				else {
					int j = i;
					while(j+1 <= tot && b[j+1] != 0)
						++j;
					int now = b[i];
					for(int ll = i+1; ll <= j; ++ll) 
						now=min(1000001LL, 1LL*b[ll]*now);
					if(now >= 1000000) {
						ans[i]=1;
						for(int ll = i+1; ll <= j; ++ll)
							ans[ll]=0;
					}
					else {
						l=i;
						r=j;
						sss=0;
						ans[i]=tt[i]=1;
						dfs(i+1);
					}
					for(int o = i; o <= j; ++o) {
						for(int p = 1; p <= lnn[o]-1; ++p)
							write(a[p+sum]), putchar('*');
						int pd = (o == j || (o != j && ans[o+1] == 1));
						write(a[lnn[o]+sum]);
						sum+=lnn[o];
						if(c[o] != 0) {
							putchar((pd ? '+' : '*'));
							for(int p = 1; p <= c[o]-1; ++p)
								write(1), putchar((pd ? '+' : '*'));
							sum+=c[o];
							if(sum == n) {
								write(1);
								putchar('\n');
								break;
							}
							else 
								write(1), putchar((pd ? '+' : '*'));
						}
						else {
							if(sum == n)
								break;
							else
								putchar('+');
						}
					}
					i=j;
				}
			}
		}
	} 
	return 0;
}
