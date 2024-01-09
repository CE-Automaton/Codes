#include <bits/stdc++.h>
using namespace std;
const int Mt=1e5, N=8e6+10;
int n, p[N], vis[N], pd[N], to[N], wh[N];
long long sum;
inline char getc(){
	static char buf[Mt],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,Mt,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	int r=0,f=1;char c=getc();
	while(!isdigit(c)){if(c=='-')f=-1;c=getc();}
	while(isdigit(c))r=(r<<1)+(r<<3)+(c^48),c=getc();
	return r*f;
}
int len;
char put[78];
inline void write(int x) {
	do {put[++len]=x%10, x/=10;}while(x);
	while(len) putchar(put[len--]^48); putchar(' ');
}
void dfs(int x) {
	vis[(p[x]-1)%(n/2)+1]=1;
	pd[x]=1;
	int y = (to[p[x]]+n/2-1)%n+1;
//	cout<<x<<" "<<p[x]<<" "<<y<<"!\n";
	if(pd[wh[y]] || vis[(y-1)%(n/2)+1]) return ;
	dfs(wh[y]);
}
int main() {
//	freopen("choose.in", "r", stdin);
//	freopen("choose.out", "w", stdout);
	n=read(), n*=2;
	for(int i = 1; i <= n; ++i) {
		p[i]=read();
		wh[p[i]]=i;
		if(i%2 == 0)
			to[p[i]]=p[i-1], 
			to[p[i-1]]=p[i];
	}
	for(int i = 1; i <= n/2; ++i) {
		if(vis[i]) continue;
//		cout<<i<<"???\n";
		dfs(wh[i]);
	}
	for(int i = 1; i <= n; ++i)
		if(pd[i]) sum+=p[i];
	if(sum%n == 0) {
		for(int i = 1; i <= n; ++i)
			if(pd[i]) write(p[i]);
	}
	else {
		for(int i = 1; i <= n; ++i)
			if(!pd[i]) write(p[i]);
	}
	return 0;
}
