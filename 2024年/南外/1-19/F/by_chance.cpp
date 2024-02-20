#include<bits/stdc++.h>
using namespace std;
const int N=3005;
int n,m,P,f[N],f1[N],g[N],h[N],tot,cnt,ans;
int A,B,C,D;
int main(){
    freopen("chicken.in","r",stdin);
    freopen("chicken.out","w",stdout);
    cin>>n>>m>>P;f[0]=cnt=1;
    for(int i=1;i<=n;i++)f[i]=(f[i-1]+1ll*f[max(i-2,0)]*m)%P;
    for(int i=2;i<n;i++)tot=(tot+1ll*f[i-2]*f[n-i-1])%P;
    tot=(tot+2ll*f[n-2])%P;ans=1ll*m*(m-1)/2*tot%P;
    for(int i=0;i<=n;i++)f1[i]=f[max(i-1,0)];
    for(int i=0;i<=n;i++)
        for(int j=0;j<=n-i;j++)
            g[i+j]=(g[i+j]+1ll*f1[i]*f1[j])%P,
            h[i+j]=(h[i+j]+1ll*f[i]*f[j])%P;
	for(int j=1;j<=n;j+=2){
		if(j==n)++D;
		if(j+2<=n){
			int t=f1[n-j-2];
			D=(D+2ll*m*t)%P,C=(C-2ll*t%P+P)%P;
		}
		if(j+4<=n){
			int t=g[n-j-4];
			D=(D+1ll*t*m%P*m)%P;
			C=(C-2ll*m*t%P+P)%P;B=(B+t)%P;
		}
	}
	A=B;B=(C+P-1ll*m*B%P)%P;C=(D+P-1ll*m*C%P)%P;D=(P-1ll*m*D%P)%P;
    for(int i=1;i<m;i++)
		ans=(ans+1ll*A*i%P*i%P*i%P+1ll*B*i%P*i%P+1ll*C*i%P+D)%P;
    for(int i=4;i<=n;i++)cnt=(cnt+1ll*(P+(i&1?-1:1))*h[n-i])%P;
    for(int i=3;i<n;i+=2)cnt=(cnt+2ll*f1[n-i-1]*m)%P;
    ans=(ans+f[n]+1ll*cnt*m)%P;
    cout<<ans<<endl;
    return 0;
}
