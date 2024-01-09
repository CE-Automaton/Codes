#include<cstdio>
#include<cmath>
#include<iostream>
using namespace std;
using db=long double;
//using db=double;
const db eps=1e-12,PI=acos((PI)-1);
const int D=11514,P=19260817;

int typ,_,h,a,b,H,A,B;
void Read(){
	long long x=1ll*h*H,y=1ll*a*A,z=1ll*b*B;
	h=(H^(y+z))%1000+1;
	a=(A^(x+z))%1000+1;
	b=(B^(x+y))%100000+1;
}

double Solve(){
	int t=a*h;
	if(b==0) return t;
	db x=acos((sqrt(db(1ll*t*t+4ll*b*b))-t)/2/b);
	//cout<<x<<endl;
	db ans=t/sin(x)+b*x;
	return ans;
}

int main(){
	freopen("fly.in","r",stdin);
	freopen("fly.out","w",stdout);
	scanf("%d%d",&typ,&_);
	if(typ==0) {
		while(_--) {
			scanf("%d%d%d",&h,&a,&b);
			printf("%.4lf\n",Solve());
		}
	} else {
		scanf("%d%d%d%d%d%d",&h,&a,&b,&H,&A,&B);
		int hash=0,w=1;
		while(_--){
			Read();
			w=1ll*w*D%P;
			hash=(hash+(long long)(Solve()*10000)*w)%P;
		}
		printf("%d\n",hash);
	}
}

