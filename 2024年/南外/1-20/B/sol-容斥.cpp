namespace Sub2 {
	int tmp[210][210];
	void DFS(int x,int fa) {
		size[x]=1;
		dp[x][1]=1;
		for(int i=head[x]; i; i=G[i].last) {
			int t=G[i].ed;
			if(t==fa)continue;
			DFS(t,x);
			for(int j=size[x]; j>=1; j--) {
				for(int k=size[t]; k>=1; k--) {
					dp[x][j+k]=(dp[x][j+k]+dp[x][j]*dp[t][k]%MOD)%MOD;
				}
			}
			size[x]+=size[t];
		}
	}
	int work() {
		memset(tmp,0,sizeof(tmp));
		DFS(Rt1,0);
		for(int i=head[Rt1]; i; i=G[i].last) {
			int t=G[i].ed;
			for(int j=1; j<=n; j++) {
				tmp[t][j]=dp[Rt1][j];
				for(int k=1; k<=min(j,size[t]); k++)tmp[t][j]=(tmp[t][j]-tmp[t][j-k]*dp[t][k]%MOD+MOD)%MOD;
			}

		}
		for(int i=1; i<=n; i++) {
			ans=(ans+dp[Rt1][i])%MOD;
			for(int j=head[Rt1]; j; j=G[j].last) {
				int t=G[j].ed;
				for(int k=(i+1)/2; k<=min(i,size[t]); k++)ans=(ans-dp[t][k]*tmp[t][i-k]%MOD+MOD)%MOD;
			}
		}
		return ans;
	}
}
