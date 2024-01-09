#include<bits/stdc++.h>
using namespace std;
int n,m,p,q,k[100010][20],b[100010],c[100010],d[100010];
int num,to[400010],nxt[400010],first[400010];
inline int read()
{
	int x=0;char ac=getchar();
	while(ac<'0' || ac>'9') ac=getchar();
	while(ac>='0' && ac<='9') x=x*10+ac-'0',ac=getchar();
	return x; 
}
inline void add(int a,int b)
{
	num++;
	to[num]=b;
	nxt[num]=first[a];
	first[a]=num;
}
inline void dfs(int u,int d,int s) 
{
	if(k[u][d]) return ;
    k[u][d]=s;
    if(!d) return ;
    for(int i=first[u];i;i=nxt[i]) dfs(to[i],d-1,s);
    dfs(u,d-1,s);
}
int main() 
{
    freopen("clash.in", "r", stdin);
    freopen("clash.out", "w", stdout);
    n=read(),m=read(),p=read(),q=read();
    for(int i=1;i<=m;i++)
    {
    	int u=read(),v=read();
    	add(u,v),add(v,u);
	}
	for(int i=1;i<=q;i++)
		b[i]=read(),c[i]=read(),d[i]=read();
	for(int i=q;i;i--)
		dfs(c[i],d[i],b[i]);
    for(int i=1;i<=n;i++)
    	printf("%d\n",k[i][0]);
    return 0;
}
