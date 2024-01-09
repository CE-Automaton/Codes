#include <iostream>
#include <cstdio>
#include <cstring>
#define mod 1000000007
using namespace std;
int n;
char s[405];
int C[405][405];
int f[405][405];
int dfs(int l,int r){
	if (l>r)return 1;
	if (f[l][r]!=-1)return f[l][r];
	int ans=0;
	for (int i=l;i<=r;i++)
		if (r==n||s[i]!=s[r+1])
			ans=(ans+1ll*C[r-l][i-l]*dfs(l,i-1)%mod*dfs(i+1,r))%mod;
	return f[l][r]=ans;
}
int main(){
	freopen("sub.in","r",stdin);
	freopen("sub.out","w",stdout);
	cin>>n;
	for (int i=0;i<=n;i++)C[i][0]=1;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=i;j++)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	scanf("%s",s+1);
	memset(f,-1,sizeof(f));
	cout<<dfs(1,n)<<endl;
	return 0;
}