#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#ifdef DEBUG
template<class T>
ostream& operator << (ostream &out,vector<T> a){
	out<<'[';
	for(T x:a)out<<x<<',';
	return out<<']';
}
template<class T>
vector<T> ary(T *a,int l,int r){
	return vector<T>{a+l,a+1+r};
}
template<class T>
void debug(T x){
	cerr<<x<<endl;
}
template<class T,class...S>
void debug(T x,S...y){
	cerr<<x<<' ',debug(y...);
}
const int N=1e3+10,V=1e3+1;
#else
#define debug(...) void()
const int N=1e3+10,V=1e3+1;
#endif
int n,w[10],t[N],a[N][N];
char str[N];
void read(int i){
	scanf("%s",str);
	t[i]=strlen(str);
	assert(t[i]<=1000);
	for(int j=0;j<t[i];j++){
		if(str[j]=='?')a[i][t[i]-j]=-1;
		else a[i][t[i]-j]=str[j]-'0';
	}
}
int cur[N],old[N],cnt[10],f[N][N];
int pre[N],suf[N],Pre[N],Suf[N];
void chkmax(int &x,int y){
	if(x<y)x=y;
}
int main(){
	freopen("digits.in","r",stdin);
	freopen("digits.out","w",stdout);
	read(0);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)read(i);
	for(int i=0;i<10;i++)scanf("%d",&w[i]);
	memset(f,-0x3f,sizeof f);
	f[0][n]=0;
	iota(cur,cur+1+n,0);
	for(int i=1;i<=V;i++){
		int st=0,ed=9;
		if(~a[0][i])st=ed=a[0][i];
		if(i==t[0])st=max(st,1);
		for(int d=st;d<=ed;d++){
			for(int j=1;j<=n;j++){
				pre[j]=pre[j-1]+(a[cur[j]][i]+d<=9);
				Pre[j]=Pre[j-1]+(i<=t[cur[j]]||i<=t[0]?w[(a[cur[j]][i]+d)%10]:0);
			}
			for(int j=n;j>=1;j--){
				suf[j]=suf[j+1]+(a[cur[j]][i]+d+1<=9);
				Suf[j]=Suf[j+1]+w[(a[cur[j]][i]+d+1)%10];
			}
			for(int j=0;j<=n;j++){
				chkmax(f[i][pre[j]+suf[j+1]],f[i-1][j]+Pre[j]+Suf[j+1]);
			}
			// if(i==4&&d==1)debug(ary(Pre,1,n),ary(Suf,1,n));
		}
		// debug(i,st,ed);
		// debug(ary(f[i],0,n));
		for(int j=1;j<=n;j++)cnt[a[j][i]]++;
		for(int j=1;j<=9;j++)cnt[j]+=cnt[j-1];
		copy(cur,cur+1+n,old);
		for(int j=n;j>=1;j--)cur[cnt[a[old[j]][i]]--]=old[j];
		fill(cnt,cnt+10,0);
		// debug(i,ary(cur,1,n));
	}
	cout<<*max_element(f[V],f[V]+1+n)<<endl;
	return 0;
}
