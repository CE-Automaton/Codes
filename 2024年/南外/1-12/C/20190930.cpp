#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct node
{
	int val,sz;
	node*ch[2];
}tr[10000000];
int n,fi[100005],ne[200005],to[200005],cnt,ans[100005];
node*rt[100005],*tot=tr;
void build(node*&rt,int d,int v)
{
	if(!rt)
		rt=++tot;
	rt->sz=1;
	if(!d)
		return;
	build(rt->ch[v>>d-1&1],d-1,v);
}
void ae(int a,int b)
{
	to[++cnt]=b,ne[cnt]=fi[a],fi[a]=cnt;
}
int fd(node*x,node*y,int d)
{
	int res=0;
	while(d--)
	{
		int t=!x->ch[0];
		x=x->ch[t];
		if(y->ch[t])
			y=y->ch[t];
		else
			res+=1<<d,y=y->ch[t^1];
	}
	return res;
}
node*merge(node*x,node*y,int d)
{
	if(!x)
		return y;
	if(!y)
		return x;
	x->sz+=y->sz;
	if(!d)
		return x;
	x->ch[0]=merge(x->ch[0],y->ch[0],d-1),x->ch[1]=merge(x->ch[1],y->ch[1],d-1);
	if(!x->ch[0])
		x->val=x->ch[1]->val;
	else
		if(!x->ch[1])
			x->val=x->ch[0]->val;
		else
			if(x->ch[0]->sz==1)
				x->val=(1<<d-1)+fd(x->ch[0],x->ch[1],d-1);
			else
				if(x->ch[1]->sz==1)
					x->val=(1<<d-1)+fd(x->ch[1],x->ch[0],d-1);
				else
					x->val=max(x->ch[0]->val,x->ch[1]->val);
	return x;
}
void dfs(int u,int fa)
{
	for(int i=fi[u];i;i=ne[i])
		if(to[i]!=fa)
			dfs(to[i],u),rt[u]=merge(rt[u],rt[to[i]],17);
	ans[u]=rt[u]->sz>1?rt[u]->val:-1;
}
int main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	scanf("%d",&n);
	for(int i=1,v;i<=n;++i)
		scanf("%d",&v),build(rt[i],17,v);
	for(int i=1,a,b;i<n;++i)
		scanf("%d%d",&a,&b),ae(a,b),ae(b,a);
	dfs(1,0);
	for(int i=1;i<=n;++i)
		printf("%d\n",ans[i]);
	return 0;
}
