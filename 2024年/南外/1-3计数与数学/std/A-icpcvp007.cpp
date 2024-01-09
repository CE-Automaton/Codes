#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#include<ctime>
#include<random>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=4e5+10;
const double PI=acos(-1);
int n,m,Q,k,lim,r[N];
int a[N],b[N];
int V1[N],V2[N],E1[N],E2[N],F1[N],F2[N];
struct comp{
    double x,y;
    comp(double xx=0,double yy=0){x=xx,y=yy;}
}f[N],g[N],h[N],e[N],d[N],q[N],A1[N],A2[N],A3[N],A4[N],A5[N],A6[N],A7[N];
comp operator + (comp a,comp b){ return comp(a.x+b.x,a.y+b.y);}
comp operator - (comp a,comp b){ return comp(a.x-b.x,a.y-b.y);}
comp operator * (comp a,comp b){ return comp(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);}
void init(int x){
	int l=0;
	for(lim=1;lim<=x;lim<<=1)
		l++;
	for(int i=0;i<lim;i++)
		r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
}
void FFT(comp *a,int type){
	for(int i=0;i<lim;i++)
		if(i<r[i])
			swap(a[i],a[r[i]]);
	for(int i=1;i<lim;i<<=1){
		comp x(cos(PI/i),type*sin(PI/i));
		for(int j=0;j<lim;j+=(i<<1)){
			comp y(1,0);
			for(int k=0;k<i;k++,y=y*x){
				comp p=a[j+k],q=y*a[j+k+i];
				a[j+k]=p+q;
				a[j+k+i]=p-q;
			}
		}
	}
    if(type==-1){
        for(int i=0;i<=lim;i++)
	    	a[i].x/=lim;
    }
}
void mul(comp *a,comp *b,comp *c){
	for(int i=0;i<lim;i++)
		a[i]=b[i]*c[i];
	FFT(a,-1);
}
signed main()
{
	n=read(),m=read(),Q=read();
	int k=1e5; 
	for(int i=1;i<=n;i++){
		a[i]=read();
		f[a[i]].x++;
		k=max(k,a[i]); 
	}
	for(int i=1;i<=m;i++){
		b[i]=read();
		g[b[i]].x++;
		k=max(k,b[i]);
	}
	for(int i=2;i<=n;i++){
		h[min(a[i],a[i-1])].x++;
		e[max(a[i],a[i-1])].x++;
	}
	for(int i=2;i<=m;i++){
		d[min(b[i],b[i-1])].x++;
		q[max(b[i],b[i-1])].x++;
	}
	init(k*2+3);
	FFT(f,1);
	FFT(g,1);
	FFT(h,1);
	FFT(e,1),
	FFT(d,1);
	FFT(q,1);
	mul(A1,f,g);
	mul(A2,f,d);
	mul(A3,g,h);
	mul(A4,f,q);
	mul(A5,g,e);
	mul(A6,h,d);
	mul(A7,e,q);
	for(int i=0;i<=lim;i++){
		V1[i]=(int)(A1[i].x+0.5);
		V2[i]=(int)(A1[i].x+0.5);
		E1[i]=(int)(A2[i].x+0.5)+(int)(A3[i].x+0.5),
		E2[i]=(int)(A4[i].x+0.5)+(int)(A5[i].x+0.5);
		F1[i]=(int)(A6[i].x+0.5);
		F2[i]=(int)(A7[i].x+0.5); 
	} 
	for(int i=lim;i>=1;i--){
		V1[i-1]+=V1[i];
		E1[i-1]+=E1[i];
		F1[i-1]+=F1[i]; 
	}
	for(int i=1;i<=lim;i++){
		V2[i]+=V2[i-1];
		E2[i]+=E2[i-1];
		F2[i]+=F2[i-1];
	}
	while(Q--){
		int x=read(); 
		int ans=V1[x]-V2[x-1]+F1[x]-F2[x-1]-E1[x]+E2[x-1];  
		cout<<ans<<'\n'; 
	}
	return 0;
}
