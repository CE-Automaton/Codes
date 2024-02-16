#include<bits/stdc++.h>
using namespace std;
const int MAXN=5e5+5;
int a[MAXN],pre[MAXN],suf[MAXN],stk[MAXN],tp;
struct I { int l,r,id; };
int col[MAXN],ans[MAXN],f[MAXN];
vector <int> u[MAXN];
void solve(int l,int r,vector<I>&Q) {
	if(l==r||Q.empty()) return ;
	int mid=(l+r)>>1;
	vector <I> LQ,RQ,MQ;
	for(auto q:Q) {
		assert(l<=q.l&&q.r<=r);
		if(q.r<=mid) LQ.push_back(q);
		else if(q.l<=mid) MQ.push_back(q);
		else RQ.push_back(q);
	}
	for(int i=mid;i>=l;--i) f[i]=(suf[i]&&suf[i]<=mid)?f[suf[i]]+suf[i]-i:0;
	for(int i=mid+1;i<=r;++i) f[i]=(pre[i]&&pre[i]>mid)?f[pre[i]]+i-pre[i]:0;
	for(int i=mid-1;i>=l;--i) f[i]=max(f[i],f[i+1]);
	for(int i=mid+2;i<=r;++i) f[i]=max(f[i],f[i-1]);
	for(auto q:MQ) ans[q.id]=max(f[q.l],f[q.r]);
	vector <I> c;
	for(int i=l;i<=mid;++i) if(suf[i]&&suf[i]>mid) c.push_back({i,suf[i],col[i]});
	for(auto q:MQ) {
		int L=0,R=c.size()-1,e=c.size();
		while(L<=R) {
			int m=(L+R)>>1;
			if(q.l<=c[m].l&&c[m].r<=q.r) e=m,R=m-1;
			else L=m+1;
		}
		if(e<(int)c.size()) {
			auto&g=u[c[e].id];
			int rp=*--upper_bound(g.begin(),g.end(),q.r);
			int lp=*lower_bound(g.begin(),g.end(),q.l);
			ans[q.id]=max(ans[q.id],rp-lp);
		}
	} 
	solve(l,mid,LQ),solve(mid+1,r,RQ);
}
signed main() {
	freopen("spiral.in","r",stdin);
	freopen("spiral.out","w",stdout);
	int n,q,k=0;
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;++i) {
		scanf("%d",&a[i]);
		while(tp&&a[stk[tp]]<a[i]) --tp;
		if(a[stk[tp]]==a[i]) pre[i]=stk[tp],suf[stk[tp]]=i;
		stk[++tp]=i;
	}
	for(int i=1;i<=n;++i) if(!pre[i]) {
		++k;
		for(int j=i;j;j=suf[j]) u[k].push_back(j),col[j]=k;
	}
	vector <I> Q;
	for(int i=1,l,r;i<=q;++i) scanf("%d%d",&l,&r),Q.push_back({l,r,i});
	solve(1,n,Q);
	for(int i=1;i<=q;++i) printf("%d\n",ans[i]+1);
	return 0;
}
