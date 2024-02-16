#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
struct node
{
	int l,r,v;
}mxp[19][500005];
int l[500005],p2[19],n,m,a[500005],cnt,nxt[500005],pre[500005],stf[19][500005],stg[19][500005],s[500005],tp;
int query(int L,int R)
{
	int t=l[R-L+1];
	return max(mxp[t][L].v,mxp[t][R-p2[t]+1].v);
}
int queryf(int L,int R)
{
	if(L>R)
		return 1;
	int t=l[R-L+1];
	return max(stf[t][L],stf[t][R-p2[t]+1]);
}
int queryg(int L,int R)
{
	if(L>R)
		return 1;
	int t=l[R-L+1];
	return max(stg[t][L],stg[t][R-p2[t]+1]);
}
pair<int,int>querymx(int L,int R)
{
	int t=l[R-L+1],lans=mxp[t][L].v,rans=mxp[t][R-p2[t]+1].v,mx=max(lans,rans),lp=R,rp=L;
	if(mx==lans)
		lp=min(lp,mxp[t][L].l),rp=max(rp,mxp[t][L].r);
	if(mx==rans)
		lp=min(lp,mxp[t][R-p2[t]+1].l),rp=max(rp,mxp[t][R-p2[t]+1].r);
	return make_pair(lp,rp);
}
inline char gc()
{
	static char buf[1048576],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,1048576,stdin),p1==p2)?EOF:*p1++;
}
inline int read()
{
	register int x=0;
	register char ch=gc(),flag=0;
	while(ch<'0'||ch>'9')
		flag|=(ch=='-'),ch=gc();
	while(ch>='0'&&ch<='9')
		x=(x<<3)+(x<<1)+ch-'0',ch=gc();
	return flag?~x+1:x;
}
char pbuf[1 << 20], *pp = pbuf;

inline void push(const char &c) {
  if (pp - pbuf == 1 << 20) fwrite(pbuf, 1, 1 << 20, stdout), pp = pbuf;
  *pp++ = c;
}

inline void write(int x) {
  static int sta[35];
  int top = 0;
  do {
    sta[top++] = x % 10, x /= 10;
  } while (x);
  while (top) push(sta[--top] + '0');
}
int main()
{
	freopen("spiral.in","r",stdin);
	freopen("spiral.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=n;++i)
		a[i]=read();
	l[1]=0;
	for(int i=2;i<=n;++i)
		l[i]=l[i/2]+1;
	for(int i=0;i<=18;++i)
		p2[i]=1<<i;
	for(int i=1;i<=n;++i)
		mxp[0][i].v=a[i],mxp[0][i].l=mxp[0][i].r=i;
	for(int j=1;j<=l[n];++j)
		for(int i=1;i+p2[j]-1<=n;++i)
		{
			mxp[j][i].v=max(mxp[j-1][i].v,mxp[j-1][i+p2[j-1]].v);
			mxp[j][i].l=2147483647;
			if(mxp[j][i].v==mxp[j-1][i].v)
				mxp[j][i].l=mxp[j-1][i].l,mxp[j][i].r=mxp[j-1][i].r;
			if(mxp[j][i].v==mxp[j-1][i+p2[j-1]].v)
				mxp[j][i].l=min(mxp[j][i].l,mxp[j-1][i+p2[j-1]].l),mxp[j][i].r=mxp[j-1][i+p2[j-1]].r;
		}
	for(int i=1;i<=n;++i)
	{
		while(tp&&a[i]>a[s[tp]])
			--tp;
		if(tp&&a[s[tp]]==a[i])
			pre[i]=s[tp];
		else
			pre[i]=s[++tp]=i;
	}
	tp=0;
	for(int i=n;i;--i)
	{
		while(tp&&a[i]>a[s[tp]])
			--tp;
		if(tp&&a[s[tp]]==a[i])
			nxt[i]=s[tp];
		else
			nxt[i]=s[++tp]=i;
	}
	for(int i=1;i<=n;++i)
		stf[0][i]=nxt[i]-i+1,stg[0][i]=i-pre[i]+1;
	for(int j=1;j<=l[n];++j)
		for(int i=1;i+p2[j]-1<=n;++i)
			stf[j][i]=max(stf[j-1][i],stf[j-1][i+p2[j-1]]),stg[j][i]=max(stg[j-1][i],stg[j-1][i+p2[j-1]]);
	while(m--)
	{
		int l,r;
		l=read(),r=read();
		pair<int,int>p=querymx(l,r);
		int ans=max(queryf(l,p.first-1),queryg(p.second+1,r));
		if(p.first!=p.second)
			ans=max(ans,p.second-p.first+1);
		write(ans),push('\n');
	}
	fwrite(pbuf,pp-pbuf,1,stdout);
	return 0;
}

