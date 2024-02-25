namespace Sub2{
    int tmp[210][210];
    void DFS(int x,int fa){
        size[x]=1;
        dp[x][1]=1;
        for(int i=head[x];i;i=G[i].last){
            int t=G[i].ed;
            if(t==fa)continue;
            DFS(t,x);
            for(int j=size[x];j>=1;j--){
                for(int k=size[t];k>=1;k--){
                    dp[x][j+k]=(dp[x][j+k]+dp[x][j]*dp[t][k]%MOD)%MOD;
                }
            }
            size[x]+=size[t];
        }
    }
    int work(){
        DFS(Rt1,0);
        memset(tmp,0,sizeof(tmp));
        int sz=1;
        tmp[1][0]=1;
        for(int i=head[Rt1];i;i=G[i].last){
            int t=G[i].ed;
            for(int j=sz;j>=0;j--){
                for(int k=sz;k>=0;k--){
                    if(tmp[j][k]==0)continue;
                    for(int o=size[t];o>=1;o--){
                        tmp[j+o][max(k,o)]=(tmp[j+o][max(k,o)]+tmp[j][k]*dp[t][o]%MOD)%MOD;
                    }
                }
            }
            sz+=size[t];
        }
        for(int i=1;i<=n;i++){
            for(int j=0;2*j<i;j++){
                ans=(ans+tmp[i][j])%MOD;
            }
        }
        return ans;
    }
}
