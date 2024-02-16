#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#define inf 2147483647
#define PA pair<int,int>
#define fi first
#define se second
#define MP make_pair
using namespace std;
const int maxl=500005;

int read(){
	int s=0,w=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-')  w=-w;ch=getchar();}
	while (ch>='0'&&ch<='9'){s=(s<<1)+(s<<3)+(ch^'0');ch=getchar();}
	return s*w;
}
int n,q;
int a[maxl],nxt[maxl],frt[maxl],f[maxl],res[maxl];

struct node{int l,r,id;};vector<node> lis;
vector<PA >ve;
vector<int> lian[maxl];

namespace ducati{
	int pos=0,T=0,sta[maxl],vis[maxl],bel[maxl];
	void get_all_in(){
		n=read(),q=read();
		for (int i=1;i<=n;i++)  a[i]=read();
		for (int i=1;i<=q;i++){
			int l=read(),r=read();
			lis.push_back(node{l,r,i});
		}
	}
	void init_lian(){
		for (int i=1;i<=n;i++){
			if (vis[i])  continue;
			
			int now=i;T++;
			while (now)  bel[now]=T,vis[now]=1,lian[T].push_back(now),now=nxt[now];
		}
	}
	void init_nxt(){
		a[sta[pos=0]=n+1]=inf;
		for (int i=n;i>=1;i--){
			while (a[sta[pos]]<a[i])  pos--;
			if (a[i]==a[sta[pos]])  nxt[i]=sta[pos],frt[nxt[i]]=i;
			sta[++pos]=i;
		}
	}
	void deal_left(int le,int ri,int mid){
		f[ri]=0;
		for (int i=ri-1;i>=le;i--){
			if (nxt[i]&&nxt[i]<=ri)  f[i]=f[nxt[i]]+(nxt[i]-i);
			else f[i]=0;
		}
		for (int i=ri-1;i>=le;i--)  f[i]=max(f[i],f[i+1]);
		for (auto t:lis){
			if (t.l<=mid&&t.r>mid)  res[t.id]=max(res[t.id],f[t.l]);
		}
	}
	void deal_right(int le,int ri,int mid){
		f[le]=0;
		for (int i=le+1;i<=ri;i++){
			if (frt[i]&&frt[i]>=le)  f[i]=f[frt[i]]+(i-frt[i]);
			else f[i]=0;
		}
		for (int i=le+1;i<=ri;i++)  f[i]=max(f[i],f[i-1]);
		for (auto t:lis){
			if (t.l<=mid&&t.r>mid)  res[t.id]=max(res[t.id],f[t.r]);
		}
	}
	int get_val(int L,int R,int id){
		int ll=lower_bound(lian[id].begin(),lian[id].end(),L)-lian[id].begin();
		int rr=upper_bound(lian[id].begin(),lian[id].end(),R)-lian[id].begin()-1;
		return lian[id][rr]-lian[id][ll];
	}
	void deal_over_mid(int le,int ri,int lim){
		ve.clear();
		for (int i=le;i<=ri;i++){
			if (nxt[i]>ri&&nxt[i]<=lim)  ve.push_back(MP(i,nxt[i]));
		}
		if (!ve.size())  return;
		
		for (auto t:lis){
			if (t.l>ri||t.r<=ri)  continue;
			
			int L=t.l,R=t.r,l=0,r=ve.size()-1,pos=0;
			while (l<=r){
				int mid=(l+r)>>1;
				if (ve[mid].fi<L||ve[mid].se>R)  l=mid+1;
				else pos=mid,r=mid-1;
			}
			res[t.id]=max(res[t.id],get_val(L,R,bel[ve[pos].fi]));
		}
	}
	void calc(int l,int r,int mid){
		deal_left(l,mid,mid),deal_right(mid+1,r,mid),deal_over_mid(l,mid,r);
	}
	void work(int l,int r){
		if (l==r)  return;
		if (lis.size())  calc(l,r,(l+r)>>1);
		
		int mid=(l+r)>>1;vector<node> lis2;
		for (auto t:lis){
			if (t.r<=mid)  lis2.push_back(t);
		}
		swap(lis,lis2),work(l,mid);
		swap(lis,lis2),lis2.clear();
		for (auto t:lis){
			if (t.l>mid)  lis2.push_back(t);
		}
		swap(lis,lis2),work(mid+1,r);
		swap(lis,lis2),lis2.clear();
	}
	void print_ans(){
		for (int i=1;i<=q;i++)  printf("%d\n",res[i]+1);
	}
	void solve(){
		get_all_in();
		init_nxt(),init_lian();
		work(1,n);
		print_ans();
	}
}

signed main(){
	freopen("spiral.in","r",stdin);
	freopen("spiral.out","w",stdout);
	
	ducati::solve();
	return 0;
}
