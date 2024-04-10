#include<bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define repn(x) rep(x,1,n)
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
using namespace std;
const int N=3e5+5;
int n,t[N<<1],a[N];
void add_(int x,int k){
	x++;
	while(x<=(n<<1))t[x]=max(t[x],k),x+=x&-x;
}
int query(int x){
	x++;
	int ans=0;
	while(x)ans=max(ans,t[x]),x-=x&-x;
	return ans; 
}
int main(){
	freopen("seq.in","r",stdin);
	freopen("seq.out","w",stdout);
	n=read();
	repn(i)a[i]=read();
	repn(i){
		int w=a[i]-i;
		if(w<0)continue;
		int k=query(w);
		add_(w,k+1);
		if(i==n){
			cout <<n-(k+1);
			return 0;
		}
	}
	return 0;
}
