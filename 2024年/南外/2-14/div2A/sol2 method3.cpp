#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define INF 1000000007
int read()
{
	char c=getchar();
	int x=0;
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x;
}
struct node
{
	int id,p;
	friend bool operator<(node x,node y)
	{
		return x.p<y.p;
	}
};
int n,m,k,a[100005],l[200005],r[200005],ans[100005];
bool vis[200005],dp[200005];
vector<int>g[200005];
tree<node,null_type,less<node>,rb_tree_tag,tree_order_statistics_node_update>st;
void dfs(int x,int res)
{
	vis[x]=1;
	if(g[x].empty())
	{
		ans[x]=min(ans[x],res);
		if(a[x]>k)
			dp[x]=1;
		return;
	}
	for(int i=0;i<g[x].size();i++)
	{
		int y=g[x][i];
		if(dp[x])
			dfs(y,0);
		else
			dfs(y,res+1);
		dp[x]|=dp[y];
	}
}
int main()
{
	freopen("tournament.in","r",stdin);
	freopen("tournament.out","w",stdout);
	n=read(),m=read(),k=read();
	for(int i=1;i<n;i++)
		a[i]=read();
	for(int i=1;i<=n;i++)
	{
		l[i]=r[i]=i;
		st.insert({i,i});
	}
	for(int i=1;i<=m;i++)
	{
		int x=read(),y=read();
		auto ed=st.find_by_order(y),it=st.find_by_order(x);
		l[n+i]=l[it->id],r[n+i]=r[ed->id];
		ed++;
		while(it!=ed)
		{
			auto t=it;
			g[n+i].push_back(t->id);
			it++;
			st.erase(t);
		}
		st.insert({n+i,l[n+i]});
	}
	for(int i=1;i<=n;i++)
		ans[i]=INF;
	int st;
	if(k==n-1)
		st=0;
	else
		st=INF;
	for(int i=n+m;i>n;i--)
		if(!vis[i])
			dfs(i,st);
	for(int i=1;i<=n;i++)
		if(!vis[i])
			ans[i]=0;
	for(int i=n;i>1;i--)
		a[i]=a[i-1];
	for(int i=1;i<=n+m;i++)
		reverse(g[i].begin(),g[i].end()),dp[i]=vis[i]=0;
	for(int i=n+m;i>n;i--)
		if(!vis[i])
			dfs(i,st);
	int res=-1,ap;
	for(int i=1;i<=n;i++)
		if(ans[i]>res)
			res=ans[i],ap=i;
	printf("%d",ap-1);
	return 0;
}
