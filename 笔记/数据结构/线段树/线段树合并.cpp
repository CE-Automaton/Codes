int tot, gs, zhan[N*30]; 
struct node {
	int ls, rs;
	//...
}tr[N*30];//�ռ���log��! 
struct tree {//�߶����ϲ����� 
	#define ls(x) tr[x].ls
	#define rs(x) tr[x].rs
	void upup(int k) {
		//...
	}
	void dlt(int k) { zhan[++tot]=k; }
	void cnw(int& ret) {
		if(tot) ret=zhan[tot], --tot;//���տռ�,�ô����Ǻܴ�,����ʲôʱ��Ҫ���ռ��˾����Ͽ��ܲ��ܹ��� 
		else ret=(++gs); 
		tr[ret]=node {0, 0/*......*/};
	}
	int merge(int x, int y, int l, int r) {
		if(!x || !y) return (x|y);
		if(l == r) {//ע���߶���Ҷ�ӽ��ҲҪ�ϲ�!!! 
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
