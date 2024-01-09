#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb push_back
#define rep(i,a,b) for(int i=a,i##end=b;i<=i##end;++i)
char IO;
int rd(){
	int s=0;
	while(!isdigit(IO=getchar()));
	do s=(s<<1)+(s<<3)+(IO^'0');
	while(isdigit(IO=getchar()));
	return s;
}
enum{N=200010,LINF=1ll<<60};

int n,m,k,I[N]; ll L;
struct Group{
	vector <int> A;
	int l,r,c;
	struct Node{
		int l,p,r; ll s;
		bool operator < (const Node &__) const { return s>__.s; }
	};
	priority_queue <Node> que;
	vector <ll> V;
	void Init(){
		l=rd(),r=rd(),sort(A.begin(),A.end()),c=A.size();
		if(c<l) {
			rep(i,1,k) puts("-1");
			exit(0);
		}
		r=min(r,c);
		rep(i,0,l-1) L+=A[i];
		ll s=0;
		if(!l) V.pb(0);
		rep(i,0,c-1) {
			if(i>=r) break;
			s+=A[i];
			if(i>=l-1) que.push((Node){i-1,i,c-1,s});
		}
	}
	void Next(){
		if(que.empty()) return V.pb(LINF);
		Node t=que.top(); que.pop();
		V.pb(t.s);
		if(t.p<t.r) que.push((Node){t.l,t.p+1,t.r,t.s-A[t.p]+A[t.p+1]}); // Move current point
		if(~t.l && t.l<t.p-1) que.push((Node){t.l-1,t.l+1,t.p-1,t.s-A[t.l]+A[t.l+1]}); // Move previous point 
	}
	// get kth sum
	ll operator [] (const int &k){
		while((int)V.size()<k) Next();
		return V[k-1];
	}
} S[N];

struct Node{
	int x,y; ll s;
	bool operator < (const Node &__) const { return s>__.s; }
};
priority_queue <Node> que;

int main(){
	freopen("shopping.in", "r", stdin);
	freopen("shopping.out", "w", stdout);
	n=rd(),m=rd(),k=rd();
	rep(i,1,n) { int x=rd(); S[x].A.pb(rd()); }
	rep(i,1,m) S[i].Init();
	printf("%lld\n",L),k--;
	rep(i,1,m) I[i]=i;
	sort(I+1,I+m+1,[&](int x,int y){ return S[x][2]-S[x][1]<S[y][2]-S[y][1]; });
	que.push((Node){1,2,L-S[I[1]][1]+S[I[1]][2]});
	while(k) {
		Node t=que.top(); que.pop();
		if(t.s>=LINF) break;
		k--,printf("%lld\n",t.s);
		int i=I[t.x],j=I[t.x+1];
		que.push((Node){t.x,t.y+1,t.s-S[i][t.y]+S[i][t.y+1]});// Move current point
		if(j) que.push((Node){t.x+1,2,t.s-S[j][1]+S[j][2]}); // Move next point
		if(t.y==2 && j) que.push((Node){t.x+1,2,t.s-S[i][2]+S[i][1]-S[j][1]+S[j][2]}); // Back current point ,and move next point
	}
	while(k--) puts("-1");
}
