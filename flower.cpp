#include<cstdio>
int n,q,v[100005],fa[1000005],f[1000005],p[20],qt[1000005],ans[100005],first[1000005],to[100005],id[100005],nxt[100005],num,cnt,to2[5500005],first2[1000005],nxt2[5500005];
int read(){char c=getchar();int x=0;while(c<'0'||c>'9')c=getchar();while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();return x;}
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
int main(){
    freopen("flower.in", "r", stdin);
    freopen("flower.out", "w", stdout);
	n=read(),q=read();
	for(int i=1;i<=n;++i)v[i]=read();
	for(int i=1;i<=1000001;++i)fa[i]=i;
	for(int i=2;i<=1000001;++i)if(!f[i])for(int j=i;j<=1000001;j+=i)f[j]=i;
	for(int i=1,a=v[i];i<=n;++i,a=v[i])while(a!=1)fa[find(f[a])]=find(v[i]),a/=f[a];
	for(int i=1,s,t;i<=q;++i){
		s=read(),t=read();
		int U=find(v[s]),V=find(v[t]);
		if(s==t)ans[i]=0;
		else if(v[s]==1||v[t]==1)ans[i]=-1;
		else if(U==V)ans[i]=0;
		else U<V?U^=V^=U^=V:0,to[++num]=U,id[num]=i,nxt[num]=first[V],first[V]=num;
	}
	for(int i=1,a=v[i],tot=0;i<=n;++i,a=v[i],tot=0){
		while(a!=1)p[++tot]=find(f[a]),a/=f[a];
		a=v[i]+1;
		while(a!=1)p[++tot]=find(f[a]),a/=f[a];
		for(int j=1;j<=tot;++j)for(int k=1;k<=tot;++k)if(k!=j&&p[j]<p[k])to2[++cnt]=p[k],nxt2[cnt]=first2[p[j]],first2[p[j]]=cnt;
	}
	for(int i=1;i<=1000001;++i){
		for(int j=first2[i];j;j=nxt2[j])qt[to2[j]]=1;
		for(int j=first[i];j;j=nxt[j])if(qt[to[j]])ans[id[j]]=1;else ans[id[j]]=2;
		for(int j=first2[i];j;j=nxt2[j])qt[to2[j]]=0;
	}
	for(int i=1;i<=q;++i){
		if(ans[i]==-1)putchar('-'),putchar('1');
		else if(!ans[i])putchar('0');
		else if(ans[i]==1)putchar('1');
		else putchar('2');
		putchar('\n');
	}
	return 0;
}
