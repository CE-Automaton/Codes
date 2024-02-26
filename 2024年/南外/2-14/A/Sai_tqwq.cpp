#include<bits/stdc++.h>
#include "tree.h"
using namespace std;
int solve(int n){
	if(n==1)return 1;
	vector<int> vec=query(1);
	if((int)vec.size()==2)return 1;
	int u=1,fa,dep;
	if((int)vec.size()==1)fa=vec.back(),dep=n;
	else{
		int v0=vec[0],v1=vec[1],cnt=0;
		int fa0=u,fa1=u;
		while(true){
			cnt++;
			vector<int> t0=query(v0);
			if((int)t0.size()==2)return v0;
			vector<int> t1=query(v1);
			if((int)t1.size()==2)return v1;
			if((int)t0.size()==1&&(int)t1.size()==1){
				dep=n-cnt;
				fa=vec[2];
				break;
			}else if((int)t0.size()==1){
				dep=n-cnt;
				fa=vec[1];
				break;
			}else if((int)t1.size()==1){
				dep=n-cnt;
				fa=vec[0];
				break;
			}
			if(t0[0]==fa0)fa0=v0,v0=t0[1];
			else fa0=v0,v0=t0[0];
			if(t1[0]==fa1)fa1=v1,v1=t1[1];
			else fa1=v1,v1=t1[0];
		}
	}
	if(dep==2)return fa;
	if(n<12){
		for(int i=dep;i>3;i--){
			vector<int> tmp=query(fa),ttmp;ttmp.clear();
			if(tmp[0]!=u)ttmp.push_back(tmp[0]);
			if(tmp[1]!=u)ttmp.push_back(tmp[1]);
			if(tmp[2]!=u)ttmp.push_back(tmp[2]);
			int v=ttmp[0],f=fa;bool fl=0;
			for(int d=i;d<=n;d++){
				vector<int> t=query(v);
				if((int)t.size()==2)return v;
				if((int)t.size()==1){fl=1;break;}
				if(t[0]==f)f=v,v=t[1];
				else f=v,v=t[0];
			}
			if(fl)u=fa,fa=ttmp[1];
			else u=fa,fa=ttmp[0];
		}
		vector<int> T=query(fa);
		if(T[0]!=u){
			if((int)query(T[0]).size()==2)return T[0];
			else if(T[1]!=u)return T[1];
			else return T[2];
		}else if((int)query(T[1]).size()==2)return T[1];
		else return T[2];
	}else if(dep==3){
		vector<int> T=query(fa);
		if(T[0]!=u){
			if((int)query(T[0]).size()==2)return T[0];
			else if(T[1]!=u)return T[1];
			else return T[2];
		}else if((int)query(T[1]).size()==2)return T[1];
		else return T[2];
	}else if(dep==4){
		vector<int> T=query(fa);
		if(T[0]!=u){
			vector<int> R=query(T[0]);
			if(R[0]!=fa){
				if((int)query(R[0]).size()==2)return R[0];
				else if(R[1]!=fa){
					if((int)query(R[1]).size()==2)return R[1];
				}
				else if((int)query(R[2]).size()==2)return R[2];
			}else if((int)query(R[1]).size()==2)return R[1];
			else if((int)query(R[2]).size()==2)return R[2];
			if(T[1]!=u){
				R=query(T[1]);
				if(R[0]!=fa){
					if((int)query(R[0]).size()==2)return R[0];
					else if(R[1]!=fa)return R[1];
					else return R[2];
				}else if((int)query(R[1]).size()==2)return R[1];
				else return R[2];
			}else{
				R=query(T[2]);
				if(R[0]!=fa){
					if((int)query(R[0]).size()==2)return R[0];
					else if(R[1]!=fa)return R[1];
					else return R[2];
				}else if((int)query(R[1]).size()==2)return R[1];
				else return R[2];
			}
		}else{
			vector<int> R=query(T[1]);
			if(R[0]!=fa){
				if((int)query(R[0]).size()==2)return R[0];
				else if(R[1]!=fa){
					if((int)query(R[1]).size()==2)return R[1];
				}
				else if((int)query(R[2]).size()==2)return R[2];
			}else if((int)query(R[1]).size()==2)return R[1];
			else if((int)query(R[2]).size()==2)return R[2];
			R=query(T[2]);
			if(R[0]!=fa){
				if((int)query(R[0]).size()==2)return R[0];
				else if(R[1]!=fa)return R[1];
				else return R[2];
			}else if((int)query(R[1]).size()==2)return R[1];
			else return R[2];
		}
	}else{
		for(int i=dep;i>5;i--){
			vector<int> tmp=query(fa),ttmp;ttmp.clear();
			if(tmp[0]!=u)ttmp.push_back(tmp[0]);
			if(tmp[1]!=u)ttmp.push_back(tmp[1]);
			if(tmp[2]!=u)ttmp.push_back(tmp[2]);
			int v=ttmp[0],f=fa;bool fl=0;
			for(int d=i;d<=n;d++){
				vector<int> t=query(v);
				if((int)t.size()==2)return v;
				if((int)t.size()==1){fl=1;break;}
				if(t[0]==f)f=v,v=t[1];
				else f=v,v=t[0];
			}
			if(fl)u=fa,fa=ttmp[1];
			else u=fa,fa=ttmp[0];
		}
		vector<int> T=query(fa);
		if(T[0]!=u){
			vector<int> R=query(T[0]);
			if(R[0]!=fa){
				vector<int> G=query(R[0]);
				if(G[0]!=T[0]){
					if((int)query(G[0]).size()==2)return G[0];
					else if(G[1]!=T[0]){
						if((int)query(G[1]).size()==2)return G[1];
					}
					else if((int)query(G[2]).size()==2)return G[2];
				}else if((int)query(G[1]).size()==2)return G[1];
				else if((int)query(G[2]).size()==2)return G[2];
				if(R[1]!=fa){
					G=query(R[1]);
					if(G[0]!=T[0]){
						if((int)query(G[0]).size()==2)return G[0];
						else if(G[1]!=T[0]){
							if((int)query(G[1]).size()==2)return G[1];
						}
						else if((int)query(G[2]).size()==2)return G[2];
					}else if((int)query(G[1]).size()==2)return G[1];
					else if((int)query(G[2]).size()==2)return G[2];
				}else{
					G=query(R[2]);
					if(G[0]!=T[0]){
						if((int)query(G[0]).size()==2)return G[0];
						else if(G[1]!=T[0]){
							if((int)query(G[1]).size()==2)return G[1];
						}
						else if((int)query(G[2]).size()==2)return G[2];
					}else if((int)query(G[1]).size()==2)return G[1];
					else if((int)query(G[2]).size()==2)return G[2];
				}
			}else{
				vector<int> G=query(R[1]);
				if(G[0]!=T[0]){
					if((int)query(G[0]).size()==2)return G[0];
					else if(G[1]!=T[0]){
						if((int)query(G[1]).size()==2)return G[1];
					}
					else if((int)query(G[2]).size()==2)return G[2];
				}else if((int)query(G[1]).size()==2)return G[1];
				else if((int)query(G[2]).size()==2)return G[2];
				G=query(R[2]);
				if(G[0]!=T[0]){
					if((int)query(G[0]).size()==2)return G[0];
					else if(G[1]!=T[0]){
						if((int)query(G[1]).size()==2)return G[1];
					}
					else if((int)query(G[2]).size()==2)return G[2];
				}else if((int)query(G[1]).size()==2)return G[1];
				else if((int)query(G[2]).size()==2)return G[2];
			}
			if(T[1]!=u){
				R=query(T[1]);
				if(R[0]!=fa){
					vector<int> G=query(R[0]);
					if(G[0]!=T[1]){
						if((int)query(G[0]).size()==2)return G[0];
						else if(G[1]!=T[1]){
							if((int)query(G[1]).size()==2)return G[1];
						}
						else if((int)query(G[2]).size()==2)return G[2];
					}else if((int)query(G[1]).size()==2)return G[1];
					else if((int)query(G[2]).size()==2)return G[2];
					if(R[1]!=fa){
						G=query(R[1]);
						if(G[0]!=T[1]){
							if((int)query(G[0]).size()==2)return G[0];
							else if(G[1]!=T[1])return G[1];
							else return G[2];
						}else if((int)query(G[1]).size()==2)return G[1];
						else return G[2];
					}else{
						G=query(R[2]);
						if(G[0]!=T[1]){
							if((int)query(G[0]).size()==2)return G[0];
							else if(G[1]!=T[1])return G[1];
							else return G[2];
						}else if((int)query(G[1]).size()==2)return G[1];
						else return G[2];
					}
				}else{
					vector<int> G=query(R[1]);
					if(G[0]!=T[1]){
						if((int)query(G[0]).size()==2)return G[0];
						else if(G[1]!=T[1]){
							if((int)query(G[1]).size()==2)return G[1];
						}
						else if((int)query(G[2]).size()==2)return G[2];
					}else if((int)query(G[1]).size()==2)return G[1];
					else if((int)query(G[2]).size()==2)return G[2];
					G=query(R[2]);
					if(G[0]!=T[1]){
						if((int)query(G[0]).size()==2)return G[0];
						else if(G[1]!=T[1])return G[1];
						else return G[2];
					}else if((int)query(G[1]).size()==2)return G[1];
					else return G[2];
				}
			}else{
				R=query(T[2]);
				if(R[0]!=fa){
					vector<int> G=query(R[0]);
					if(G[0]!=T[2]){
						if((int)query(G[0]).size()==2)return G[0];
						else if(G[1]!=T[2]){
							if((int)query(G[1]).size()==2)return G[1];
						}
						else if((int)query(G[2]).size()==2)return G[2];
					}else if((int)query(G[1]).size()==2)return G[1];
					else if((int)query(G[2]).size()==2)return G[2];
					if(R[1]!=fa){
						G=query(R[1]);
						if(G[0]!=T[2]){
							if((int)query(G[0]).size()==2)return G[0];
							else if(G[1]!=T[2])return G[1];
							else return G[2];
						}else if((int)query(G[1]).size()==2)return G[1];
						else return G[2];
					}else{
						G=query(R[2]);
						if(G[0]!=T[2]){
							if((int)query(G[0]).size()==2)return G[0];
							else if(G[1]!=T[2])return G[1];
							else return G[2];
						}else if((int)query(G[1]).size()==2)return G[1];
						else return G[2];
					}
				}else{
					vector<int> G=query(R[1]);
					if(G[0]!=T[2]){
						if((int)query(G[0]).size()==2)return G[0];
						else if(G[1]!=T[2]){
							if((int)query(G[1]).size()==2)return G[1];
						}
						else if((int)query(G[2]).size()==2)return G[2];
					}else if((int)query(G[1]).size()==2)return G[1];
					else if((int)query(G[2]).size()==2)return G[2];
					G=query(R[2]);
					if(G[0]!=T[2]){
						if((int)query(G[0]).size()==2)return G[0];
						else if(G[1]!=T[2])return G[1];
						else return G[2];
					}else if((int)query(G[1]).size()==2)return G[1];
					else return G[2];
				}
			}
		}else{
			vector<int> R=query(T[1]);
			if(R[0]!=fa){
				vector<int> G=query(R[0]);
				if(G[0]!=T[1]){
					if((int)query(G[0]).size()==2)return G[0];
					else if(G[1]!=T[1]){
						if((int)query(G[1]).size()==2)return G[1];
					}
					else if((int)query(G[2]).size()==2)return G[2];
				}else if((int)query(G[1]).size()==2)return G[1];
				else if((int)query(G[2]).size()==2)return G[2];
				if(R[1]!=fa){
					G=query(R[1]);
					if(G[0]!=T[1]){
						if((int)query(G[0]).size()==2)return G[0];
						else if(G[1]!=T[1]){
							if((int)query(G[1]).size()==2)return G[1];
						}
						else if((int)query(G[2]).size()==2)return G[2];
					}else if((int)query(G[1]).size()==2)return G[1];
					else if((int)query(G[2]).size()==2)return G[2];
				}else{
					G=query(R[2]);
					if(G[0]!=T[1]){
						if((int)query(G[0]).size()==2)return G[0];
						else if(G[1]!=T[1]){
							if((int)query(G[1]).size()==2)return G[1];
						}
						else if((int)query(G[2]).size()==2)return G[2];
					}else if((int)query(G[1]).size()==2)return G[1];
					else if((int)query(G[2]).size()==2)return G[2];
				}
			}else{
				vector<int> G=query(R[1]);
				if(G[0]!=T[1]){
					if((int)query(G[0]).size()==2)return G[0];
					else if(G[1]!=T[1]){
						if((int)query(G[1]).size()==2)return G[1];
					}
					else if((int)query(G[2]).size()==2)return G[2];
				}else if((int)query(G[1]).size()==2)return G[1];
				else if((int)query(G[2]).size()==2)return G[2];
				G=query(R[2]);
				if(G[0]!=T[1]){
					if((int)query(G[0]).size()==2)return G[0];
					else if(G[1]!=T[1]){
						if((int)query(G[1]).size()==2)return G[1];
					}
					else if((int)query(G[2]).size()==2)return G[2];
				}else if((int)query(G[1]).size()==2)return G[1];
				else if((int)query(G[2]).size()==2)return G[2];
			}
			R=query(T[2]);
			if(R[0]!=fa){
				vector<int> G=query(R[0]);
				if(G[0]!=T[2]){
					if((int)query(G[0]).size()==2)return G[0];
					else if(G[1]!=T[2]){
						if((int)query(G[1]).size()==2)return G[1];
					}
					else if((int)query(G[2]).size()==2)return G[2];
				}else if((int)query(G[1]).size()==2)return G[1];
				else if((int)query(G[2]).size()==2)return G[2];
				if(R[1]!=fa){
					G=query(R[1]);
					if(G[0]!=T[2]){
						if((int)query(G[0]).size()==2)return G[0];
						else if(G[1]!=T[2])return G[1];
						else return G[2];
					}else if((int)query(G[1]).size()==2)return G[1];
					else return G[2];
				}else{
					G=query(R[2]);
					if(G[0]!=T[2]){
						if((int)query(G[0]).size()==2)return G[0];
						else if(G[1]!=T[2])return G[1];
						else return G[2];
					}else if((int)query(G[1]).size()==2)return G[1];
					else return G[2];
				}
			}else{
				vector<int> G=query(R[1]);
				if(G[0]!=T[2]){
					if((int)query(G[0]).size()==2)return G[0];
					else if(G[1]!=T[2]){
						if((int)query(G[1]).size()==2)return G[1];
					}
					else if((int)query(G[2]).size()==2)return G[2];
				}else if((int)query(G[1]).size()==2)return G[1];
				else if((int)query(G[2]).size()==2)return G[2];
				G=query(R[2]);
				if(G[0]!=T[2]){
					if((int)query(G[0]).size()==2)return G[0];
					else if(G[1]!=T[2])return G[1];
					else return G[2];
				}else if((int)query(G[1]).size()==2)return G[1];
				else return G[2];
			}
		}
	}
}
