#include <bits/stdc++.h>
#include "tree.h"
using namespace std;
const int N = (1<<13)+5;
int vis[N], zhan[N], tot, cnt;
vector <int> to[N];
queue <int> q[6];
void ask(int x) {
    if(!vis[x]) to[x]=query(x), vis[x]=1;
}
void dfs(int now) {
    ask(now);
    if(to[now].size() != 3) return ;
    int tt = to[now][0];
    dfs(tt);
    zhan[++tot]=tt;
}
void chng() {
    for(int op = (tot+1)/2; tot > op; --tot);
}
void ksm(int x) {
    int now = 0;
    for(int i = 0; i < 3; ++i) {
        int j = to[x][i];
        if(!vis[j]) {
            now=j;
            break;
        }
    }
    ask(now);
    while(to[now].size() == 3) { //跳到根或者叶子就结束
        zhan[++tot]=now;
        now=to[now][0];
        ask(now);
    }
    zhan[++tot]=now;
}
int solve(int n) {
    if(n == 1) return 1;
    tot=0;
    for(int i = 1; i <= n; ++i)
        vis[i]=0, to[i].clear();//清空
    dfs(1);//先找第一个儿子链
    if(to[zhan[tot]].size() == 2) return zhan[tot];
    ksm(1);//拼接
    if(to[zhan[tot]].size() == 2) return zhan[tot];
    while(1) {
        chng();//跳到lca
        if(to[zhan[tot]].size() == 2) return zhan[tot];
        if(n-tot <= 4) {//深度小直接搜(bfs)
            while(!q[0].empty()) q[0].pop();
            q[0].push(zhan[tot]);
            int dp = n-tot;
            for(int i = 1; i <= dp; ++i) {
                while(!q[0].empty()) {//扩展
                    int it = q[0].front(); q[0].pop();
                    for(int j = 0; j < 3; ++j) {
                        int k = to[it][j];
                        if(!vis[k]) 
                            q[i].push(k);
                    }
                }
                while(!q[i].empty()) {//看有没有根节点
                    if(i == dp && q[i].size() == 2)
                        return q[i].front();
                    int it = q[i].front(); q[i].pop();
                    ask(it);
                    if(to[it].size() == 2) return it;
                    if(to[it].size() == 3)
                        q[0].push(it);
                }
            }
            return 0;
        }
        if(to[zhan[tot]].size() == 2) return zhan[tot];
    }
}