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


//disjoint_set_union with rollback
class dsu_with_rollback{
	public:
	int n;
	vi parent;
	vi rank;
	vi size;
	stack<pair<int,int> > st;
	
	dsu_with_rollback(){
		
	}
	dsu_with_rollback(int nn){
		n=nn;
		parent.resize(n+1);
		rank.resize(n+1);
		size.resize(n+1);
		fo(i,1,n){
			rank[i]=0;
			parent[i]=i;
			size[i]=1;
		}
	}
	int find_set(int v){
		if(v==parent[v])
		return v;
		return find_set(parent[v]);  //dont do path compression with rollback
	}
	void union_set(int a,int b){
		a=find_set(a);
		b=find_set(b);
		if(a!=b){
			if(rank[a]<rank[b]) swap(a,b);
			st.push({b,rank[a]});
			parent[b]=a;
			rank[a]=max(rank[a],rank[b]+1);
			size[a]+=size[b];
		}
		else st.push({-1,-1});
	}
	void rollback(){
		if(st.empty())return;
		pair<int,int> pr=st.top();
		st.pop();
		if(pr.first == -1)return;
		int v=pr.first;
		int u=parent[v];
		rank[u]=pr.second;
		size[u]-=size[v];
		parent[v]=v;
	}
	
};


//query tree --> use to solve problem of dynamic connectivity
struct query{
	int u,v;
	bool united;
	query(){
		united=false;
	}
	query(int u_,int v_){
		u=u_;
		v=v_;
		united=false;
	}
};

class query_tree{
	public:
	vector<vector<query> > st;
	dsu_with_rollback o;
	vector<int> ans;
	int n,t; //n= no in dsu ans t=maximum time 
	
	query_tree(){
		
	}
	query_tree(int nn,int tt){
		n=nn;
		t=tt;
		o = dsu_with_rollback(n);
		st.resize(4*t+10);
		ans.resize(t+1);
	}
	
	void add(query q,int l,int r,int ind,int low,int high){
		if(low>r || high<l)return;
		if(low>=l && high<=r){
			st[ind].push_back(q);
			return;
		}
		int mid = (low+high)/2;
		add(q,l,r,2*ind,low,mid);
		add(q,l,r,2*ind+1,mid+1,high);
	}
	void add(query q,int l,int r){
		add(q,l,r,1,1,t);
	}
	void dfs(int ind,int low,int high){
		for(query &q:st[ind]){      //dont remove reference -> &q
			if(o.find_set(q.u)!=o.find_set(q.v)){
				o.union_set(q.u,q.v);
				q.united = true;
			}
		}
		if(low==high){
			// answer the required using ans vector
			if(ans[low]!=-1){
				int u=ans[low];
				u=o.find_set(u);
				cout<<o.size[u]<<'\n';
			}
		}
		else{
			int mid=(low+high)/2;
			dfs(2*ind,low,mid);
			dfs(2*ind+1,mid+1,high);
		}
		for(query q:st[ind]){
			if(q.united){
				o.rollback();
				q.united = false;
			}
		}
	}
};


int main(){
	fastio
	
}




