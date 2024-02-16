#include<bits/stdc++.h>
using namespace std;
#define Mo(a) (a>=mo?a-=mo:a)
#define reg register
bool st;
const int mo=1e9+7;
int n,m,k,tmp,ans,Pre[10][2];
int r,A[10],now,la,Ne[10],hash;
int DP[1003][1003][10];
map<int,int>M;
bool ed;
void ADD(int& a,int b) {
	a+=b,Mo(a);
}
int max(int a,int b) {
	return a>b?a:b;
}
int min(int a,int b) {
	return a<b?a:b;
}
void DO() {
	memset(DP,0,sizeof(DP));
	DP[0][0][1]=1;
//	for(int i=1; i<=k+1; ++i)printf("%d %d\n",Pre[i][0],Pre[i][1]);
//	puts("");
	reg int i,j,o;
	for(i=0; i!=n; ++i) {
		for(j=min(max(0,i-k+1),m); ~j; --j) {
			for(o=k+1; o; --o) {
				if(!DP[i][j][o])continue;
				tmp=Pre[o][0]+1,la=j+(tmp>k&&j<m);
				ADD(DP[i+1][la][tmp],DP[i][j][o]);
				tmp=Pre[o][1]+1,la=j+(tmp>k&&j<m);
				ADD(DP[i+1][la][tmp],DP[i][j][o]);
			}
		}
	}
	tmp=0;
	for(int i=1; i<=k+1; ++i)
		tmp+=DP[n][m][i],Mo(tmp);
}
int main() {
//	printf("%lf\n",(&ed-&st)/1024.0/1024.0);
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	scanf("%d %d %d",&n,&m,&k),n-=k;
	r=1<<k;
	for(int i=0; i!=r; ++i) {
		for(int j=1; j<=k; ++j)
			A[j]=(i&(1<<(j-1)))>0;
		now=1,la=0;
		while(now<=k) {
			if(la==0||A[now]==A[la])++now,++la,Ne[now]=la;
			else la=Ne[la];
		}
		hash=0,A[now]=-1;
		for(int j=1; j<=k+1; ++j) {
			hash=10*hash+(Ne[j]+1);
			if(A[j]==0)Pre[j][0]=j;
			else Pre[j][0]=Pre[Ne[j]][0];
			if(A[j]==1)Pre[j][1]=j;
			else Pre[j][1]=Pre[Ne[j]][1];
		}
		if(!M.count(hash))DO(),M[hash]=tmp;
		ans+=M[hash],Mo(ans);
	}
	printf("%d\n",ans);
//	printf("%d\n",(int)M.size());
	return 0;
}
