#include<cstdio>
int n;
struct edge{int to;edge*next;}E[200010],*ne=E,*first[100010];
void link(int u,int v){*ne=(edge){v,first[u]};first[u]=ne++;}
struct node{
	int siz,val;
	node*ch[2];
}nodes[1900010],*newnode=nodes,*roots[100010];
node*create(int v,int d=17){
	node*x=newnode++;
	x->siz=1;
	if(!d)return x;
	x->ch[v>>d-1&1]=create(v,d-1);
	return x;
}
int find(node*x,node*y,int d){
	int s=0;
	for(;d;d--){
		int c=!x->ch[0];
		x=x->ch[c];
		if(y->ch[c])y=y->ch[c];
		else s|=1<<d-1,y=y->ch[!c];
	}
	return s;
}
int max(int a,int b){return a>b?a:b;}
node*merge(node*x,node*y,int d=17){
	if(!x)return y;
	if(!y)return x;
	x->siz+=y->siz;
	if(!d)return x;
	x->ch[0]=merge(x->ch[0],y->ch[0],d-1);
	x->ch[1]=merge(x->ch[1],y->ch[1],d-1);
	if(!x->ch[0])x->val=x->ch[1]->val;
	else if(!x->ch[1])x->val=x->ch[0]->val;
	else if(x->ch[0]->siz==1)x->val=1<<d-1|find(x->ch[0],x->ch[1],d-1);
	else if(x->ch[1]->siz==1)x->val=1<<d-1|find(x->ch[1],x->ch[0],d-1);
	else x->val=max(x->ch[0]->val,x->ch[1]->val);
	return x;
}
int ans[100010];
void dfs(int i,int f){
	for(edge*e=first[i];e;e=e->next)if(e->to!=f){
		dfs(e->to,i);
		roots[i]=merge(roots[i],roots[e->to]);
	}
	ans[i]=roots[i]->siz<2?-1:roots[i]->val;
}
int main(){
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	scanf("%d",&n);
	for(int i=1,v;i<=n;i++)scanf("%d",&v),roots[i]=create(v);
	for(int i=1,u,v;i<n;i++)scanf("%d%d",&u,&v),link(u,v),link(v,u);
	dfs(1,0);
	for(int i=1;i<=n;i++)printf("%d\n",ans[i]);
}
