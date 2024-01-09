#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
const int maxn=(1<<18)+10;
const int B=800;
const int lim=24e4;
const int mod=998244353;

inline int read(){
    int x=0,w=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
    while(c<='9'&&c>='0'){x=(x<<3)+(x<<1)+c-'0';c=getchar();}
    return x*w;
}

inline int q_pow(int A,int B,int P){
    int res=1;
    while(B){
        if(B&1) res=1ll*res*A%P;
        A=1ll*A*A%P;
        B>>=1;
    }
    return res;
}

int fact[maxn],inv_fact[maxn];
inline int C(int N,int M){
    if(M<0) return 0;
    if(N<M) return 0;
    return 1ll*fact[N]*inv_fact[M]%mod*inv_fact[N-M]%mod;
}

int rev[maxn];
int base,w[maxn];
struct Poly{
    const static int g=3;
    int deg;
    vector<ull> f;
    ull &operator[](const int &i){return f[i];}
    ull operator[](const int &i)const{return f[i];}
    inline void set(int L){deg=L;f.resize(L);}
    inline void clear(int L,int R){for(int i=L;i<=R;++i)f[i]=0;}
    inline void output(int L){for(int i=0;i<L;++i)printf("%llu ",f[i]);printf("\n");}
    inline void NTT(int L,bool type){
        set(L);
        for(int i=1;i<L;++i){
            rev[i]=(rev[i>>1]>>1)+(i&1?L>>1:0);
            if(i<rev[i]) swap(f[i],f[rev[i]]);
        }
        for(int d=1;d<L;d<<=1){
            base=q_pow(type?g:q_pow(g,mod-2,mod),(mod-1)/(2*d),mod);
            w[0]=1;
            for(int i=1;i<d;++i) w[i]=1ll*w[i-1]*base%mod;
            for(int i=0;i<L;i+=d<<1){
                for(int j=0;j<d;++j){
                    ull x=f[i+j],y=f[i+d+j]*w[j]%mod;
                    f[i+j]=x+y,f[i+d+j]=x-y+mod;
                }
            }
        }
        for(int i=0;i<L;++i) f[i]%=mod;
        if(!type){
            int inv_L=q_pow(L,mod-2,mod);
            for(int i=0;i<L;++i) f[i]=f[i]*inv_L%mod;
        }
    }
}F,G,H;

inline void calc(int t,int R,vector<int> &f,int coef){
    // cerr<<"calc t:"<<t<<" R:"<<R<<" coef:"<<coef<<endl;
    if(R<0) return;
    int S1=1,S2=0;
    for(int i=1;i<=t;++i){
        S1=(2ll*S1-C(i-1,(i-1+R)/2)+mod)%mod;
        S2=(2ll*S2-C(i-1,i/2-1)+mod)%mod;
        if(!((i+R)&1)) S1=(S1+C(i,(i+R)/2))%mod;
        if(i&1) S2=(S2+C(i,(i+1)/2-1))%mod;
        // cerr<<"i:"<<i<<" S1:"<<S1<<" S2:"<<S2<<endl;
        f[i]=(f[i]+1ll*coef*(S1-S2+mod)%mod+mod)%mod;
    }
}
int dp[2][maxn];
inline void solve(int t,int n,int a,vector<int> &f){
    f.push_back(1);
    if(n<=B){
        for(int i=1;i<=n;++i) dp[0][i]=dp[1][i]=0;
        dp[0][a]=1;
        for(int i=1;i<=t;++i){
            for(int j=1;j<=n;++j){
                if(j>1) dp[i&1][j-1]=(dp[i&1][j-1]+dp[i&1^1][j])%mod;
                if(j<n) dp[i&1][j+1]=(dp[i&1][j+1]+dp[i&1^1][j])%mod;
            }
            int sum=0;
            for(int j=1;j<=n;++j){
                sum=(sum+dp[i&1][j])%mod;
                dp[i&1^1][j]=0;
            }
            sum=1ll*sum*inv_fact[i]%mod;
            f.push_back(sum);
        }
    }
    else{
        for(int i=1;i<=t;++i) f.push_back(0);
        for(int i=-((t-1)/n+1)-1;i<=(t-1)/n+1;++i){
            int l=i*(n+1)+1,r=(i+1)*(n+1)-1,L,R;
            // cerr<<"i:"<<i<<" ["<<l<<","<<r<<"]"<<endl;
            if(!i){
                L=0,R=r-a;
                calc(t,R,f,1);
                L=1,R=a-l;
                calc(t,R,f,1);
                calc(t,L-1,f,-1);
            }
            else if(i>0){
                L=l-a,R=r-a;
                calc(t,R,f,(i&1)?-1:1);
                calc(t,L-1,f,(i&1)?1:-1);
            }
            else{
                L=a-r,R=a-l;
                calc(t,R,f,((-i)&1)?-1:1);
                calc(t,L-1,f,((-i)&1)?1:-1);
            }
        }
        for(int i=1;i<=t;++i) f[i]=1ll*f[i]*inv_fact[i]%mod;
    }
}

int t,n,m,k,a,b,c;
vector<int> f,g,h;
int ans;

int main(){
    freopen("homura.in","r",stdin);
    freopen("homura.out","w",stdout);
    fact[0]=1;
    for(int i=1;i<=lim;++i) fact[i]=1ll*fact[i-1]*i%mod;
    inv_fact[0]=1,inv_fact[lim]=q_pow(fact[lim],mod-2,mod);
    for(int i=lim-1;i>=1;--i) inv_fact[i]=1ll*inv_fact[i+1]*(i+1)%mod;
    t=read(),n=read(),m=read(),k=read(),a=read(),b=read(),c=read();
    solve(t,n,a,f);
    solve(t,m,b,g);
    solve(t,k,c,h);
    int L=1;
    while(L<2*t) L<<=1;
    F.set(L),G.set(L),H.set(L);
    for(int i=0;i<=t;++i) F[i]=f[i],G[i]=g[i];
    F.NTT(L,1),G.NTT(L,1);
    for(int i=0;i<L;++i) H[i]=1ll*F[i]*G[i]%mod;
    H.NTT(L,0);
    for(int i=0;i<=t;++i) ans=(ans+1ll*H[i]*h[t-i])%mod;
    ans=1ll*ans*fact[t]%mod;
    printf("%d\n",ans);
    return 0;
}
