#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
int n, a[500005], b[500005], ans, now, c[2][20000006], ww[1000006], st[500005], ha, az[10005], qwq, gs, mx[500005];
char m[10005];
void read(int& x) {
	x=0; char c = getchar(); while(c < '0' || c > '9') c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
}
int main() {
	freopen("relic.in", "r", stdin);
	freopen("relic.out", "w", stdout);
	read(n);
	a[0]=1;
	for(int i = 1; i < n; ++i) read(a[i]);
	for(int i = 1; i <= n; ++i) {
		read(b[i]);
		mx[i]=mx[i-1]/a[i-1]+b[i];
	}
	scanf("%s", m+1);
	ha=strlen(m+1);
	for(int i = 1; i < n; ++i) {
		int haha = 0, pd = 0;
		for(int j = 1; j <= ha; ++j) {
			haha=haha*10+m[j]-'0';
			if(haha >= a[i]) {
				az[++pd]=haha/a[i];
				haha%=a[i];
			}
			else if(pd) az[++pd]=0;
		}
		ha=pd;
		for(int i = 1; i <= ha; ++i)
			m[i]=az[i]+'0', az[i]=0;
		st[i]=haha;
		if(!pd) {
			qwq=i;
			break;
		}
		if(i == n-1 && pd) {
			for(int j = 1; j <= ha; ++j) {
				st[n]=st[n]*10+m[j]-'0';
				if(st[n] > b[n]) {
					puts("0");
					return 0;
				}
			}
			qwq=n;
		}
	}
	if(st[qwq] > mx[qwq]) {
		puts("0");
		return 0;
	}
	c[now^1][st[qwq]]=1;
	for(int j = mx[qwq]; j >= 0; --j) c[now^1][j]+=c[now^1][j+1];
	for(int i = qwq-1; i >= 1; --i, now^=1) {
		int www = mx[i];
		for(int j = 0; j <= www+1; ++j) c[now][j]=0;
		for(int j = st[i], o = 0; j <= www; j+=a[i], ++o)
			c[now][j]=(c[now^1][o]-c[now^1][b[i+1]+o+1]+mod)%mod;
		if(i != 1) for(int j = www; j >= 0; --j) (c[now][j]+=c[now][j+1])%=mod;
	}
	for(int i = 0; i <= b[1]; ++i)
		(ans+=c[now^1][i])%=mod;
	printf("%d\n", ans);
	return 0;
} 
