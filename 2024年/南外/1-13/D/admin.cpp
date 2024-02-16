#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<vector>
#include<map>
#include<vector>
using namespace std;
template<class T> inline bool ten(T &x,const T &y){return y<x?x=y,1:0;}
template<class T> inline bool rel(T &x,const T &y){return x<y?x=y,1:0;}
inline void readi(int &x);
const int maxn=500005;

int n,m,L[maxn],R[maxn],ans[maxn];
int A[maxn],lg2[maxn],cur[maxn],nex[maxn];
int st[maxn][20];

map<int,int> mem;

bool vis[maxn],big[maxn];
vector<int> seq;
vector<pair<int,int> > Q[maxn];

int tr[maxn];

void Add(int x,int c)
{for(;x<=n;x+=x&-x)rel(tr[x],c);}

int Get(int x)
{int s=0;for(;x;x^=x&-x)rel(s,tr[x]);return s;}

int Max(int l,int r)
{
	int k=lg2[++r-l];
	return max(st[l][k],st[r-(1<<k)][k]);
}

int main()
{ 
	freopen("spiral.in","r",stdin);
	freopen("spiral.out","w",stdout);
	readi(n),readi(m);
	lg2[0]=-1;
	for(int i=1;i<=n;i++)
		readi(A[i]),st[i][0]=A[i],lg2[i]=lg2[i>>1]+1;
	for(int i=1;i<=m;i++)
	{
		readi(L[i]),readi(R[i]);
		Q[L[i]].push_back(make_pair(R[i],i));
		ans[i]=1;
	}
	for(int j=1;j<=19;j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
			st[i][j]=max(st[i][j-1],st[i+(1<<j-1)][j-1]);
	for(int i=n,j;i;i--)
	{
		if(mem.count(A[i]))
		{
			j=mem[A[i]];
			if(Max(i,j)<=A[i])nex[i]=j;
		}
		mem[A[i]]=i;
	}
	int lim=sqrt(n/(log(n)/log(2)));
	for(int i=1;i<=n;i++)
		if(!vis[i])
		{
			seq.clear();
			seq.push_back(0);
			for(int j=i;j;j=nex[j])
			{
				seq.push_back(j);
				vis[j]=1;
			}
			if(seq.size()>=lim)
			{
				for(int j=1,k=0;j<=n;j++)
				{
					for(;k<seq.size()&&j>=seq[k];k++)big[seq[k]]=1;
					cur[j]=k-1;
				}
				for(int j=1,x,y;j<=m;j++)
					if(cur[L[j]-1]+1<seq.size())
					{
						x=seq[cur[L[j]-1]+1];
						y=seq[cur[R[j]]];
						rel(ans[j],y-x+1);
					}
			}
		}
	for(int i=n;i;i--)
	{
		if(!big[i])
		{
			for(int j=i;j;j=nex[j])
				Add(j,j-i+1);
		}
		for(int j=0;j<Q[i].size();j++)
			rel(ans[Q[i][j].second],Get(Q[i][j].first));
	}
	for(int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
	return 0;
}

inline void readi(int &x)
{char c;bool fl;while(c=getchar(),c!='-'&&(c<'0'||c>'9'));
if(c=='-')x=0,fl=1;else x=c-'0',fl=0;
while(c=getchar(),c>='0'&&c<='9')x=x*10+c-'0';
if(fl)x=-x;}
