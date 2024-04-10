#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)? EOF:*p1++)
using namespace std;
typedef long long ll;
const int N=2e5+5;
char buf[1<<23],*p1=buf,*p2=buf;
ll n,ji[N],fa[N],c[N][2],ans, dep[N], mx, ds[N];
vector <int> to[N];
struct aa
{
	ll id,c0,c1;
	bool operator <(const aa &b)const{return c0*b.c1==c1*b.c0? c0==b.c0? c1==b.c1? id<b.id:c1<b.c1:c0<b.c0:c0*b.c1<c1*b.c0;}
	bool operator ==(const aa &b)const{return id==b.id&&c0==b.c0&&c1==b.c1;}
};
priority_queue<aa> q1,q2;
int read()
{
	int res=0,fl=0; char a=getchar();
	while(a<'0'||a>'9') fl|=a=='-',a=getchar();
	while(a>='0'&&a<='9') res=res*10+a-'0',a=getchar();
	return fl? -res:res;
}
int getf(int x) {return ji[x]==x? x:ji[x]=getf(ji[x]);}
void dfs(int x) {
	mx=max(mx, dep[x]);
	for(int y : to[x])
		dep[y]=dep[x]+1, dfs(y);
}
int main()
{
	int i,j,li;
	mx=1;
	for(n=read(),i=2;i<=n;i++) {
		fa[i]=read(), to[fa[i]].push_back(i), ++ds[fa[i]], ++ds[i];
		mx&=(fa[i] == i-1);
		if(fa[i] == i)
			cerr<<"si\n";
	}
	cerr<<mx<<"!\n";
	mx=0;
	dfs(1);
	cerr<<mx<<"!?\n";
	mx=0;
	for(i=1;i<=n;i++) c[i][read()]=1, mx+=c[i][1], i>1&&(q1.push(aa{i,c[i][0],c[i][1]}),1),ji[i]=i;
	cerr<<mx<<"!!!\n";
	mx=0;
	int gg = 0;
	for(i=1;i<=n;i++)
		mx=max(mx, ds[i]), gg+=(ds[i] <= 2 ? 1 : 0);
	cerr<<mx<<' '<<gg<<" "<<(gg == n-1)<<"???\n";
	for(i=1;i<n;i++)
	{
		while(!q2.empty()&&q1.top()==q2.top()) q1.pop(),q2.pop();
		int lx=q1.top().id,ly=getf(fa[lx]);
		q1.pop(),ly>1&&(q2.push(aa{ly,c[ly][0],c[ly][1]}),q1.push(aa{ly,c[ly][0]+c[lx][0],c[ly][1]+c[lx][1]}),1);
		ans+=c[ly][1]*c[lx][0],c[ly][0]+=c[lx][0],c[ly][1]+=c[lx][1],ji[lx]=ly;
	}
	cout<<ans;
	return 0;
}
