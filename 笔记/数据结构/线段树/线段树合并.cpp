int tot, gs, zhan[N*30]; 
struct node {
	int ls, rs;
	//...
}tr[N*30];//空间是log的! 
struct tree {//线段树合并板子 
	#define ls(x) tr[x].ls
	#define rs(x) tr[x].rs
	void upup(int k) {
		//...
	}
	void dlt(int k) { zhan[++tot]=k; }
	void cnw(int& ret) {
		if(tot) ret=zhan[tot], --tot;//回收空间,用处不是很大,兴许什么时候要卡空间了就用上看能不能过吧 
		else ret=(++gs); 
		tr[ret]=node {0, 0/*......*/};
	}
	int merge(int x, int y, int l, int r) {
		if(!x || !y) return (x|y);
		if(l == r) {//注意线段树叶子结点也要合并!!! 
			//...
			return x;
		}
		int mid = ((l+r)>>1); 
		ls(x)=merge(ls(x), ls(y), l, mid);
		rs(x)=merge(rs(x), rs(y), mid+1, r);
		upup(x), dlt(y);
		return x;
	}
	void updt(int& k, int l, int r, int tt) {
		if(!k) cnw(k);
		if(l == r) {
			//... 
			return ;
		} 
		int mid = ((l+r)>>1);
		if(tt <= mid)
			updt(ls(k), l, mid, tt);
		else
			updt(rs(k), mid+1, r, tt);
		upup(k);
	}
}A;
