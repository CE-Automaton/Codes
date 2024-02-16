#include <bits/stdc++.h>
#define pdd pair<double,double>
#define fi first
#define se second
#define sq(x) ((x)*(x))
using namespace std;
inline int read(){
	char c;int f=1,res=0;
	while(c=getchar(),!isdigit(c))if(c=='-')f*=-1;
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res*f;
}
const int N=1e3+5;
const double eps=1e-11;
int n;double S;
struct node{double x,y,z,vx,vy,vz;}p[N];
inline pdd calc(int _u,int _v,double d){
	node u=p[_u],v=p[_v];d+=eps;
	double dx=u.x-v.x,dy=u.y-v.y,dz=u.z-v.z;
	double dvx=u.vx-v.vx,dvy=u.vy-v.vy,dvz=u.vz-v.vz;
	double A=sq(dvx)+sq(dvy)+sq(dvz);
	double B=2*(dvx*dx+dvy*dy+dvz*dz);
	double C=sq(dx)+sq(dy)+sq(dz)-sq(d);
	if(A<eps)return C<=0?pdd{0,1/eps}:pdd{-1,-1};
	if(sq(B)-4*A*C<-eps)return {-1,-1};
	double s=(-B-sqrt(sq(B)-4*A*C))/2/A;
	double t=(-B+sqrt(sq(B)-4*A*C))/2/A;
	return {max(0.0,s),t};
}
vector<double> f[N],s[N];
vector<int> t0[N],t1[N];
struct edge{pdd t;int v;};
inline bool operator<(edge x,edge y)
	{return x.t<y.t;}
vector<edge> g[N];int id[N][N];
inline bool build(double d){
	for(int u=1;u<=n;++u){
		g[u].resize(0);t0[u].resize(0);
		t1[u].resize(0);f[u].resize(0);s[u].resize(0);
		for(int v=1;v<=n;++v){
			if(u==v)continue;
			pdd t=calc(u,v,d);
			if(t.fi<0)continue;
			g[u].push_back({t,v});
		}sort(g[u].begin(),g[u].end());
		if(u==1&&(g[u].empty()||g[u][0].t.fi>S))
			return false;
		double lst=-1;int i=-1;
		for(edge e:g[u]){++i;
			if(lst<e.t.fi){
				t0[u].push_back(i);
				t1[u].push_back(i);
				s[u].push_back(lst=e.t.se+S);
			}else{
				t1[u].back()=i;
				s[u].back()=(lst=max(lst,e.t.se+S));
			}id[e.v][u]=t0[u].size()-1;
		}f[u].resize(t0[u].size(),1/eps);
	}return true;
}
struct st{int u,i;double t;};
inline bool operator<(st x,st y)
	{return x.t==y.t?x.u<y.u:x.t>y.t;}
priority_queue<st> q;
inline bool chk(double d){
	if(!build(d))return false;
	q.push({1,0,f[1][0]=0});
	while(!q.empty()){
		st cur=q.top();q.pop();
		int u=cur.u,i=cur.i;double t=cur.t;
		if(fabs(t-f[u][i])>=eps)continue;
		int b=lower_bound(s[u].begin(),s[u].end(),t)-s[u].begin();
		if(b>=s[u].size())continue;
		for(int j=t0[u][b];j<=t1[u][b];++j){
			if(g[u][j].t.se<t)continue;
			int v=g[u][j].v;double nt=max(t,g[u][j].t.fi);
			if(nt<f[v][id[u][v]])
				q.push({v,id[u][v],f[v][id[u][v]]=nt});
		}
	}for(double x:f[2])
		if(x<(1/eps))return true;
	return false;
}
int main(){
	freopen("rebel.in","r",stdin);
	freopen("rebel.out","w",stdout);
	n=read();S=read();
	for(int i=1;i<=n;++i){
		p[i].x=read();p[i].y=read();p[i].z=read();
		p[i].vx=read();p[i].vy=read();p[i].vz=read();
	}double l=0,r=2e3;
	while(r-l>1e-8){
		double mid=(l+r)/2;
		if(chk(mid))r=mid;
		else l=mid;
	}printf("%.4lf",l);
	return 0;
}

