#include<bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
#define mod 998244353
using namespace std;
const int BUF_SIZ=(1<<20);
char ibuf[BUF_SIZ],*iS=ibuf,*iT=ibuf;
#define getchar() (iS==iT&&(iT=(iS=ibuf)+fread(ibuf,1,BUF_SIZ,stdin)),iS==iT?EOF:*iS++)
template <typename _Tp>void read(_Tp &x){
	char ch(getchar());bool f(false);while(!isdigit(ch))f|=(ch==45),ch=getchar();
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch&15),ch=getchar();
	if(f)x=-x;
}
template <typename _Tp,typename... Args>void read(_Tp &t,Args &...args){read(t);read(args...);}
typedef unsigned long long ull;
int n,q;
struct MY_GENERATOR{
	int typ;ull sedd;
	inline ull nextInt(){
		ull z=(sedd+=0x9E37793B5F4A7C15ULL);
		z=(z^(z>>30))*0xBE99136D1CE4E5B9ULL;
		z=(z^(z>>27))*0x94A749BB033BD1FBULL;
		return z^(z>>31);
	}
	int get(){return nextInt()%998244352+1;}
	inline void get(int lastans,int &l,int &r){
		if(typ==2){
			if(!typ)lastans=0;
			l=((1+(nextInt()>>33))^lastans)%n+1;
			r=((1+(nextInt()>>33))^lastans)%n+1;
			if(l>r) swap(l,r);
		}
		else{
			read(l),read(r);
			if(typ)l^=lastans,r^=lastans;
		}
	}
}gen;
const int N=3000005;
int a[N],p[N],zhan[N],tot,ss[N],anss[5000005],rr[N];
struct qwq {
	int r, d;
};
struct node {
	int ll, rr, tr[2], lzy;
};
vector <qwq> pro[N];
int ksm(int x, int y, int ret = 1) {
	while(y) {
		if(y&1)
			ret=1LL*ret*x%mod;
		x=1LL*x*x%mod;
		y=(y>>1);
	}
	return ret;
}
struct tree {
	int tr[N<<2][2], lzy[N<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	void upup(int k) {
		tr[k][0]=1LL*tr[ls][0]*tr[rs][0]%mod;
		tr[k][1]=1LL*tr[ls][1]*tr[rs][1]%mod;
	}
	void down(int k) {
		if(lzy[k]) {
			swap(tr[ls][0], tr[ls][1]);
			swap(tr[rs][0], tr[rs][1]);
			lzy[ls]^=1, lzy[rs]^=1;
			lzy[k]=0;
		}
	}
	void built(int k, int l, int r) {
		if(l == r) {
			tr[k][1]=a[l], tr[k][0]=ksm(a[l], mod-2);
			return ;
		}
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
		upup(k);
	}
	void updt(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq) {
			swap(tr[k][0], tr[k][1]);
			lzy[k]^=1;
			return ;
		}
		down(k);
		int mid = ((l+r)>>1);
		if(lq <= mid)
			updt(ls, l, mid, lq, rq);
		if(mid+1 <= rq)
			updt(rs, mid+1, r, lq, rq);
		upup(k);
	}
	int ask(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq)
			return tr[k][0];
		down(k);
		int mid = ((l+r)>>1), ret = 1;
		if(lq <= mid)
			ret=ask(ls, l, mid, lq, rq);
		if(mid+1 <= rq)
			ret=1LL*ret*ask(rs, mid+1, r, lq, rq)%mod;
		upup(k);
		return ret;
	}
}AAA;
int gs,rt[N];
struct tree2 {
	node tr[20000007];
	void upup(int k) {
		tr[k].tr[0]=1LL*tr[tr[k].ll].tr[tr[k].lzy]*tr[tr[k].rr].tr[tr[k].lzy]%mod;
		tr[k].tr[1]=1LL*tr[tr[k].ll].tr[tr[k].lzy^1]*tr[tr[k].rr].tr[tr[k].lzy^1]%mod;
	}
	void built(int& k, int l, int r) {
		++gs; k=gs;
		tr[k].lzy=0;
		if(l == r) {
			tr[k].tr[1]=a[l], tr[k].tr[0]=ksm(a[l], mod-2);
			return ;
		}
		int mid = ((l+r)>>1);
		built(tr[k].ll, l, mid);
		built(tr[k].rr, mid+1, r);
		upup(k);
	}
	void updt(int& k, int l, int r, int lq, int rq) {
		++gs; tr[gs]=tr[k]; k=gs;
		if(lq <= l && r <= rq) {
			swap(tr[k].tr[0], tr[k].tr[1]);
			tr[k].lzy^=1;
			return ;
		}
		int mid = ((l+r)>>1);
		if(lq <= mid)
			updt(tr[k].ll, l, mid, lq, rq);
		if(mid+1 <= rq)
			updt(tr[k].rr, mid+1, r, lq, rq);
		upup(k);
	}
	int ask(int k, int l, int r, int lq, int rq, int now) {
		if(lq <= l && r <= rq)
			return tr[k].tr[now];
		int mid = ((l+r)>>1), ret = 1;
		if(lq <= mid)
			ret=ask(tr[k].ll, l, mid, lq, rq, now^tr[k].lzy);
		if(mid+1 <= rq)
			ret=1LL*ret*ask(tr[k].rr, mid+1, r, lq, rq, now^tr[k].lzy)%mod;
		return ret;
	}
}BBB;
int main(){
	File("fraction");
	read(n),read(q),read(gen.typ),read(gen.sedd);
	for(int i=0;i<=n;++i) a[i]=gen.get();
	for(int i=1;i<=n;++i) read(p[i]);
	int l,r,lastans=0;
	ull final_ans=0;
	if(n <= 2000 && q <= 2000) {
		for(int t=1;t<=q;++t){
			gen.get(lastans,l,r);
			int ansnow=0;
			zhan[tot=1]=n+1;
			ansnow=a[l-1];
			for(int i = l; i <= r; ++i) {
				while(p[i] >= zhan[tot]) --tot;
				ansnow=1LL*ansnow*(tot%2 == 1 ? ksm(a[i], mod-2) : a[i])%mod;
				zhan[++tot]=p[i];
			}
			lastans=ansnow;
			final_ans^=1ull*t*ansnow;
		}
		printf("%llu\n",final_ans);
		return 0;
	}
	else if(gen.typ == 0) {
		for(int t=1;t<=q;++t){
			gen.get(lastans,l,r);
			pro[l].push_back(qwq {r, t});
		}
		for(int i = 1; i <= n; ++i) {
			while(tot && p[i] >= p[zhan[tot]]) rr[zhan[tot]]=i-1, --tot;
			zhan[++tot]=i;
		}
		while(tot)
			rr[zhan[tot]]=n, --tot;
		AAA.built(1, 1, n);
		for(int i = n; i >= 1; --i) {
			if(i+1 <= rr[i])
				AAA.updt(1, 1, n, i+1, rr[i]);
			for(qwq y : pro[i])
				anss[y.d]=1LL*AAA.ask(1, 1, n, i, y.r)*a[i-1]%mod;
		}
		for(int t=1;t<=q;++t)
			final_ans^=1ull*t*anss[t];
		printf("%llu\n",final_ans);
		return 0;
	}
	else {
		for(int i = 1; i <= n; ++i) {
			while(tot && p[i] >= p[zhan[tot]]) rr[zhan[tot]]=i-1, --tot;
			zhan[++tot]=i;
		}
		while(tot) rr[zhan[tot]]=n, --tot;
		BBB.built(rt[n+1], 1, n);
		for(int i = n; i >= 1; --i) {
			rt[i]=rt[i+1];
			if(i+1 <= rr[i])
				BBB.updt(rt[i], 1, n, i+1, rr[i]);
		}
		for(int t=1;t<=q;++t){
			gen.get(lastans,l,r);
			int ansnow=1LL*a[l-1]*BBB.ask(rt[l], 1, n, l, r, 0)%mod;
			lastans=ansnow;
			final_ans^=1ull*t*ansnow;
		}
		printf("%llu\n",final_ans);
		return 0;
	}
	return 0;
}