#include<cstdio>
int n,p,C[505][505],f[505][1010][2];
int min(int a,int b){return a<b?a:b;}
int dfs(int n,int x,int t){
	if(!t){
		if((x<0?x=-x:x)>n)return 0;
		if(!n)return!x;
	}
	int&g=f[n][x+t*::n][t];
	if(g)return g-1;
	if(!t)
		for(int y=1,ym=min(n,min((x+n*2)/3,n*2-x));y<=ym;y++)
			g=(g+1ll*C[n][y]*dfs(n-y,x-y,1))%p;
	for(int y=x<=0?x&1:x,ym=min(n,min((n*2-x)/3,x+n*2));y<=ym;y+=2)
		if(t||y)g=(g+1ll*C[n][y]*dfs(n-y,x+y>>1,0))%p;
	return g++;
}
int main(){
	freopen("rabbit.in","r",stdin);
	freopen("rabbit.out","w",stdout); 
	scanf("%d%d",&n,&p);
	for(int i=0;i<=n;i++)
		for(int j=*C[i]=1;j<=i;j++)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%p;
	int ans=1ll*(dfs(n-1,0,0)+dfs(n-1,1,0))*n%p;
	printf("%d\n",ans);
}
