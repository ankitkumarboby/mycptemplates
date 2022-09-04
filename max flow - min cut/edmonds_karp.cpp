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
#define   mod                         (ll)1000000007
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
    if(r>n)return 0;
    ll n1=1,d1=1,d2=1;
    n1=fact(n,m);d1=fact(r,m);d2=fact(n-r,m);
    ll ans=mod_inverse((d1*d2)%m,m);
    ans=(ans*n1)%m;
    return ans;
}
 
/***************************code begins here*****************************/

//edmonds karp algorithm -> O(V * E^2)

class max_flow_edmonds_karp{
	public:
	vector<vector<pi> > g;  //{v,w} v-> to_vertex  w-> capacity of (u,v) and g id directed graph
	
	int n; //n-> no of vertex
	int s,t; //s->source t->sink
	
	vector<vector<int> > capacity,adj;
	int INF=1000000000; //change as required
	
	
	void build(){
		capacity = vector<vi>(n+1,vi(n+1,0));
		fo(u,1,n){
			for(auto pr:g[u]){
				int v=pr.F,w=pr.S;
				capacity[u][v]+=w;
			}
		}
		adj = vector<vi>(n+1);
		fo(u,1,n)fo(v,1,n){
			if(capacity[u][v]||capacity[v][u]) adj[u].pb(v);
		}
	}
	
	max_flow_edmonds_karp(vector<vector<pi> > &gg,int nn,int ss,int tt){
		g=gg;
		n=nn;
		s=ss;
		t=tt;
		build();
	}
	
	int bfs(vector<int>& par){
		fill(all(par),-1);
		par[s]=s;
		queue<pi> qu;
		qu.push({s,INF});
		
		while(!qu.empty()){
			int u=qu.front().F;
			int curr_flow=qu.front().S;
			qu.pop();
			for(auto v:adj[u]){
				if(par[v]==-1 && capacity[u][v]){
					par[v]=u;
					int next_flow=min(curr_flow,capacity[u][v]);
					if(v==t)return next_flow;
					qu.push({v,next_flow});
				}
			}
		}
		return 0;
	}
	
	int max_flow(){
		int flow=0;
		vector<int> par(n+1);
		int new_flow;
		while(new_flow = bfs(par)){
			flow+=new_flow;
			int cur=t;
			while(cur!=s){
				int prv=par[cur];
				capacity[prv][cur] -= new_flow;
				capacity[cur][prv] += new_flow;
				cur=prv;
			}
		}
		return flow;
	}	
 
};

int main(){
	
}
