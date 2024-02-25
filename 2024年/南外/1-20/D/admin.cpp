#include <bits/stdc++.h>
using namespace std;
const int N = 2005,M = 2005,K = 5005;
struct edge{
	int to,nxt,cap;
}graph[N + M + K << 1];
int n,m,k,s,t;
int type[N];
int head[N + M << 1],cnt = 0;
void addedge(int u,int v,int cap){
	edge node = {v,head[u],cap};
	graph[head[u] = cnt++] = node;
}
queue<int> q;
int depth[N + M << 1],cur[N + M << 1];
bool bfs(){
	for(int i=s;i <= t;i++)depth[i] = -1,cur[i] = head[i];
	q.push(s),depth[s] = 0;
	while(!q.empty()){
		int u = q.front();
		q.pop();
		for(int i=head[u];i >= 0;i = graph[i].nxt){
			int v = graph[i].to;
			if(graph[i].cap && depth[v] < 0)depth[v] = depth[u] + 1,q.push(v);
		}
	}
	return depth[t] > 0;
}
int dfs(int u,int rest){
	int flow = 0;
	if(u == t || !rest)return rest;
	for(int &i = cur[u];i >= 0;i = graph[i].nxt){
		int v = graph[i].to;
		if(graph[i].cap && depth[v] == depth[u] + 1){
			int go = dfs(v,min(rest,graph[i].cap));
			graph[i].cap -= go,graph[i ^ 1].cap += go;
			rest -= go,flow += go;
		}
		if(!rest)break;
	}
	return flow;
}
int maxflow(){
	int ans = 0;
	while(bfs())ans += dfs(s,m);
	return ans;
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	s = 0,t = n + 1 + (m << 1);
	for(int i=s;i <= t;i++)head[i] = -1;
	for(int i=1;i <= n;i++)scanf("%d",&type[i]);
	for(int i=1;i <= n;i++){
		if(type[i])addedge(i + (m << 1),t,1),addedge(t,i + (m << 1),0);
		else addedge(s,i + (m << 1),1),addedge(i + (m << 1),s,0);
	}
	for(int i=1;i <= m;i++)addedge(2 * i,2 * i - 1,1),addedge(2 * i - 1,2 * i,0);
	for(int i=1;i <= k;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		if(type[u])addedge(2 * v - 1,u + (m << 1),1),addedge(u + (m << 1),2 * v - 1,0);
		else addedge(u + (m << 1),2 * v,1),addedge(2 * v,u + (m << 1),0);
	}
	printf("%d\n",maxflow());
	fclose(stdin),fclose(stdout);
	return 0;
}
