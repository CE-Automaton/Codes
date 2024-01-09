#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define maxn 25
#define put() putchar('\n')
#define Tp template<typename T>
#define Ts template<typename T,typename... Ar>
using namespace std;
Tp void read(T &x){
    int f=1;x=0;char c=getchar();
    while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar();}
    while (c>='0'&&c<='9') {x=x*10+c-'0';c=getchar();}
    x*=f;
}
namespace Debug{
	Tp void _debug(char* f,T t){cerr<<f<<'='<<t<<endl;}
	Ts void _debug(char* f,T x,Ar... y){while(*f!=',') cerr<<*f++;cerr<<'='<<x<<",";_debug(f+1,y...);}
	#define gdb(...) _debug((char*)#__VA_ARGS__,__VA_ARGS__)
}using namespace Debug;
#define fi first
#define se second
#define mk make_pair
const int mod=1e9+7;
int power(int x,int y=mod-2) {
	int sum=1;
	while (y) {
		if (y&1) sum=sum*x%mod;
		x=x*x%mod;y>>=1;
	}
	return sum;
}
const int inf=2147483647;
int n,m,q;
int a[maxn][maxn];
ll f[(1<<21)+5];
int dis[22][(1<<21)+5];
#define lowbit(x) ((x)&(-(x)))
signed main(void){
	// freopen("1.in","r",stdin);
	freopen("acquire.in","r",stdin);freopen("acquire.out","w",stdout);
	int i,x,y,z,j,k,s;
	read(n);read(m);
	for (i=1;i<=n;i++) for (j=1;j<=n;j++) a[i][j]=inf;
	for (i=1;i<=m;i++) {
		read(x);read(y);read(z);
		a[x][y]=a[y][x]=z;
	}
	memset(f,0x3f,sizeof(f));
	for (i=0;i<n;i++) f[1<<i]=0;
	int N=(1<<n);
	for (i=0;i<n;i++) {
		dis[i][0]=inf;
		for (j=0;j<n;j++) dis[i][(1<<j)]=a[i+1][j+1];
		for (s=0;s<N;s++) if ((s>>i)%2==0) {
			dis[i][s]=min(dis[i][s^lowbit(s)],dis[i][lowbit(s)]);
			// gdb(i,s,dis[i][s]);
		}
	}
	for (i=1;i<(1<<n);i++) {
		for (j=0;j<n;j++) if ((i>>j)%2==0) {
			f[i^(1<<j)]=min(f[i^(1<<j)],f[i]+dis[j][i]);
		}
	}
	read(q);
	for (j=0;j<n;j++)
		for (i=0;i<(1<<n);i++) if ((i>>j)&1) {
			f[i^(1<<j)]=min(f[i^(1<<j)],f[i]);
		}
	while (q--) {
		read(k);int s=0;
		while (k--) read(x),s|=(1<<x-1);
		// gdb(s);
		printf("%lld\n",f[s]);
	}
	return 0;
}
//i=begin && g++ $i.cpp -o $i -std=c++14 && ./$i
