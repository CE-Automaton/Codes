#include<stdio.h>
#include<bits/stdc++.h>
#define fir first
#define sec second
#define all(x) begin(x),end(x)
using namespace std;
typedef long long ll;
typedef unsigned uint;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
typedef __int128 int128;
typedef __uint128_t uint128;
typedef pair<int,int> pii;
template<typename type>
inline void chmin(type &x,const type &y)
{
	if(y<x)
		x=y;
}
template<typename type>
inline void chmax(type &x,const type &y)
{
	if(x<y)
		x=y;
}
bool mmp1;
constexpr int Max=5e5+10,Size=1048576;
constexpr ll inf=1e18;
int n,a[Max],num[Max],lim;
#define ls(p) ((p)<<1)
#define rs(p) ((p)<<1|1)
struct line
{
	ll k,b;
	inline line()
	{
		k=0,b=0;
	}
	inline line(const ll &k,const ll &b)
	{
		this->k=k,this->b=b;
	}
	inline bool operator <(const line &rhs)const
	{
		return b==rhs.b?k<rhs.k:b<rhs.b;
	}
	inline friend ll cross(line u,line v)
	{
		if(v<u)
			swap(u,v);
		if(u.k<=v.k)
			return inf;
		return max<ll>((v.b-u.b)/(u.k-v.k),1);
	}
};
line t[Size];
ll pos[Size];
ll tag1[Size],tag2[Size];
inline void push_up(int p)
{
	t[p]=min(t[ls(p)],t[rs(p)]);
	pos[p]=min(pos[ls(p)],pos[rs(p)]);
	chmin(pos[p],cross(t[ls(p)],t[rs(p)]));
}
inline void set_tag1(int p,const ll &x)
{
	pos[p]-=x,t[p].b+=t[p].k*x;
	tag1[p]+=x;
}
inline void set_tag2(int p,const ll &x)
{
	t[p].b+=x;
	tag2[p]+=x;
}
void push_down(int p)
{
	if(tag1[p])
	{
		set_tag1(ls(p),tag1[p]);
		set_tag1(rs(p),tag1[p]);
		tag1[p]=0;
	}
	if(tag2[p])
	{
		set_tag2(ls(p),tag2[p]);
		set_tag2(rs(p),tag2[p]);
		tag2[p]=0;
	}
}
void update(const int &ql,const int &qr,int p,int l,int r,const ll &x)
{
	if(l>=ql&&r<=qr&&pos[p]>x)
	{
		set_tag1(p,x);
		return;
	}
	push_down(p);
	int mid=(l+r)>>1;
	if(ql<=mid)
		update(ql,qr,ls(p),l,mid,x);
	if(qr>=mid+1)
		update(ql,qr,rs(p),mid+1,r,x);
	push_up(p);
}
void add(const int &ql,const int &qr,int p,int l,int r,const ll &x)
{
	if(l>=ql&&r<=qr)
	{
		set_tag2(p,x);
		return;
	}
	push_down(p);
	int mid=(l+r)>>1;
	if(ql<=mid)
		add(ql,qr,ls(p),l,mid,x);
	if(qr>=mid+1)
		add(ql,qr,rs(p),mid+1,r,x);
	push_up(p);
}
void modify(const int &x,int p,int l,int r,const ll &y)
{
	if(l==r)
	{
		t[p]=line(num[l],y);
		return;
	}
	push_down(p);
	int mid=(l+r)>>1;
	if(x<=mid)
		modify(x,ls(p),l,mid,y);
	else
		modify(x,rs(p),mid+1,r,y);
	push_up(p);
}
ll query(const int &ql,const int &qr,int p,int l,int r)
{
	if(l>=ql&&r<=qr)
		return t[p].b;
	push_down(p);
	int mid=(l+r)>>1;
	ll ans=inf;
	if(ql<=mid)
		chmin(ans,query(ql,qr,ls(p),l,mid));
	if(qr>=mid+1)
		chmin(ans,query(ql,qr,rs(p),mid+1,r));
	return ans;
}
void build(int p,int l,int r)
{
	if(l==r)
	{
		t[p]=line(num[l],0);
		pos[p]=inf;
		return;
	}
	push_down(p);
	int mid=(l+r)>>1;
	build(ls(p),l,mid);
	build(rs(p),mid+1,r);
	push_up(p);
}
#undef ls
#undef rs
bool mmp2;
signed main()
{
//	cerr<<(&mmp1-&mmp2)/1048576.0<<"\n";
	freopen("stairs.in","r",stdin),freopen("stairs.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>a[i],num[i]=a[i];
	sort(num+1,num+n+1);
	lim=unique(num+1,num+n+1)-num-1;
	for(int i=1;i<=n;++i)
		a[i]=lower_bound(num+1,num+lim+1,a[i])-num;
	build(1,0,lim);
	int w=0;
	for(int i=1;i<=n;++i)
	{
		const ll x=num[a[i]],y=num[w];
		const ll tmp=query(0,a[i],1,0,lim);
		if(a[i]>w)
		{
			modify(a[i],1,0,lim,tmp);
			add(0,lim,1,0,lim,x);
			w=a[i];
		}
		else
		{
			modify(a[i],1,0,lim,tmp+x);
			add(0,a[i]-1,1,0,lim,y);
			if(a[i]<lim)
				update(a[i]+1,lim,1,0,lim,1);
		}
	}
	cout<<query(0,lim,1,0,lim)<<"\n";
	return 0;
}
