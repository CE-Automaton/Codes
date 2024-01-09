#include<bits/stdc++.h>
using namespace std;
template<typename T>inline void read(T &x){
    x=0;
    char ch=getchar();
    bool flag=0;
    while(ch>'9'||ch<'0') flag=flag||ch=='-',ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    x=flag?-x:x;
}
template<typename T,typename ...Args>inline void read(T &x,Args &...args){
    read(x),read(args...);
}
template<typename T>inline void prt(T x){
    if(x>9) prt(x/10);
    putchar(x%10+'0');
}
template<typename T>inline void put(T x){
    if(x<0) putchar('-'),x=-x;
    prt(x);
}
template<typename T>inline void put(char ch,T x){
    put(x),putchar(ch);
}
template<typename T,typename ...Args>inline void put(char ch,T x,Args ...args){
    put(ch,x),put(ch,args...);
}
#define N 1000005
struct info{
	int x,y;
	info(int _x=0,int _y=0):x(_x),y(_y){}
	inline info operator+(const info &B)const{
		return info(x+B.x,y+B.y);
	}
	inline info operator-(const info &B)const{
		return info(x-B.x,y-B.y);
	}
	inline long long operator^(const info &B)const{
		return 1ll*x*B.y-1ll*y*B.x;
	}
};
#define convex vector<info>
inline convex maintain(convex now){
	convex res;
	sort(now.begin(),now.end(),[](const info &A,const info &B){return (A.x==B.x?A.y>B.y:A.x<B.x);});
	for(auto tmp:now){
		while(res.size()>=2&&((tmp-res[res.size()-2])^(res[res.size()-1]-res[res.size()-2]))>=0) res.pop_back();
		res.emplace_back(tmp);
	}
	return res;
}
inline convex minkowski(convex A,convex B){
	if(!A.size()) return B;
	if(!B.size()) return A;
	for(int i=A.size()-1;i;i--) A[i]=A[i]-A[i-1];
	for(int i=B.size()-1;i;i--) B[i]=B[i]-B[i-1]; 
	convex C(A.size()+B.size()-1);
	C[0]=A[0]+B[0];
	int i=1,j=1,k=1;
	while(i<A.size()&&j<B.size())
		if((long long)A[i].y*B[j].x<(long long)B[j].y*A[i].x) C[k++]=A[i++];
		else C[k++]=B[j++];
	while(i<A.size()) C[k++]=A[i++];
	while(j<B.size()) C[k++]=B[j++];
	for(k=1;k<C.size();k++) C[k]=C[k]+C[k-1];
	return C;
}
int n,m,head[N],cnt=1; 
struct edge{
	int v,nxt,w;
}e[N<<1];
inline void add(int u,int v,int w){
	e[++cnt]=(edge){v,head[u],w},head[u]=cnt;
}
vector<int> vec;
bool vis[N];
int num_ed;
inline void dfs(int x){
	if(vis[x]) return;
	vis[x]=1,vec.emplace_back(x);
	for(int i=head[x];i;i=e[i].nxt)
		dfs(e[i].v),num_ed++;
}
int deg[N];
namespace Circle{
	int val1,val2,det1,det2;
	inline void dfs1(int x,int id,int fir){
		if(x==fir) return;
		for(int i=head[x];i;i=e[i].nxt){
			if(i==(id^1)||deg[e[i].v]<2) continue;
			if(x<=n) det1+=e[i].w;
			else det2+=e[i].w;
			dfs1(e[i].v,i,fir); 
		}
	} 
	inline convex insert_circle(){
		val1=val2=0;
		queue<int> q;	
		for(auto v:vec)
			if(deg[v]==1) q.push(v);
		while(!q.empty()){
			int x=q.front();q.pop();
			for(int i=head[x];i;i=e[i].nxt){
				int v=e[i].v;
				if(deg[v]<=1) continue;
				if(x<=n) val1+=e[i].w;
				else val2+=e[i].w;
				if(--deg[v]==1) q.push(v);
			}
		}
		int x=0;
		for(auto v:vec)
			if(deg[v]>1){
				x=v;
				break;
			}
		convex now;
		for(int i=head[x];i;i=e[i].nxt){
			int v=e[i].v;
			if(deg[v]<2) continue;
			det1=det2=0;
			if(x<=n) det1+=e[i].w;
			else det2+=e[i].w;
			dfs1(v,i,x);
			now.emplace_back(det1+val1,det2+val2);
		}
		return now;
	}
}
namespace Tree{
	int val1,val2;
	inline void dfs1(int x,int fa){
		for(int i=head[x];i;i=e[i].nxt){
			int v=e[i].v;
			if(v==fa) continue;
			dfs1(v,x);
			if(v<=n) val1+=e[i^1].w;
			else val2+=e[i^1].w;
		}
	}
	convex now;
	inline void dfs2(int x,int fa){
		now.emplace_back(val1,val2);
		for(int i=head[x];i;i=e[i].nxt){
			int v=e[i].v;
			if(v==fa) continue;
			if(v<=n) val1-=e[i^1].w,val2+=e[i].w;
			else val2-=e[i^1].w,val1+=e[i].w;
			dfs2(v,x);
			if(v<=n) val1+=e[i^1].w,val2-=e[i].w;
			else val2+=e[i^1].w,val1-=e[i].w; 
		}
	}
	inline convex insert_tree(){
		val1=val2=0,now.clear();
		dfs1(vec[0],0),dfs2(vec[0],0);
		return now;
	}
}
struct node{
	convex res;
	node(){}
	node(convex _res):res(_res){}
	inline bool operator<(const node &b)const{
		return res.size()>b.res.size();
	}
};
int main(){
    freopen("world.in","r",stdin);
    freopen("world.out","w",stdout);
	read(n,m);
	for(int i=1,x,y,a,b;i<=m;i++)
		read(x,y,a,b),add(x,y+n,a),add(y+n,x,b),deg[x]++,deg[y+n]++;
	priority_queue<node> q;
	for(int i=1;i<=n+n;i++){
		if(vis[i]) continue;
		num_ed=0,vec.clear(),dfs(i);
		num_ed>>=1;
		if(!num_ed) continue;
		convex res;
		if(vec.size()==num_ed) res=Circle::insert_circle();
		else if(vec.size()==num_ed+1) res=Tree::insert_tree();
		else exit(1);
		res=maintain(res);
		q.push(res);
	}
	while(q.size()>1){
		convex A=q.top().res;q.pop();
		convex B=q.top().res;q.pop();
		q.push(minkowski(A,B));
	}
	convex ans=q.top().res;
	long long res=2e18;
	for(int i=0;i<ans.size();i++)
		res=min(res,1ll*ans[i].x*ans[i].y);
	put('\n',res);
	return 0;
}
