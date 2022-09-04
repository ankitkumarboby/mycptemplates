#include<bits/stdc++.h>
#define   ll                          long long int
#define   fo(number1,number2,number3) for(int number1=number2;number1<=number3;++number1)
#define   pi                          pair<int,int>
#define   vi                          vector<int>
#define   pb                          push_back
#define   fastio                      ios_base::sync_with_stdio(false);cin.tie(NULL);
#define   cps                         CLOCKS_PER_SEC
#define   decimal(k)                  fixed<<setprecision(k)
#define   PI                          3.14159265359
#define   F                           first
#define   S                           second
#define   all(A)                      (A).begin(),(A).end()
#define   mymax                       1000000000000000001
#define   mymin                      -1000000000000000001
#define   mod                         (ll)1000000007ll
#define   SZ                          sizeof
#define   test(t_case)                "Case #"<<t_case<<": "
//#include <unordered_set>
using namespace std;
//int dx[]={0,1,0,-1};
//int dy[]={1,0,-1,0};
//int dx[]={0,1,1,-1,0,-1,1,-1};
//int dy[]={1,0,1,0,-1,-1,-1,1};
//int dx[]={1,1,2,2,-1,-1,-2,-2};
//int dy[]={2,-2,1,-1,2,-2,1,-1};

ll power(ll x,ll y,ll m){            //power(x,y)=x^y  %m;
    if(y==0)return 1;
    ll a=power(x,y/2,m);
    if(y%2){
        return (a*((a*x)%m))%m;
    }
    else{
        return (a*a)%m;
    }
}
ll mod_inverse(ll x,ll m){
    return power(x,m-2,m);
}
ll fact(ll n,ll m){
    if(n<=1)return 1;
    return (fact(n-1,m)*n)%m;
}
ll ncr(ll n,ll r,ll m){
    if(r>n || r<0)return 0;
    if(n<0)return 0;
    ll n1=1,d1=1,d2=1;
    n1=fact(n,m);d1=fact(r,m);d2=fact(n-r,m);
    ll ans=mod_inverse((d1*d2)%m,m);
    ans=(ans*n1)%m;
    return ans;
}

/***************************code begins here*****************************/
class segment_tree{
	public:
	
	int find(int l,int r){
		return 1;
	}	
};

//heavy light decomposition -> use in case of path query , query time complexity: O(n * log^2(n) )
// make seg tree of a : a[ pos[u] ] = value(u) 
class HLD{
	public:
	vector<vector<int> > g;
	int n,root,cur_pos;
	vector<int> parent,depth,heavy,head,pos;
	
	int dfs(int u,int par){
		int size=1,mx_size=-1;
		parent[u] = par;
		if(u!=par) depth[u] = 1+depth[par];
		
		for(int v:g[u]){
			if(v==par)continue;
			int v_size = dfs(v,u);
			size += v_size;
			if(v_size > mx_size){
				mx_size = v_size;
				heavy[u] = v;
			}
		}
		return size;
	}
	
	void decompose(int u,int par,int h){   		//u-> curr node  par->parent of u  h->head of current segment
		head[u] = h;
		pos[u] = ++cur_pos;
		if(heavy[u]!=-1) decompose(heavy[u],u,h);
		for(int v:g[u]){
			if((v == par) || (v == heavy[u])) continue;
			decompose(v,u,v);
		}
	}
	
	HLD(vector<vector<int> > gg,int nn,int ruut){
		g=gg;
		n=nn;
		root=ruut;
		
		parent.resize(n+1);
		depth.resize(n+1);
		heavy.resize(n+1);
		head.resize(n+1);
		pos.resize(n+1);
		for(int i=0;i<=n;++i)heavy[i] = -1;
		
		cur_pos=0;
		dfs(root,root);
		decompose(root,root,root); 
	}
	
	//important and need to be change according to problems
	//segment tree object must be pass by reference otehrwise give TLE 
	int query(int u,int v,segment_tree& o){
		int res = 0;
		for( ; head[u]!=head[v]; v=parent[head[v]]){
			if(depth[head[u]] > depth[head[v]]) 
				swap(u,v);
			
			res += o.find(pos[head[v]] , pos[v]);        // range -> [ pos[head[v]] , pos[v] ]
			
		}
		if(depth[u] > depth[v]) swap(u,v);
		res += o.find(pos[u],pos[v]);
		return res;
	}
};





int main(){
	fastio
	
}




