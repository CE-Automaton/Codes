#include<bits/stdc++.h>
using namespace std;
#define cs const
#define re register
#define pb push_back
#define pii pair<int,int>
#define ll long long
#define fi first
#define se second
#define bg begin
cs int RLEN=1<<20|1;
inline char gc(){
    static char ibuf[RLEN],*ib,*ob;
    (ib==ob)&&(ob=(ib=ibuf)+fread(ibuf,1,RLEN,stdin));
    return (ib==ob)?EOF:*ib++;
}
inline int read(){
    char ch=gc();
    int res=0;bool f=1;
    while(!isdigit(ch))f^=ch=='-',ch=gc();
    while(isdigit(ch))res=(res+(res<<2)<<1)+(ch^48),ch=gc();
    return f?res:-res;
}
inline ll readll(){
    char ch=gc();
    ll res=0;bool f=1;
    while(!isdigit(ch))f^=ch=='-',ch=gc();
    while(isdigit(ch))res=(res+(res<<2)<<1)+(ch^48),ch=gc();
    return f?res:-res;
}
inline int readstring(char *s){
	int top=0;char ch=gc();
	while(isspace(ch))ch=gc();
	while(!isspace(ch)&&ch!=EOF)s[++top]=ch,ch=gc();
	return top;
}
template<typename tp>inline void chemx(tp &a,tp b){a<b?a=b:0;}
template<typename tp>inline void chemn(tp &a,tp b){a>b?a=b:0;}
class ThePowers{
	private:
		int lim=31,l[35],r[35];
		inline ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
		inline bool check(int k,int pw,int l){
			ll mt=1;
			for(int i=1;i<=pw;i++){
				mt=mt*k;
				if(mt>l)return true;
			}return false;
		}
		int pr[100],tot;
		inline ll solve(ll up,int l,int r){
			tot=0;
			for(int i=l;i<=r;i++){
				int fg=1;
				for(int j=0;j<tot&&fg;j++)if(i%pr[j]==0)fg=0;
				if(fg)pr[tot++]=i;
			}
			int sta=(1<<tot);ll res=0;
			for(int s=1;s<sta;s++){
				int siz=0;ll lcm=1;
				for(int j=0;j<tot;j++)if(s&(1<<j)){
					siz++,lcm=lcm*pr[j]/gcd(lcm,pr[j]);
					if(lcm>up)break;
				}
				if(siz&1)res+=up/lcm;
				else res-=up/lcm;
			}
			return res;
		}
		inline ll calc(int l1,int l2){
			ll res=0;
			for(int i=1;i<=l1;i++){
				res+=solve(1ll*i*l2,i,l1)-solve(1ll*(i-1)*l2,i,l1);
			}return res;
		}
	public:
		inline ll find(int A,int B){
			for(int i=1;i<=lim;i++){
				r[i]=(i==1)?A:(l[i-1]-1);
				if(r[i]==1){lim=i-1;break;}
				int L=2,R=r[i],res=r[i]+1;
				while(L<=R){
					int mid=(L+R)>>1;
					if(check(mid,i+1,A))R=mid-1,res=mid;
					else L=mid+1;
				}
				l[i]=res;
			}
			for(int i=lim;i;i--){
				int now=r[i]-l[i]+1;
				for(int j=2;j<=i;j++)
				r[i/j]-=now;
			}
			ll res=0;
			for(int i=1;i<=lim;i++){
				int now=r[i]-l[i]+1;
				if(now)res+=calc(i,B)*now;
			}
			return res+1;
		}
};

