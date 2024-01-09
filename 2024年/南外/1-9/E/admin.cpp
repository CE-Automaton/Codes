#include <bits/stdc++.h>
using namespace std;
const int MAXN=7010,P=998244353;
int n,eg,ans,cur0,cur1,inv2,a[MAXN],mk[MAXN],vis[MAXN],hd[MAXN],nx[MAXN],ver[MAXN];
char c[MAXN];
void add_edge (int x,int y) {
	ver[++eg]=y;
	nx[eg]=hd[x];
	hd[x]=eg;
	return;
}
void dfs (int x) {
	vis[x]=1;
	if (mk[x]==0||a[x]==0) {cur0=1;}
	if (mk[x]==1||a[x]==1) {cur1=1;}
	for (int i=hd[x];i;i=nx[i]) {
		if (!vis[ver[i]]) {dfs(ver[i]);}
	}
	return;
}
int calc1 (int x,int ch) {
	int res=0;
	for (int i=0;i<(1<<(x-1));i++) {
		for (int j=1;j<=n;j++) {mk[j]=-1,hd[j]=vis[j]=0;}
		eg=0;
		int tmp=1;
		for (int j=1;j<=x-1;j++) {
			if (i&(1<<(j-1))) {
				for (int k=x;k<=n;k++) {add_edge(j+(k-x),k),add_edge(k,j+(k-x));}
				mk[j+(n+1-x)]=ch,tmp=P-tmp;
			}
		}
		for (int j=1;j<=n;j++) {
			if (vis[j]) {continue;}
			cur0=cur1=0;
			dfs(j);
			if (!cur0&&!cur1) {tmp=(2ll*tmp)%P;}
			if (cur0&&cur1) {tmp=0;}
		}
		res=(res+tmp)%P;
	}
	return res;
}
int tmpres,b[MAXN],sum[MAXN],dp[MAXN],nxt[MAXN],bd[MAXN],flg[MAXN];
void chk (int x) {
	int len=n-x+2;
	for (int i=1;i<=n+1;i++) {dp[i]=bd[i]=0,flg[i]=1;}
	nxt[1]=0;
	for (int i=2,j=0;i<=len;i++) {
		while (j&&b[x+j]!=b[x+i-1]) {j=nxt[j];}
		if (b[x+j]==b[x+i-1]) {j++;}
		nxt[i]=j;
	}
	int cur=len;
	while (cur) {
		bd[cur]=1;
		cur=nxt[cur];
	}
	for (int i=1;i<=x;i++) {
		for (int j=1;j<=len;j++) {
			if (a[i+j-1]!=-1&&a[i+j-1]!=b[x+j-1]) {flg[i]=0;}
		}
	}
	for (int i=1;i<=x;i++) {
		if (!flg[i]) {continue;}
		dp[i]=-(1ll<<sum[i-1])%P;
		dp[i]=(dp[i]+P)%P;
		for (int j=1;j<i;j++) {
			if (j+len<=i) {
				int tmp=(1ll<<(sum[i-1]-sum[j+len-1]))%P;
				dp[i]=(dp[i]-(1ll*dp[j]*tmp)%P+P)%P;
			} else {
				if (bd[j+len-i]) {dp[i]=(dp[i]-dp[j]+P)%P;}
			}
		}
	}
	tmpres=(tmpres-dp[x]+P)%P;
	return;
}
void dfs2 (int x,int bg) {
	if (x==n+2) {chk(bg);return;}
	if (a[x]!=-1) {b[x]=a[x];dfs2(x+1,bg);}
	else {
		b[x]=0;dfs2(x+1,bg);
		b[x]=1;dfs2(x+1,bg);
	}
	return;
}
int calc2 (int x,int ch) {
	a[n+1]=ch;
	tmpres=0;
	dfs2(x,x);
	return tmpres;
}
int main () {
	freopen("rewopniarb.in","r",stdin);
	freopen("rewopniarb.out","w",stdout);
	inv2=(P+1)/2;
	scanf("%d%s",&n,c+1);
	int flg0=0,flg1=0;
	for (int i=1;i<=n;i++) {
		a[i]=(c[i]=='?'?-1:c[i]-'0');
		if (c[i]=='0') {flg0=1;}
		if (c[i]=='1') {flg1=1;}
	}
	ans=2-flg0-flg1;
	for (int i=1;i<=n/2;i++) {swap(a[i],a[n-i+1]);}
	for (int i=1;i<=n;i++) {sum[i]=sum[i-1]+(a[i]==-1);}
	for (int i=n;i>=1;i--) {
		if (i>n/2) {
			ans=(0ll+ans+calc2(i,0)+calc2(i,1))%P;
		} else {
			ans=(0ll+ans+calc1(i,0)+calc1(i,1))%P;
		}
	}
	for (int i=1;i<=n;i++) {
		if (a[i]==-1) {ans=(1ll*ans*inv2)%P;}
	}
	ans=(ans+P-1)%P;
	printf("%d\n",ans);
	return 0;
}
