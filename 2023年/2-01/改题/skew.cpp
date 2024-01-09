#include <bits/stdc++.h>
using namespace std;
int n, typ, q, len[200005], midd, mr, ans, ll, rr;
char s[100005], t[200005];
int lasans;
struct dian {
	int ls, rs, gs, slen, si;
	dian operator +(const dian& a) const {
		dian ret;
		ret.gs=gs+a.gs, ret.si=si+a.si, ret.slen=slen+a.slen;
		return ret;
	}
};
struct zxtree {
	int tot, root[200005];
	dian p[4000005];
	void update(int &x, int to, int lent, int i, int l, int r) {
		p[++tot]=p[x], x=tot;
		++p[x].gs, p[x].si+=i, p[x].slen+=lent;
		if(l == r) return ;
		int mid = (l+r)/2;
		if(to <= mid) update(p[x].ls, to, lent, i, l, mid);
		else update(p[x].rs, to, lent, i, mid+1, r);
	}
	dian ask(int x, int l, int r, int lq, int rq) {
		if(!x || lq > rq) return dian{0,0,0,0,0};
		if(lq <= l && r <= rq) return p[x];
		int mid = (l+r)/2;
		if(lq <= mid && mid+1 <= rq)
			return ask(p[x].ls, l, mid, lq, mid)+ask(p[x].rs, mid+1, r, mid+1, rq);
		if(lq <= mid) return ask(p[x].ls, l, mid, lq, rq);
		if(mid+1 <= rq) return ask(p[x].rs, mid+1, r, lq, rq);
	}
}A, B;
int main() {
	freopen("skew.in", "r", stdin);
	freopen("skew.out", "w", stdout);
	scanf("%d%d", &n, &typ);
	scanf("%s", s+1);
	for(int i = 1; i <= n; ++i) t[i*2]=s[i], t[i*2-1]='#';
	t[2*n+1]=t[0]='#', len[0]=len[1]=1, midd=1, mr=2;
	for(int i = 2; i <= 2*n+1; ++i) {
		if(i >= mr) len[i]=1;
		else len[i]=min(len[midd*2-i], mr-i);
		while(t[i+len[i]] == t[i-len[i]]) ++len[i];
		if(i+len[i] > mr) {
			mr=i+len[i];
			midd=i;
		}
	}
	for(int i = 2; i <= 2*n; ++i) {
		A.root[i]=A.root[i-1];
		if(len[i]/2) A.update(A.root[i], (i/2-len[i]/2+1), len[i]/2, i/2, 1, n);
	}
	for(int i = 2*n; i >= 2; --i) {
		B.root[i]=B.root[i+1];
		if(len[i]/2) B.update(B.root[i], ((i+1)/2+len[i]/2-1), len[i]/2, (i+1)/2, 1, n);
	}
	scanf("%d", &q);
	for(int i = 1; i <= q; ++i) {
		scanf("%d%d", &ll, &rr); if(typ) ll^=lasans, rr^=lasans;
		lasans=0;
		lasans+=A.ask(A.root[ll+rr], 1, n, ll, ll+rr).slen;
		dian x, y;
		x=A.ask(A.root[ll+rr], 1, n, 1, ll-1);
		y=A.ask(A.root[2*ll-1], 1, n, 1, ll-1);
		lasans+=(x.si-y.si)-(x.gs-y.gs)*(ll-1);
		lasans+=B.ask(B.root[ll+rr+1], 1, n, (ll+rr+1)/2, rr).slen;
		x=B.ask(B.root[ll+rr+1], 1, n, rr+1, n);
		y=B.ask(B.root[2*rr+1], 1, n, rr+1, n);
		lasans+=(x.gs-y.gs)*(rr+1)-(x.si-y.si);
		printf("%d\n", lasans);
	}
	return 0;
} 
