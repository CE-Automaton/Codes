#include<bits/stdc++.h>
#define F(i,l,r) for(int i=l;i<r;++i)
#define Fe(i,l,r) for(int i=l;i<=r;++i)
#define Fer(i,l,r) for(int i=l;i>=r;--i)
#if 1
#define pr(...) fprintf(stderr,__VA_ARGS__)
#else
#define pr(...) void(0)
#endif

typedef long long i64;
const int maxn=1e6,maxm=1e6,inf=1e9,N=1.1e6+10;

int read(int L,int R){
	int x;
	assert(scanf("%d",&x)==1);
	assert(L<=x&&x<=R);
	return x;
}
struct A{
	int y,t;
}a[N];

struct M{
	int t1,t2,x,y;
	bool operator<(const M &w)const{return x<w.x;}
}ms[N*2];
struct Q{
	int t,x;
	bool operator<(const Q &w)const{return x<w.x;}
}qs[N];
i64 ans[N];
int v[N];
i64 vs[N];

using std::min;
using std::max;
struct Tag{
	int mn,s0,s1;
	i64 smn;
	void operator*=(int t){
		mn=max(mn,t);
	}
	void operator*=(const Tag &t){
		assert(mn<t.mn||t.mn==0);
		smn+=t.smn;
		s1+=t.s1;
		if(!mn)s0+=t.s0;
		else{
			smn+=i64(t.s0)*mn;
			s1+=t.s0;
		}
		if(t.mn)mn=t.mn;
	}
	void clr(){
		mn=0;
		s0=0;
		s1=0;
		smn=0;
	}
}_op2{0,1,0,0};
struct Data{
	int mn,mn2,mnc;
	i64 s,ss;
	void operator*=(int t){
		assert(mn<t&&t<mn2);
		s+=i64(t-mn)*mnc;
		mn=t;
	}
	void operator*=(const Tag &t){
		if(t.mn==0&&t.s0==0&&t.s1==0&&t.smn==0)return;
		ss+=t.s0*s+mnc*t.smn+(s-i64(mn)*mnc)*t.s1;
		if(t.mn)*this*=t.mn;
	}
	void clr(){
		mn=0;
		mn2=inf;
		mnc=1;
		s=0;
		ss=0;
	}
	void up(const Data &a,const Data &b){
		mn=min(a.mn,b.mn);
		mn2=min(a.mn2,b.mn2);
		mnc=0;
		if(mn!=a.mn)mn2=min(mn2,a.mn);
		else mnc+=a.mnc;
		if(mn!=b.mn)mn2=min(mn2,b.mn);
		else mnc+=b.mnc;
		s=a.s+b.s;
		ss=a.ss+b.ss;
	}
	operator i64(){
		return ss;
	}
};
int _l,_r,_v;
i64 _s;
struct Node{
	Node *lc,*rc;
	int L,R;
	Tag tag;
	Data data;
	void app(Tag t){
		if(t.mn<=data.mn)t.mn=0,t.smn=t.s1*i64(data.mn);
		tag*=t;
		data*=t;
	}
	void dn(){
		lc->app(tag);
		rc->app(tag);
		tag.clr();
	}
	void up(){
		data.up(lc->data,rc->data);
	}
	void upd1(){
		if(_v<=data.mn)return;
		if(_l<=L&&R<=_r&&_v<data.mn2){
			tag*=_v;
			data*=_v;
			assert(tag.mn==data.mn);
			return;
		}
		dn();
		int M=(L+R)>>1;
		if(_l<=M)lc->upd1();
		if(_r>M)rc->upd1();
		up();
	}
	void upd2(){
		app(_op2);
	}
	void que(){
		if(_l<=L&&R<=_r){
			_s+=data;
			return;
		}
		dn();
		int M=(L+R)>>1;
		if(_l<=M)lc->que();
		if(_r>M)rc->que();
	}
}ns[N*2],*np=ns,*rt;

Node *build(int L,int R){
	Node *w=np++;
	w->L=L;
	w->R=R;
	w->tag.clr();
	if(L==R){
		w->data.clr();
	}else{
		int M=(L+R)>>1;
		w->lc=build(L,M);
		w->rc=build(M+1,R);
		w->up();
	}
	return w;
}

int main(){
	int n=read(1,maxn);
	int m=read(1,maxm);
	int mp=0,qp=0;
	Fe(t,1,m){
		int x=read(1,n),y=read(1,n);
		if(a[x].y){
			ms[mp++]=M{a[x].t,t-1,x,a[x].y};
		}
		a[x].y=y;
		a[x].t=t;
		qs[qp++]=Q{t,x};
	}
	Fe(x,1,n){
		if(a[x].y){
			ms[mp++]=M{a[x].t,m,x,a[x].y};
		}
	}
	std::sort(ms,ms+mp);
	std::sort(qs,qs+qp);
	rt=build(1,m);
	int mp1=0,qp1=0;
	Fe(x,1,n){
		for(;mp1<mp&&ms[mp1].x==x;++mp1){
			M &q=ms[mp1];
			_l=q.t1;_r=q.t2;
			_v=q.y;
			rt->upd1();
		}
		rt->upd2();
		for(;qp1<qp&&qs[qp1].x==x;++qp1){
			int t=qs[qp1].t;
			_l=1,_r=t;_s=0;
			rt->que();
			ans[t]=_s;
		}
	}
	Fe(i,1,m)printf("%lld\n",ans[i]);
	return 0;
}
