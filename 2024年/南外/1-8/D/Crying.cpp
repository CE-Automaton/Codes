#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
using namespace std;
const ll MAXN = 5e5+10,INF = 1e18;
void tomin(ll& x,ll y){x = min(x,y);}
void tomax(ll& x,ll y){x = max(x,y);}

int n,tot,a[MAXN],b[MAXN],x;

ll f[MAXN];

set<int> S;


#define mid ((l+r)>>1)
struct myArray{ //支持单点求点值
	ll tk[MAXN<<2],tb[MAXN<<2],val[MAXN];
	void Init(){
		rep(i,2,tot)val[i] = INF;
	}
	void add(int x,ll vk,ll vb){tk[x] += vk; tb[x] += vb;}
	void pd(int x){
		add(lc(x),tk[x],tb[x]); add(rc(x),tk[x],tb[x]);
		tk[x] = tb[x] = 0;
	}
	void mdf(int x,int l,int r,int ql,int qr,ll vk,ll vb){
		if(ql>qr)return; if(ql<=l && qr>=r)return add(x,vk,vb);
		pd(x);
		if(ql<=mid)mdf(lc(x),l,mid,ql,qr,vk,vb);
		if(qr>mid)mdf(rc(x),mid+1,r,ql,qr,vk,vb);
	}
	void mdf(int x,int l,int r,int pos,ll w){
		if(l==r){
			if(val[l] + tb[x] + tk[x] * b[l] > w){
				val[l] = w;
				tk[x] = tb[x] = 0;
			}
			return;
		}
		pd(x);
		(pos<=mid)?(mdf(lc(x),l,mid,pos,w)):(mdf(rc(x),mid+1,r,pos,w));
	}
	ll qry(int x,int l,int r,int pos){
		if(l==r)return val[l] + tb[x] + tk[x] * b[l];
		pd(x);
		return (pos<=mid)?qry(lc(x),l,mid,pos):qry(rc(x),mid+1,r,pos);
	}
	ll operator[](int x){return qry(1,1,tot,x);}
}arr;
struct Seg{ //用于快速找到min和minidx
	ll mn[MAXN<<2],pos[MAXN<<2],tag[MAXN<<2];
	void pu(int x){
		if(mn[lc(x)] <= mn[rc(x)])mn[x] = mn[lc(x)],pos[x] = pos[lc(x)];
		else mn[x] = mn[rc(x)],pos[x] = pos[rc(x)];
	}
	void add(int x,ll v){
		mn[x] += v,tag[x] += v;
	}
	void pd(int x){
		if(!tag[x])return;
		add(lc(x),tag[x]),add(rc(x),tag[x]);
		tag[x]=0;
	}
	//
	void build(int x,int l,int r){
		mn[x] = INF;pos[x] = l;
		if(l==r)return;
		build(lc(x),l,mid),build(rc(x),mid+1,r);
	}
	void mdf(int x,int l,int r,int ql,int qr,ll val){
		if(ql>qr)return; if(ql<=l && qr>=r)return add(x,val);
		pd(x);
		if(ql<=mid)mdf(lc(x),l,mid,ql,qr,val);
		if(qr>mid)mdf(rc(x),mid+1,r,ql,qr,val);
		pu(x);
	}
	void mdf(int x,int l,int r,int pos,ll val){
		if(l==r)return void(mn[x] = val);
		pd(x);
		(pos<=mid)?(mdf(lc(x),l,mid,pos,val)):(mdf(rc(x),mid+1,r,pos,val));
		pu(x);
	}
}seg;
#undef mid

ll qry_pre(int x){
	auto it = S.upper_bound(x); 
	if(it == S.begin())return INF;
	else return arr[*prev(it)];
}

ll calc(int x,int y){ //计算x何时干掉y	
	ll d = arr[x] - arr[y],dx = b[y]-b[x],t = max(0LL,(d+dx-1)/dx);
	return t;
}

void ins(int x){ //插入决策点x
	if(S.find(x) != S.end())return;
	auto it = S.upper_bound(x);
	int y = -1;
	if(it != S.begin()){
		y = *prev(it);
		/*
		if(x==4){
			printf("\n\n\npre %d\n",y);
			printf("with %lld %lld\n",arr[y],arr[x]);
			printf("\n\n\n");
		}
		*/
		if(arr[y] <= arr[x])return;
	}
	//
	S.insert(x);
	if(it != S.end()){
		int z = *it;

		seg.mdf(1,1,tot,x,calc(x,z));
	}		
	if(y != -1){
		seg.mdf(1,1,tot,y,calc(y,x));
	}
}

void rmdf(int p){ //<p的和>=p的
	auto it = S.lower_bound(p);
	if(it == S.end() || it == S.begin())return;
	int x = *prev(it),y = *it;
	seg.mdf(1,1,tot,x,calc(x,y));
}

int main(){
	freopen("stairs.in","r",stdin);
	freopen("stairs.out","w",stdout);

	ios::sync_with_stdio(false); cin.tie(0);

	cin>>n;
	rep(i,1,n)cin>>a[i],b[++tot] = a[i];
	b[++tot] = 0;
	sort(b+1,b+1+tot); tot = unique(b+1,b+1+tot)-b-1;
	rep(i,1,n)a[i] = lower_bound(b+1,b+1+tot,a[i])-b;
	//
	arr.Init();
	seg.build(1,1,tot);

	S.insert(1);
	
	rep(i,1,n){
		int y = a[i];
		//printf("add %d : %d\n",i,y);
		if(x<=y){
			ll mn = qry_pre(tot);
			arr.mdf(1,1,tot,1,tot,0,b[y]);

			arr.mdf(1,1,tot,x,mn+b[y]);
		}else{
			ll mn = qry_pre(y-1); 

			arr.mdf(1,1,tot,1,y-1,0,b[x]);
			arr.mdf(1,1,tot,y,x-1,1,0);
			arr.mdf(1,1,tot,x,tot,0,b[x]);
			
			arr.mdf(1,1,tot,y,mn+b[y]);

			seg.mdf(1,1,tot,y,x-1,-1);

			//printf("sub [%d,%d]\n",y,x-1);

			rmdf(y);
			rmdf(x);

			//if(i==5)printf("HERE : %lld\n",arr[4]);

			ins(y);
		}
		x = max(x,y);
		//不断合并
		//printf("pre merge : ");printf("S: ");for(auto u : S)cout<<u<<" ";cout<<endl;
		//printf("get %lld\n",seg.mn[1]);
		while(seg.mn[1] == 0){
			int x = seg.pos[1]; 
			auto it = S.find(x); 
			assert(it != S.end());
			it = next(it); 
			assert(it != S.end());
			int y = *it;
			it = next(it);

			//printf("merge (%d,%d)\n",x,y);

			S.erase(y);
			seg.mdf(1,1,tot,y,INF);

			if(it != S.end()){
				int z = *it;
				ll t = calc(x,z);
				seg.mdf(1,1,tot,x,t);
			}else{
				seg.mdf(1,1,tot,x,INF);
			}
		}
		//printf("done merge : ");for(auto u : S)cout<<u<<" ";cout<<endl;
		/*
		rep(j,1,tot){
			printf("%d : %lld\n",j,arr[j]);
		}
		printf("\n");
		printf("done get : %lld\n",seg.mn[1]);
		*/
	}
	
	ll ans = qry_pre(tot);
	cout<<ans<<endl;

    return 0;
}
