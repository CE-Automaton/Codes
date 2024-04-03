#include<bits/stdc++.h>
using namespace std;
int n,x,_n=0,h1[20010],h2[20010],a[20010];
int sol(){
	if(n<=2) return a[n];
	if(n<=4) return x+1;
	
	n-=4;
	int sum=0,b,_w=0;
	for(int i=1;i<=n;i++) a[i]=x+1-a[i+4],sum+=a[i];
	for(b=1;b<=n;b++){
		_w+=a[b];
		if(_w>sum/2){
			_w-=a[b];
			break;
		}
	}
	b--;
	int *f=h1+x,*g=h2+x;
	f[_w-sum/2]=b+1;
	for(int i=b+1;i<=n;i++){
		for(int j=-x+1;j<=x;j++) g[j]=f[j];
		for(int j=0;j>=-x+1;j--) g[j+a[i]]=max(g[j+a[i]],f[j]);
		for(int j=x;j>=1;j--) for(int k=g[j]-1;k>=max(1,f[j]);k--) g[j-a[k]]=max(g[j-a[k]],k);
		swap(f,g);
	}
	for(int j=0;j>=-x+1;j--) if(f[j]){
		return sum-sum/2-j+x+1;
	}
	assert(1);
}
int main(){
	scanf("%d%d",&n,&x);
	int tp=0;
	for(int i=1,w;i<=n;i++){
		scanf("%d",&w);
		if(w>x) tp=max(tp,w);
		else a[++_n]=w;
	}
	n=_n; sort(a+1,a+n+1);
	printf("%d\n",max(tp,sol()));
}


