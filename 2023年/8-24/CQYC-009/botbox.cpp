#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+5;
int n, nxt[3], cnt, cc[3], l[N], r[N], tot;
long long k; 
char s[N], zhan[N];
struct qwq {
	int a[3], st;
}haha[N];
struct to {
	int i, col;
}now;

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
void merge(int x, int y) {
	return ;
}

signed main() {
	freopen("botbox.in", "r", stdin);
	freopen("botbox.out", "w", stdout);
	read(n), read(k);
	nxt[0]=2, nxt[1]=0, nxt[2]=1;
	scanf("%s", s+1);
	for(int i = 1; i <= n; ++i) {
		int j = i;
		while(j+1 <= n && s[i] == s[j+1])
			++j;
		haha[++cnt].a[s[i]-'A']=j-i+1;
		haha[cnt].st=s[i]-'A';
		i=j;
		while(j+1 <= n && nxt[s[i]-'A'] == s[j+1]-'A')
			++j;
		if(i == j) continue;
		haha[cnt].a[s[j]-'A']=j-i;
		i=j;
		while(j+1 <= n && nxt[s[i]-'A'] == s[j+1]-'A')
			++j;
		if(i == j) continue;
		haha[cnt].a[s[j]-'A']=j-i;
		i=j;
	}
//	for(int i = 1; i <= cnt; ++i)
//		cout<<i<<": "<<haha[i].st<<" "<<haha[i].a[0]<<" "<<haha[i].a[1]<<" "<<haha[i].a[2]<<"\n";
	for(int i = 1; i <= cnt; ++i)
		l[i]=i-1, r[i]=i+1;
	l[1]=cnt, r[cnt]=1;
	now = to{1, s[1]-'A'};
	while(1) {
//		write(k, '\n');
		long long ned = 0;
		cc[haha[now.i].st]=0;
		cc[nxt[haha[now.i].st]]=1;
		cc[nxt[nxt[haha[now.i].st]]]=2;
		if(cc[now.col] <= cc[nxt[now.col]] && haha[now.i].a[nxt[now.col]] != 0) {
			ned=haha[now.i].a[now.col];
			if(k >= ned) 
				k-=ned, now=to {now.i, nxt[now.col]};
			else {
				for(int o = 1; o <= ned-k; ++o)
					putchar('A'+now.col);
				for(int o = 1; o <= haha[now.i].a[nxt[now.col]]; ++o)
					putchar('A'+nxt[now.col]);
				if(cc[nxt[now.col]] <= cc[nxt[nxt[now.col]]])
					for(int o = 1; o <= haha[now.i].a[nxt[nxt[now.col]]]; ++o)
						putchar('A'+nxt[nxt[now.col]]);
				for(int u = r[now.i]; u != now.i; u=r[u]) {
					for(int o = haha[u].st, pd = 0; ; o=nxt[o]) {
						if(o == haha[u].st) {
							++pd;
							if(pd == 2)
								break;
						}
						for(int p = 1; p <= haha[u].a[o]; ++p)
							putchar('A'+o);
					}
				}
				if(cc[nxt[now.col]] > cc[nxt[nxt[now.col]]])
					for(int o = 1; o <= haha[now.i].a[nxt[nxt[now.col]]]; ++o)
						putchar('A'+nxt[nxt[now.col]]);
				for(int o = 1; o <= k; ++o)
					putchar('A'+now.col);
				return 0;
			}
		}
		else {
			for(int o = now.col; ; o=nxt[o]) {
				ned+=haha[now.i].a[o];
				if(cc[o] == 2) break;
			}
			int u = 0, pdd = 1;
			for(u = r[now.i]; ; u=r[u]) {
				for(int o = haha[u].st, pd = 0; ; o=nxt[o]) {
					if(o == haha[u].st) {
						++pd;
						if(pd == 2)
							break;
					}
					if(o == nxt[now.col] && haha[u].a[o] != 0) {
						pdd=0;
						break;
					}
					ned+=haha[u].a[o];
				}
				if(pdd == 0)
					break;
			}
			if(k >= ned) {
				--haha[now.i].a[now.col];
				if(haha[u].st == nxt[now.col] && haha[u].a[now.col] == 0)
					haha[u].st=now.col;
				++haha[u].a[now.col];
				merge(l[now.i], now.i);
				merge(l[u], u);
				merge(u, r[u]);
				k-=ned, now=to {u, nxt[now.col]};
			}
			else {
				tot=0;
				for(int o = now.col; ; o=nxt[o]) {
					for(int p = 1; p <= haha[now.i].a[o]; ++p)
						zhan[++tot]='A'+o;
					if(cc[o] == 2) break;
				}
				for(int q = r[now.i]; q != now.i; q=r[q]) {
					for(int o = haha[q].st, pd = 0; ; o=nxt[o]) {
						if(o == haha[q].st) {
							++pd;
							if(pd == 2)
								break;
						}
						for(int p = 1; p <= haha[q].a[o]; ++p)
							zhan[++tot]='A'+o;
					}
				}
				for(int o = haha[now.i].st; o != now.col; o=nxt[o]) 
					for(int p = 1; p <= haha[now.i].a[o]; ++p)
						zhan[++tot]='A'+o;
				putchar(now.col+'A');
				for(int o = k+2; o <= tot; ++o)
					putchar(zhan[o]);
				for(int o = 2; o <= k+1; ++o)
					putchar(zhan[o]);
				return 0;
			}
		}
//		for(int i = 1; i <= cnt; ++i)
//		cout<<i<<": "<<haha[i].st<<" "<<haha[i].a[0]<<" "<<haha[i].a[1]<<" "<<haha[i].a[2]<<"\n";
	}
	return 0;
}
