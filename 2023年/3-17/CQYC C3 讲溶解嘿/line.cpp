#include <bits/stdc++.h>
// char buf[1<<23],*p1=buf,*p2=buf;
// #define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
using namespace std;
int n, dep[5005], az[5005], vis[5005];
struct node {
    int h, d, id;
}l[5005], r[5005], per[5005];
bitset<10004> to[10004], ppp;

template <typename T> inline void read(T& s) {
	s=0; char ch = getchar(); while(ch<'0' || ch > '9') ch=getchar();
	while(ch >= '0'&& ch <= '9') s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
}
int lne; char put[105];
template <typename T> void write(T x) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
}
int comp1(node A, node B) {
    return A.h < B.h;
}
int comp2(node A, node B) {
    return 1LL*A.d*B.h < 1LL*B.d*A.h;
}

void dfs(int x, int pd) {
//	cout<<x<<" ";
	if(pd && dep[x] != n-1) {
		ppp=(to[x]&to[x+n]);
		for(int i = ppp._Find_first(); i <= n; i=ppp._Find_next(i)) {
			int v = i+n;
			if(dep[i] < dep[x]+1 && !vis[i] && ppp[v])
				dep[i]=dep[x]+1, vis[i]=1, dfs(i, 1), vis[i]=0;
		}
	}
	else {
		ppp=to[x];
		for(int i = ppp._Find_first(); i <= n+n; i=ppp._Find_next(i)) {
			if(i <= n) continue;
			int v = i-n;
			if(dep[v] < dep[x]+1 && !vis[v])
				dep[v]=dep[x]+1, vis[v]=1, dfs(v, 1), vis[v]=0;
		}
	}
}

int main() {
	 freopen("line.in", "r", stdin);
	 freopen("line.out", "w", stdout);
    read(n);
    for(int i = 1; i <= n; ++i)
        read(per[i].h), read(per[i].d), per[i].id=i;
//    sort(per+1, per+1+n, comp1);
//    for(int i = 1; i <= n; ++i) {
//        int ll = 0, rr = 0;
//        for(ll = 1; ll <= i; ++ll)
//            if(per[ll].h == per[i].h) {
//                --ll;
//                break;
//            }
//            else
//                l[ll].h=per[i].h-per[ll].h, l[ll].d=per[i].d-per[ll].d, l[ll].id=per[ll].id;
//        for(rr = 1; rr <= n-i+1; ++rr)
//            if(per[n-rr+1].h == per[i].h) {
//                --rr;
//                break;
//            }
//            else
//                r[rr].h=per[i].h-per[n-rr+1].h, r[rr].d=per[i].d-per[n-rr+1].d, r[rr].id=per[rr].id;
//        if(ll)
//            sort(l+1, l+1+ll, comp2);
//        if(rr)
//            sort(r+1, r+1+rr, comp2);
//        if(i == 1 || per[i].h != per[i-1].h) {
//            for(int o = ll+1; o < rr; ++o)
//                ppp[per[o].id+n]=1;
//            for(int o = ll+1; o < rr; ++o)
//                to[per[o].id]|=ppp;
//            for(int o = ll+1; o < rr; ++o)
//                ppp[per[o].id+n]=0;
//            
//            for(int o = ll+1; o < rr; ++o)
//                ppp[per[o].id]=1;
//            for(int o = ll+1; o < rr; ++o)
//                to[per[o].id+n]|=ppp;
//            for(int o = ll+1; o < rr; ++o)
//                ppp[per[o].id]=0;
//        }
//        for(int j = 1; j <= ll; ++j)
//            to[per[i].id][l[j].id+n]=1, ppp[l[j].id]=1;
//        int qqq = 1;
//        for(int j = 1; j <= ll; ++j) {
//            while(qqq <= ll && 1LL*l[j].d*l[qqq].h > 1LL*l[qqq].d*l[j].h)
//                ppp[l[qqq].id]=0, ++qqq;
//            to[l[j].id+n]|=ppp;
//        }
//        for(int j = 1; j <= ll; ++j)
//            ppp[l[j].id]=0;
//
//        qqq=1;
//        for(int j = 1; j <= rr; ++j)
//            to[per[i].id][r[j].id+n]=1, ppp[r[j].id]=1;
//        for(int j = 1; j <= rr; ++j) {
//            while(qqq <= ll && 1LL*r[j].d*r[qqq].h > 1LL*r[qqq].d*r[j].h)
//                ppp[r[qqq].id]=0, ++qqq;
//            to[r[j].id+n]|=ppp;
//        }
//        for(int j = 1; j <= rr; ++j)
//            ppp[r[j].id]=0;
//        
//        qqq=1;
//        for(int j = 1; j <= ll; ++j) {
//            while(qqq <= rr && 1LL*l[j].d*r[qqq].h <= 1LL*r[qqq].d*l[j].h)
//                ppp[r[qqq].id]=1, ++qqq;
//            to[l[j].id+n]|=ppp;
//        }
//        for(int j = 1; j <= rr; ++j)
//            ppp[r[j].id]=0;
//
//        qqq=1;
//        for(int j = 1; j <= rr; ++j) {
//            while(qqq <= ll && 1LL*r[j].d*l[qqq].h <= 1LL*l[qqq].d*r[j].h)
//                ppp[l[qqq].id]=1, ++qqq;
//            to[r[j].id+n]|=ppp;
//        }
//        for(int j = 1; j <= ll; ++j)
//            ppp[l[j].id]=0;
//    }
	for(int i = 1; i <= n; ++i) 
		for(int j = 1; j <= n; ++j) {
			if(i == j) continue;
			for(int k = 1; k <= n; ++k) {
				if(i == k || j == k) continue;
				if(1LL*(per[i].h-per[k].h)*(per[i].d-per[j].d) <= 1LL*(per[i].d-per[k].d)*(per[i].h-per[j].h))
					to[i][j+n]=1, to[j+n][k]=1/*, cout<<i<<"-"<<j<<"-"<<k<<"\n"*/;
			}
		}
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) 
			dep[j]=0, az[j]=0;
		dep[i]=vis[i]=1;
		dfs(i, 0);
		vis[i]=0;
		int pd = 1;
		for(int i = 1; i <= n; ++i) {
//			cout<<i<<" "<<dep[i]<<"\n";
			if(az[dep[i]] || !dep[i]) {
				pd=0;
				break;
			}
			az[dep[i]]=i;
		}
		if(pd) {
			for(int i = 1; i <= n; ++i)
				write(az[i]), putchar(' ');
			exit(0);
		}
	} 
	puts("-1");
	return 0;
}
